#ifndef VKAUTH_H
#define VKAUTH_H

#include <QObject>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QUrl>
#include <QUrlQuery>

#include <QPointer>

class VkAuth : public QObject
{
Q_OBJECT
QPointer<QWebEngineView> viewer; //Обертка для QWebEngineView *viewer;
QString access_token;
QVariant id=5915208;

private slots:
void checkUrl();


public:
explicit VkAuth(QObject *parent = 0);
~VkAuth();
void Auth();


signals:
void authcompleted(QString token);

public slots:
};

#endif // VKAUTH_H
