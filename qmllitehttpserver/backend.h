#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQuickView>
#include <QString>

class litehttpserver;

class BackEnd : public QObject
{
Q_OBJECT

QQuickView *viewer;
litehttpserver *server;
QString log;

public:
BackEnd(QQuickView &v);
void addLog(QString str);
void setServer(litehttpserver &s);

signals:

public slots:
    void startServer();
    void stopServer();
    QString getLog();
};

#endif // BACKEND_H
