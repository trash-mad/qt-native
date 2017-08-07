#include "fileclient.h"

FileClient::FileClient(QObject *parent) : QObject(parent){

}

void FileClient::run(QThread *p){
    socket=new QTcpSocket();
    socket->moveToThread(p);
    socket->setParent(this->parent());
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    timer=new QTimer();
    //timer->moveToThread(p);
    timer->setParent(this->parent());
    connect(timer,SIGNAL(timeout()),this,SLOT(scanwifi()));
    timer->start(1000);
}

FileClient::~FileClient(){
    timer->disconnect(timer,SIGNAL(timeout()),this,SLOT(scanwifi()));
    timer->stop();
    timer->deleteLater();
}

void FileClient::scanwifi(){

    if(isScanRunning) return;
    isScanRunning=true;

    QString ip;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
    ip=address.toString();
    }

    QString localprefix=ip.split(".").at(0)+"."+ip.split(".").at(1)+"."+ip.split(".").at(2);

    for(int i=1;i<256;i++){

      host=localprefix+"."+QVariant(i).toString();
      socket->connectToHost(host,port);
      if(!socket->waitForConnected(1000)){
         //Порт недоступен, пропускаем. Проверяем, был ли хост в списке
         //qDebug() << "can't connect to "+host;
         for(int i=0;i<iplist.count();i++) {
             if(host==iplist.at(i).ip){
                 //Он в списке, но недоступен. Надо удалить
                 iplist.removeAt(i);
                 emit needupdate(iplist);
             }
         }
         socket->disconnectFromHost();
      }else{
         //Идет попытка подключения, надо сделать паузу
         while(!socket->waitForDisconnected(1000)){}
      }


    }



    isScanRunning=false;
}

void FileClient::ReadyRead(){
    QString request;
    while (socket->bytesAvailable())
    {
        request += socket->readAll();
    }
    if(request=="true"){
        //Наш клиент, стоит проверить базу
        qDebug() << host+" is music2007";
        bool isNewClient=true;
        foreach (LocalItem item, iplist) {
            if(host==item.ip) isNewClient=false;
        }

        if(isNewClient){
            LocalItem client;
            client.ip=host;
            iplist << client;
            emit needupdate(iplist);
        }


        socket->disconnectFromHost();
    }
}

void FileClient::Connected(){
    QByteArray data=QByteArray::fromStdString(QString("-ismusic2007 ").toStdString());
    socket->write(data);
    socket->waitForBytesWritten();
}
