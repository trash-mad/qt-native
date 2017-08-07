#ifndef BACKEND_H
#define BACKEND_H

/*
 * Данный класс реализует взаимодействие с GUI. Только ловит сигналы внешних классов, преобразует структуры данных в xml и дает в qml
 * Ну и обратно.
 * Не стоит пихать воспроизведение музыки и подобное: это сделает код нечитаемым(уже, стоило следить за табуляциями, лол)
 * По задумке он еще отдает и пишет информацию в QSettings, но не более
 *
 */

#include <QObject>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QQmlProperty>
#include <QVariant>
#include <QTcpSocket>
#include <QMessageBox>
#include <QSettings>
#include "musicstorage.h"
#include "fileclient.h"
#include "socketfiledownloader.h"

class BackEnd : public QObject
{
Q_OBJECT

QQuickView *viewer;
QString selectedhost="127.0.0.1";

QString hostxml;
QString musxml;

public:
    explicit BackEnd(QObject *parent = 0);
    void setViewer(QQuickView &v);

signals:
    void updateMusList(QString xml); //Нужен для отправки xml в qml
    void updateHostList(QString xml);

    void playpausesignal(int index); //Управление плеером
    void nextsignal();
    void prevsignal();

public slots:
    void updatemuslist(MusicList list); //нужен для получения структуры и конвертации в xml
    void updatehostlist(LocalList list);
    void update(){
        emit updateMusList(musxml);
        emit updateHostList(hostxml);
    }

    void downloadfile(QString name,QString host,QString id);

    void load(const QString str); //подгрузить другой qml файл

    QString getFileList(const QString ip);

    void setSelectedHost(const QString ip){
        selectedhost=ip;
    }

    QString getSelectedHost(){
        return selectedhost;
    }

    void playpause(const QString index); //Управление плеером
    void next();
    void prev();



private slots:
    void loadnewurl(const QUrl &url){
       viewer->setSource(url);
    }
};

#endif // BACKEND_H
