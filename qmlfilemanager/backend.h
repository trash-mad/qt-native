#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QDir>

class BackEnd : public QObject
{
Q_OBJECT

QDir path;
QString rootpath;

public:
BackEnd();

public slots:
QString getDir(QString command);

};

#endif // BACKEND_H
