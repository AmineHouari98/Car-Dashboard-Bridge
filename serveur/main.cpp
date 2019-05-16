#include "mainwindow.h"
#include "myparentobject.h"
#include "enumtables.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

QSqlDatabase bdd ;
void msgCritical(QString,QString);
bool initDatabase(QString);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString databaseName = "bdd.sqlite";
    QString databasePath = QDir::currentPath() ;
    QString databaseLocation = databasePath +"/"+ databaseName ;
    if(!initDatabase(databaseLocation))
        return -1 ;

    MainWindow w;
    w.show();


    return a.exec();
}
bool initDatabase(QString databaseLocation)
{
    bool check = QSqlDatabase::isDriverAvailable("QSQLITE") ;
    if( !check )qDebug()<<"erreur bdd 1";
    bdd = QSqlDatabase::addDatabase("QSQLITE");
    bdd.setDatabaseName(databaseLocation);

    bool ok = bdd.open();
    if ( !ok ) qDebug()<<"erreur bdd 2";

    return ok ;
}
