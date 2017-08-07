#ifndef FILESERVER_H
#define FILESERVER_H

/*
 * Осуществляет раздачу музона. Ловит сигнал needupdate() и формирует xml, который отдает при запросе с локальной сети
 * Порт- константа, 1488
 *
 */


#include <QObject>
#include <QTcpServer>
#include <QTextStream>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include <QStringList>

#include <QCommandLineOption>
#include <QCommandLineParser>

#include "musicstorage.h"

class FileServer : public QObject
{
Q_OBJECT

QTcpServer *tcpServer;
QMap<int,QTcpSocket *> SClients;
int server_status;
int port=1488;

MusicList musiclist;

private:
    void stopServer();
    void startServer();

public:
    explicit FileServer(QObject *parent = 0);

signals:

public slots:
    void newConnection();
    void readClient();
    void updatelist(MusicList list);
};

#endif // FILESERVER_H
