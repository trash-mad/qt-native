#include "backend.h"



BackEnd::BackEnd(QObject *parent) : QObject(parent){

}

void BackEnd::setViewer(QQuickView &v){
viewer=&v;
}

void BackEnd::load(const QString str){
    QUrl url(str);
    QMetaObject::invokeMethod(this, "loadnewurl", Qt::QueuedConnection, Q_ARG(QUrl, url));
}

QString BackEnd::getFileList(const QString ip){
    qDebug() << "gfl";
    QTcpSocket *socket=new QTcpSocket;
    socket->connectToHost(ip,1488);
    if(!socket->waitForConnected(1000)){
        QMessageBox msg;
        msg.setText("Ошибка, хост недоступен");
        msg.exec();
        socket->disconnectFromHost();
        delete socket;
        load("qrc:/qml/player/main.qml");
    }
    else{
        QByteArray data=QByteArray::fromStdString(QString("-getlist ").toStdString());
        socket->write(data);
        socket->waitForBytesWritten();
        while(!socket->waitForReadyRead(1000)){} //Ждем пока будет доступно чтение
        QString request;
        while (socket->bytesAvailable())
        {
            request += socket->readAll();
        }
        qDebug() << request;
        return request;
    }
    return "error";
}

void BackEnd::playpause(const QString index)
{
    qDebug() << "playpause" << index;
    emit playpausesignal(index.toInt());
}

void BackEnd::next()
{
    emit nextsignal();
}

void BackEnd::prev()
{
    emit prevsignal();
}

void BackEnd::updatehostlist(LocalList list){
    qDebug() << "update";
    QString xml="<root>";
    foreach (LocalItem item, list) {
        xml+="<item><ip>"+item.ip+"</ip></item>";
    }
    xml+="</root>";
    hostxml=xml;
    emit updateHostList(xml);
}


void BackEnd::downloadfile(QString name,QString host,QString id){
    QSettings settings;
    SocketFileDownloader *dl=new SocketFileDownloader;
    connect(dl,SIGNAL(finished(QString)),this,SLOT(downloadfinished(QString)));
    dl->download(host,settings.value("muspath","C:/test").toString()+"/"+name+".mp3",1488,id.toInt());
}

void BackEnd::updatemuslist(QList<MusicItem> list){
    QString xml="<root>";
    foreach (MusicItem item, list) {
        xml+="<item><name>"+item.name+"</name><path>"+item.path+"</path><id>"+QVariant(item.id).toString()+"</id></item>";
    }
    xml+="</root>";
    musxml=xml;
    emit updateMusList(xml);
}
