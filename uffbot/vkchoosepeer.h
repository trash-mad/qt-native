#ifndef VKCHOOSEPEER_H
#define VKCHOOSEPEER_H


#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QPointer>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>


class VkChoosePeer : public QObject
{
Q_OBJECT
QPointer<QInputDialog> dialog; //Указатель на dialog
QPointer<QNetworkAccessManager> getpeer;
QString access_token;
QString peer_id;

QStringList peernames;
QStringList peerids;

public:
    explicit VkChoosePeer(QObject *parent = 0);
    ~VkChoosePeer();

public slots:
    void ChoosePeer(QString token);
    QString getToken();
    void peerChoosed(QString id);
    void getResponse(QNetworkReply *reply);


signals:
    void setPeer(QString id);

};

#endif // VKCHOOSEPEER_H
