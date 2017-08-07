#include "fileserver.h"

void FileServer::stopServer(){
    if(server_status==1){
            foreach(int i,SClients.keys()){
                QTextStream os(SClients[i]);
                os.setAutoDetectUnicode(true);
                SClients[i]->close();
                SClients.remove(i);
            }
            tcpServer->close();
            qDebug() << "Server stoped\n";
            server_status=0;
    }
}


FileServer::FileServer(QObject *parent) : QObject(parent){
    startServer();
}


void FileServer::startServer()
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!tcpServer->listen(QHostAddress::Any, port) && server_status==0) {
       server_status=0;
       qDebug() << QString("Error, this port in use\n");
    } else {
        server_status=1;
        qDebug() << QString("Server started\n");
    }
}

void FileServer::newConnection(){
    QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(readClient()));
}

void FileServer::readClient(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QString request;
    QString returntoclient;


    //чтение полученых данных
    while (clientSocket->bytesAvailable())
    {
        request += clientSocket->readAll();
    }
    qDebug() << request;

    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    QStringList list;
    //парсер пропускает первый аргумент, так что учитываем
    list << " "  << request.split(" ");

    const  QCommandLineOption getfile("getfile", "get file", "1");
    const  QCommandLineOption isavailable("isavailable", "check file", "1");
    const  QCommandLineOption getlist("getlist", "get music list");
    const  QCommandLineOption ismusic2007("ismusic2007", "check app");
    parser.addOption(getfile);
    parser.addOption(ismusic2007);
    parser.addOption(getlist);
    parser.addOption(isavailable);
    parser.parse(list);

    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);


    //os << "lol";


    if(parser.isSet(isavailable)){
        const QString tmp = parser.value(isavailable);
        bool temp=false;
        foreach (MusicItem item, musiclist) {
            if(item.id==QVariant(tmp).toInt()){
                os << "true";
                temp=true;
                break;
            }
        }
        if(!temp)os << "false";
    }
    if(parser.isSet(getfile)){
        const QString id = parser.value(getfile);
        bool isExist=false;
        int number=-1;
        for(int i=0;i<musiclist.count();i++) {
            if(musiclist.at(i).id==QVariant(id).toInt()){
                isExist=true;
                number=i;
                break;
            }
        }
        if(isExist){
            QFile inputFile(musiclist.at(number).path);
            QByteArray read;
            inputFile.open(QIODevice::ReadOnly);
            while(1)
            {
            read.clear();
            read = inputFile.read(32768*8);
            qDebug() << "Read : " << read.size();
            if(read.size()==0)  break;
            qDebug() << "Written : " << clientSocket->write(read);
            clientSocket->waitForBytesWritten();
            read.clear();
            }
            inputFile.close();
            }

        }

    if(parser.isSet(ismusic2007)){
        os << "true";
    }
    if(parser.isSet(getlist)){
        QString xml="<root>";
        foreach(MusicItem item, musiclist){
            xml+="<item><name>"+item.name+"</name><id>"+QVariant(item.id).toString()+"</id></item>";
        }
        xml+="</root>";

        QByteArray ba;
        ba=xml.toLatin1();

        os << ba.data();
    }


    //clientSocket->close();
    SClients.remove(idusersocs);
}

void FileServer::updatelist(MusicList list){
    musiclist.clear();
    foreach (MusicItem item, list) {
        musiclist.append(item);
    }
}
