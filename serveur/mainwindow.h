#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlTableModel>
#include <QTimer>
#include "rowdata.h"
#include "myparentobject.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,public myParentObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void newConnection();
    void readyReadB();
    void disconnectedB();
    void readyReadA();
    void disconnectedA();
    void onTimeOut();
private:
    rowData *currentData;
    void toDB();
    void refreshData(QString);
    void setTextOnUi(QString,QString,QString);


    Ui::MainWindow *ui;
    int tcpPort = 9854 ;
    QTcpServer *server = nullptr ;
    QTcpSocket *clientA = nullptr ;
    QTcpSocket *clientB = nullptr ;
    QTimer *timer;
    bool clientIsSending=false;
    bool timerStarted=false;
};

#endif // MAINWINDOW_H
