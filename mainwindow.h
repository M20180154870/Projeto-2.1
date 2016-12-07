#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void putData();
private slots:

  void timerEvent(QTimerEvent *e);

  void on_pushButton_clicked();

  void on_pushButton_Connect_clicked();

  void on_pushButton_Disconnect_clicked();

  void on_pushButton_Start_clicked();

  void on_pushButton_Stop_clicked();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int timer;
};

#endif // MAINWINDOW_H

