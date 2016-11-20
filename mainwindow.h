#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <time.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void tcpConnect();

public slots:
  void putData();

private slots:
  void on_pushButton_Connect_clicked();

  void lcdNumber_Max();

  void lcdNumber_Min();

  void lcdNumber_Time();

  void print(QString strp);

  bool stop();

  void on_pushButton_Start_clicked();

  void on_pushButton_Stop_clicked(bool checked);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;

  QString IP;
  int Max, Min, Time;

protected:

};

#endif // MAINWINDOW_H
