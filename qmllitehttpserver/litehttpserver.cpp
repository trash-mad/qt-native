#include "litehttpserver.h"
#include "backend.h"
#include <QString>
#include <QFile>

litehttpserver::litehttpserver(int p)
{
    port=p;
}

void litehttpserver::setBackend(BackEnd &p)
{
    parent=&p;
}

void litehttpserver::startServer()
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!tcpServer->listen(QHostAddress::Any, port) && server_status==0) {
       server_status=0;
       parent->addLog(QString("Error, this port in use\n"));
    } else {
        server_status=1;
        parent->addLog(QString("Server started\n"));
    }
}

void litehttpserver::stopServer()
{
    if(server_status==1){
        foreach(int i,SClients.keys()){
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
        tcpServer->close();
        parent->addLog("Server stoped\n");
        server_status=0;
    }
}


void litehttpserver::newConnection()
{
    QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(ReadClient()));
}

void litehttpserver::ReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QString request;
    QString returntoclient;


    //чтение полученых данных
    while (clientSocket->bytesAvailable())
    {
           QString tmp= clientSocket->readAll();
           request=tmp.split(" ").at(1);
           qDebug() << "in " << tmp.split(" ").at(1);
    }
    qDebug() << "all ";

    if(request.compare("/")==0){
    request="/index.html";
    }

    QFile thisFile(QString(":")+request);

    if(!thisFile.open(QFile::ReadOnly | QFile::Text)){
    qDebug() << "Return 404";
    }
    else{
    QTextStream in(&thisFile);
    returntoclient = in.readAll();
    thisFile.close();
    }



    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    os << "HTTP/1.0 200 Ok\r\n";
    os << "Content-Type: text/html; charset=\"utf-8\"\r\n";
    os << "\r\n";
    os << returntoclient;
    os << "\n";
    clientSocket->close();
    SClients.remove(idusersocs);
}
