#include "socketfiledownloader.h"
#include <QDataStream>
SocketFileDownloader::SocketFileDownloader(QObject *parent) : QObject(parent){
    socket=new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(Disconnected()));
}

void SocketFileDownloader::download(QString host, QString path, int port, int id){
    this->host=host;
    this->path=path;
    this->port=port;
    this->id=id;
    socket->connectToHost(host,port);
}

void SocketFileDownloader::Disconnected(){
    emit finished();
}

void SocketFileDownloader::ReadyRead()
{
       QFile file(path);
       if(!(file.open(QIODevice::Append)))
       {
           qDebug("File cannot be opened.");
           exit(0);
       }
       QByteArray read = socket->read(socket->bytesAvailable());
       qDebug() << "Read    : " << read.size();
       file.write(read);
       file.close();

}

void SocketFileDownloader::Connected()
{
    qDebug() << "con";
    QByteArray data=QByteArray::fromStdString(QString("-getfile "+QVariant(id).toString()).toStdString());
    //socket->write(IntToArray(data.size()));
    socket->write(data);
    socket->waitForBytesWritten();
}

