#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <time.h>
#include <unistd.h>
/**
 * @brief MainWindow::MainWindow é o construtor da classe.
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui -> setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();


  connect(ui -> pushButton_Start,
          SIGNAL(clicked(bool)),
          this,
          SLOT(putData()));

}

/**
 * @brief MainWindow::tcpConnect é a classe de conexão ao servidor.
 */
void MainWindow::tcpConnect(){
  socket -> connectToHost(IP,1234);
  if(socket -> waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

//Comentand

/**
 * @brief MainWindow::putData gera as informações, mensagens TCP, que serão produzidas e enviadas ao servidor.
 */
void MainWindow::putData()
{
  QDateTime datetime;
  QString str,str1;
  if(socket -> state() == QAbstractSocket::ConnectedState){
      //int i = 0;
      //while(i < 10){

        lcdNumber_Max();
        lcdNumber_Min();
        lcdNumber_Time();

        datetime = QDateTime::currentDateTime();

        str = "set "+
            datetime.toString(Qt::ISODate)+
            " "+
            QString::number(Min + (qrand()%Max))+"\r\n";

        ui -> textBrowser -> append(str);

        qDebug() << str;

        qDebug() << socket -> write(str.toStdString().c_str()) << " bytes written";

        if(socket -> waitForBytesWritten(3000)){
        qDebug() << "wrote";

        sleep(Time);



        //i++;
        }
      //}
  }
}

/**
 * @brief MainWindow::~MainWindow é o destrutor da classe.
 */
MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}

/**
 * @brief MainWindow::on_pushButton_Connect_clicked passa um IP para realizar a conexão com o servidor
 */
void MainWindow::on_pushButton_Connect_clicked()
{
    IP = ui -> lineEdit_TCP -> text();

    qDebug() << IP;

    tcpConnect();
}

/**
 * @brief MainWindow::lcdNumber_Max estabelece um valor máximo para intervalo de dados
 */
void MainWindow::lcdNumber_Max()
{
    Max = ui -> lcdNumber_Max -> value();

    qDebug() << Max;
}

/**
 * @brief MainWindow::lcdNumber_Min estabelece um valor máximo para intervalo de dados
 */
void MainWindow::lcdNumber_Min()
{
    Min = ui -> lcdNumber_Min -> value();

    qDebug() << Min;
}

/**
 * @brief MainWindow::lcdNumber_Time NÃO CONCLUÍDO
 */
void MainWindow::lcdNumber_Time()
{
    Time = ui -> lcdNumber_Time -> value();

    qDebug() << Time;
}

/**
 * @brief MainWindow::stop NÃO CONCLUÍDO
 * @return
 */
bool MainWindow::stop()
{
    return ui -> pushButton_Stop -> isChecked();
}

/**
 * @brief MainWindow::on_pushButton_Start_clicked inicializa o recebimento das informações do putData()
 */
void MainWindow::on_pushButton_Start_clicked()
{
    int i = 0;
    bool checked = true;
    while(true){
        on_pushButton_Stop_clicked(checked);
        if (checked == true){
            putData();
        }else{
            return;
        }
    }
}

/**
 * @brief MainWindow::on_pushButton_Stop_clicked NÃO CONCLUÍDO
 * @param checked
 */
void MainWindow::on_pushButton_Stop_clicked(bool checked)
{
    checked = false;
}
