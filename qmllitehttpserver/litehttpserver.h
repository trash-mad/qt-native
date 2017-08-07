#ifndef LITEHTTPSERVER_H
#define LITEHTTPSERVER_H
#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>

class BackEnd;

class litehttpserver : public QObject
{
Q_OBJECT

QTcpServer *tcpServer;
BackEnd *parent;
int server_status;
int port;
QMap<int,QTcpSocket *> SClients;


public:
    litehttpserver(int p);
    void setBackend(BackEnd &p);

public slots:
    void startServer();
    void stopServer();
    void newConnection();
    void ReadClient();

};

#endif // LITEHTTPSERVER_H
