#ifndef FILECLIENT_H
#define FILECLIENT_H

/*
 * Класс С++, осуществляющий сканирование локальной сети
 *
 * Он не запускает получение списка файлов или загрузку, только мониторинг
 *
 */


#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QNetworkInterface>
#include <QByteArray>

#include <musicstorage.h>

struct LocalItem{
    QString ip="192.168.1.1";
};

typedef QList<LocalItem> LocalList;

class FileClient : public QObject
{
Q_OBJECT

QTcpSocket *socket;
QTimer *timer;
LocalList iplist;
QString host; //Текущий хост, к которому подключаемся
int port=1488;
bool isNeedUpdate=true;
bool isScanRunning=false;

public:
    explicit FileClient(QObject *parent = 0);
    void run(QThread *p); //Конструктор вызывается в одном потоке, после класс переносится в другой. Придется создавать элементы тут
    ~FileClient();

signals:
    void needupdate(LocalList list);

public slots:
    void scanwifi();
    void ReadyRead();
    void Connected();
};

#endif // FILECLIENT_H
