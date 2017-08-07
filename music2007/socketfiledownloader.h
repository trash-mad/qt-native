#ifndef SOCKETFILEDOWNLOADER_H
#define SOCKETFILEDOWNLOADER_H

/*
 * Класс для скачивания музона. Следует создать экземпляр и вызвать метод downloa
 *
 */


#include <QObject>
#include <QTcpSocket>
#include <QFile>

class SocketFileDownloader : public QObject
{
Q_OBJECT

QTcpSocket *socket;
QString host;
QString path;
int port;
int id;

public:
    explicit SocketFileDownloader(QObject *parent = 0);
    void download(QString host, QString path, int port, int id);

signals:
    void finished();

public slots:
    void ReadyRead();
    void Connected();
    void Disconnected();
};

#endif // SOCKETFILEDOWNLOADER_H
