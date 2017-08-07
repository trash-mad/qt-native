#include "backend.h"
#include "litehttpserver.h"

BackEnd::BackEnd(QQuickView &v){
    viewer=&v;
}

void BackEnd::addLog(QString str)
{
    log+=str;
}

void BackEnd::setServer(litehttpserver &s)
{
    server=&s;
}

void BackEnd::startServer()
{
server->startServer();
}

void BackEnd::stopServer()
{
server->stopServer();
}

QString BackEnd::getLog()
{
    return log;
}
