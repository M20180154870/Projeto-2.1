#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer> // Classe que fornece temporizadores repetitivos e de uma única vez.


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

}

void MainWindow::timerEvent(QTimerEvent *e){ // Função para ficar reenviando a cada tempo
    putData();
}

void MainWindow::putData() // Função que gera os textos a ser enviados com a data, tempo e número aleatório
{
   int maxx = ui->maximo->value(); // Constante para valor máximo
   int minn = ui->minimo->value(); // Constante para valor mínimo

  QDateTime datetime;
  QString str;
  if(socket->state()== QAbstractSocket::ConnectedState){
      datetime = QDateTime::currentDateTime();
      str = "set "+
          datetime.toString(Qt::ISODate)+
          " "+
          QString::number((qrand()%((maxx+1)-minn))+minn)+"\r\n"; // Geração do número aleatória de acordo com o intervalo

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }

  ui->textBrowser->append(str); // Impressão do texto no textBrowser

}

MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}

void MainWindow::on_pushButton_Connect_clicked()
{
    socket->connectToHost(ui->ip->text(),1234);
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }
}

void MainWindow::on_pushButton_Disconnect_clicked()
{
    qDebug() << "Disconnected";
    close();
}

void MainWindow::on_pushButton_Start_clicked()
{
    int inicio = ui->timming->value(); // Cria uma variável para receber o valor do timing
    timer = startTimer(inicio*1000); // Inicia o Timer de acordo com o escolhido em timing
}

void MainWindow::on_pushButton_Stop_clicked()
{
    killTimer(timer);
}

