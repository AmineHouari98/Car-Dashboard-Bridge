#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    timer =new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    ui->lineEditA->setStyleSheet("background-color:red;color:white;");
    ui->lineEditB->setStyleSheet("background-color:red;color:white;");
    ui->lineEditA->setText("No Client");
    ui->lineEditB->setText("No Client");



    server = new QTcpServer(this) ;
    if(!server->listen(QHostAddress::Any, tcpPort))
        qDebug() << "m_tcpServer : " + server->errorString() ;

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    currentData = new rowData;
    initializeTables();
    qDebug() << tables() ;
    ui->tableView->setModel(tModel);
    ui->tableView_2->setModel(tModel_2);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tModel->setTable(EnumTableSensors::tableName);

    tModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tModel->select();
    tModel_2->setTable(EnumTableGps::tableName);
    tModel_2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tModel_2->select();
    ui->tableView->hideColumn(EnumTableSensors::_00id);
    ui->tableView->hideColumn(EnumTableSensors::_07duree_demarrage_moteur);
    ui->tableView_2->hideColumn(EnumTableGps::_00id);
    ui->tableView->setSortingEnabled(true);
    ui->tableView_2->setSortingEnabled(true);


    timer->setInterval(5 *1000);//seconds


    currentData->vitesse_vehicule(0);
    currentData->altitude(0);
    currentData->latitude(35.6911100);
    currentData->longitude(-0.6416700);
    currentData->position_pedale_accelerateur(0);
    currentData->temperature_air_admission(0);
    currentData->temp_air_ambiante(0);
    currentData->temp_liquide_froidissement(0);
    currentData->regime_moteur(0);
    currentData->reservoir(0);
    currentData->temp_catalyseur(0);
    currentData->chargeMoteur(0);
    currentData->pression_atmospherique(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{
    if(clientA == nullptr)
    {
        clientA = server->nextPendingConnection();
        connect(clientA, SIGNAL(readyRead()), this, SLOT(readyReadA()));
        connect(clientA, SIGNAL(disconnected()), this, SLOT(disconnectedA()));
        qDebug() << "newConnection: " << clientA->peerAddress().toIPv4Address() ;
        ui->lineEditA->setStyleSheet("background-color:green;color:white;");

        ui->lineEditA->setText("Client A connected");

        QThread::msleep(1000);

        clientA->write(QString("connected").toLatin1());
        QThread::msleep(1000);

        //clientA->write(QString("sending").toLatin1());


        return ;
    }
    if(clientB == nullptr)
    {
        clientB = server->nextPendingConnection();
        connect(clientB, SIGNAL(readyRead()), this, SLOT(readyReadB()));
        connect(clientB, SIGNAL(disconnected()), this, SLOT(disconnectedB()));
        qDebug() << "newConnection: " << clientB->peerAddress().toString() ;
        ui->lineEditB->setStyleSheet("background-color:green;color:white;");
        ui->lineEditB->setText("Client B connected");

        QThread::msleep(1000);

        clientB->write(QString("connected").toLatin1());
        QThread::msleep(1000);

        //clientB->write(QString("sending").toLatin1());

        return ;
    }

}

void MainWindow::readyReadA()
{
    QByteArray data = clientA->readAll();
    qDebug() << "readyRead A: " << clientA->peerAddress().toString()
             <<  data;

    setTextOnUi("","","Received data from A");

    if(clientB != nullptr)
    {
        qDebug()<<"client A passed";
        setTextOnUi("","","Data redirected to B");

        //clientB->write(QString("sending").toLatin1());

        QThread::msleep(1000);

        clientB->write(data);

    }
    // if(!clientBisSending)
    refreshData(data);

    if(!timerStarted)
        timer->start();

}

void MainWindow::readyReadB()
{
    QByteArray data = clientB->readAll();
    qDebug() << "readyRead B: " << clientB->peerAddress().toString()
             <<  data;


    setTextOnUi("","","Received data from B");



    if(clientA != nullptr)
    {
        qDebug()<<"client B passed";

        setTextOnUi("","","Data redirected to A");
        //clientA->write(QString("sending").toLatin1());
        clientA->write(data);

    }
    // if(!clientIsSending)
    refreshData(data);
}

void MainWindow::onTimeOut()
{
    timerStarted=true;

    toDB();
}

void MainWindow::disconnectedA()
{
    qDebug() << "disconnected: " << clientA->peerAddress().toString() ;
    ui->lineEditA->setStyleSheet("background-color:red;color:white;");
    ui->lineEditA->setText("No Client");
    clientA = nullptr ;
    if(clientB==nullptr)
        timer->stop();
}

void MainWindow::disconnectedB()
{
    qDebug() << "disconnected: " << clientB->peerAddress().toString() ;
    ui->lineEditB->setStyleSheet("background-color:red;color:white;");
    ui->lineEditB->setText("No Client");
    clientB = nullptr ;
    if(clientA==nullptr)
        timer->stop();
}

void MainWindow::toDB()
{

    int row = tModel->rowCount();

    tModel->insertRow(row);

    tModel->setData(tModel->index(row, EnumTableSensors::_01Date),
                    getCurrentDateTime());
    tModel->setData(tModel->index(row, EnumTableSensors::_02charge_moteur),
                    currentData->chargeMoteur());

    tModel->setData(tModel->index(row, EnumTableSensors::_03temp_liquide_froidissement),
                    currentData->temp_liquide_froidissement());

    tModel->setData(tModel->index(row, EnumTableSensors::_04regime_moteur),
                    currentData->regime_moteur());

    tModel->setData(tModel->index(row, EnumTableSensors::_05vitesse_vehicule),
                    currentData->vitesse_vehicule());

    tModel->setData(tModel->index(row, EnumTableSensors::_06temperature_air_admission),
                    currentData->temperature_air_admission());


    tModel->setData(tModel->index(row, EnumTableSensors::_07duree_demarrage_moteur),
                    currentData->duree_demarrage_moteur());

    tModel->setData(tModel->index(row, EnumTableSensors::_08reservoir),
                    currentData->reservoir());

    tModel->setData(tModel->index(row, EnumTableSensors::_09pression_atmospherique),
                    currentData->pression_atmospherique());

    tModel->setData(tModel->index(row, EnumTableSensors::_10temp_catalyseur),
                    currentData->temp_catalyseur());

    tModel->setData(tModel->index(row, EnumTableSensors::_11temp_air_ambiante),
                    currentData->temp_air_ambiante());

    tModel->setData(tModel->index(row, EnumTableSensors::_12position_pedale_accelerateur),
                    currentData->position_pedale_accelerateur());


    if( !tModel->submitAll() ) msgCritical("insertion error 1", tModel->lastError().text());

    qDebug()<<"latitude : " + QString::number(currentData->latitude());
    qDebug()<<"longitude : " + QString::number(currentData->longitude());
    qDebug()<<"altitude : " + QString::number(currentData->altitude());

        int row_2 = tModel_2->rowCount();

        tModel_2->insertRow(row_2);

        tModel_2->setData(tModel->index(row_2, EnumTableGps::_01Date),
                          getCurrentDateTime());

        tModel_2->setData(tModel->index(row_2, EnumTableGps::_02longitude),
                          currentData->longitude());

        tModel_2->setData(tModel->index(row_2, EnumTableGps::_03latitude),
                          currentData->latitude());

        tModel_2->setData(tModel->index(row_2, EnumTableGps::_04altitude),
                          currentData->altitude());

        if( !tModel_2->submitAll() ) msgCritical("insertion error 2", tModel_2->lastError().text());


}

void MainWindow::refreshData(QString data)
{
    QStringList splitedData = data.split("///");
    QStringList dataValues;
    QString theData="";
    for(int i=0;i<splitedData.length();i++)
    {
        dataValues = splitedData.at(i).split("=");
        if(dataValues.length() < 2 ) continue ;
        theData=dataValues.at(1);
        if(dataValues.at(0)=="chargeMoteur")                        currentData->chargeMoteur(theData.toInt());
        if(dataValues.at(0)=="temp_liquide_froidissement")          currentData->temp_liquide_froidissement(theData.toInt());
        if(dataValues.at(0)=="regime_moteur")                       currentData->regime_moteur(theData.toInt());
        if(dataValues.at(0)=="vitesse_vehicule")                    currentData->vitesse_vehicule(theData.toInt());
        if(dataValues.at(0)=="temperature_air_admission")           currentData->temperature_air_admission(theData.toInt());
        if(dataValues.at(0)=="duree_demarrage_moteur")              currentData->duree_demarrage_moteur(theData.toInt());
        if(dataValues.at(0)=="reservoir")                           currentData->reservoir(theData.toInt());
        if(dataValues.at(0)=="pression_atmospherique")              currentData->pression_atmospherique(theData.toInt());
        if(dataValues.at(0)=="temp_catalyseur")                     currentData->temp_catalyseur(theData.toInt());
        if(dataValues.at(0)=="temp_air_ambiante")                   currentData->temp_air_ambiante(theData.toInt());
        if(dataValues.at(0)=="position_pedale_accelerateur")        currentData->position_pedale_accelerateur(theData.toInt());
        if(dataValues.at(0)=="longitude")                           currentData->longitude(theData.toFloat());
        if(dataValues.at(0)=="latitude")                            currentData->latitude(theData.toFloat());
        if(dataValues.at(0)=="altitude")                            currentData->altitude(theData.toFloat());
    }

}

void MainWindow::setTextOnUi(QString client, QString status, QString data)
{
    //    ui->plainTextEdit->setPlainText(
    //                ui->plainTextEdit->toPlainText()+"\n"

    //                +"<p style=\"color:green; \">"+client +" : </p>"
    //                +data


    //                );

    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText()+"\n"+data);




}
