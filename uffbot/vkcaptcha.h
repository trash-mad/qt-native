#ifndef VKCAPTCHA_H
#define VKCAPTCHA_H

#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QPointer>

class VkCaptcha : public QObject
{
Q_OBJECT
QVBoxLayout *verticalLayout;
QLabel *captcha;
QPushButton *sendcaptcha;
QLineEdit *lineEdit;
QPointer<QDialog> dialog; //Обертка для указателя, на самом деле это QDialog *dialog
QString captcha_sid;
QString peer_id;
QString access_token;
QPointer<QNetworkAccessManager> manager; //Обертка для указателя, на самом деле это QNetworkAccessManager *manager

public:
explicit VkCaptcha(QObject *parent = 0);
~VkCaptcha();

signals:
    void sendData(QString url);
    void restartbot();
    void log(QString log);


public slots:
    void captchaEntered();
    void runCaptcha(QString sid,QString id,QString token);

private slots:
    void getResponse(QNetworkReply*);


};

#endif // VKCAPTCHA_H
