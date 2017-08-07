#ifndef VKREADER_H
#define VKREADER_H

#include <QObject>
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDateTime>
#include <QDate>
#include <QInputDialog>
#include <windows.h>

#include <QPointer>

#include "vkmessageparser.h"

class VkReader : public QObject
{
Q_OBJECT
QPointer<VkMessageParser> parser; //VkMessageParser *parser с оберткой
QPointer<QNetworkAccessManager> messagewatchdog; //QNetworkAccessManager *messagewatchdog с оберткой
QPointer<QNetworkAccessManager> datasender; //QNetworkAccessManager *datasender с оберткой
QString access_token;
QString peer_id;

QString userid;

//Если появится капча можно поюзать как симафор
bool isrunning=true;

//Пауза между проверками сообщения
int timeout=1000;

//Время приёма последнего сообщения, для ограничения повторений
int lastdate=0;

public:
    explicit VkReader(QObject *parent = 0);
    ~VkReader();

    void setMessageParser(VkMessageParser &p){
        parser=&p;
    }

    void log(QString log){
        emit addLog(log);
    }

    QString getToken(){
        return access_token;
    }

    QString getPeer(){
        return peer_id;
    }

    void setNetworkAccessManager(QNetworkAccessManager &mwd, QNetworkAccessManager &ds);

signals:
    void addLog(QString log);
    void choosePeer(QString token);
    void runCaptcha(QString sid,QString id,QString token);


private:
    void checkChat();

public slots:
    void setToken(QString token);
    void setPeer(QString peer);
    void restartbot();

    //Для отправки сообщений
    void sendData(QString param);
    void getResponse(QNetworkReply *reply);

private slots:
    void messagewatchdogcycle();
    //void exit();


};

#endif // VKREADER_H
