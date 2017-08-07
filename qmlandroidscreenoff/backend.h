#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QAndroidJniObject>

class BackEnd : public QObject
{
Q_OBJECT
bool isRunning=false;
public:
BackEnd();

public slots:
QString callJava();
};

#endif // BACKEND_H
