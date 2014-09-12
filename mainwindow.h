#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class PortControl;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fillparam();

int t;
private:
    Ui::MainWindow *ui;
    PortControl *m_control;
public slots:
     void soed();
private slots:

 void saveport(QString str);
 void savespeed(QString str);
 void savestopbits(QString str);
 void error(QString error1);
};

#endif // MAINWINDOW_H
