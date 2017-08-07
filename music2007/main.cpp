#include <QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QSettings>

#include <QThread>
#include <QStandardPaths>


#include "musicstorage.h"
#include "backend.h"
#include "fileserver.h"
#include "fileclient.h"
#include "musicplayer.h"


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setOrganizationName("PetrSoft");
    QApplication::setOrganizationDomain("tripolskypetr.github.io");
    QApplication::setApplicationName("Music2007");
    QApplication app(argc, argv);

    QSettings settings;
    /*if(settings.value("muspath","none").compare("none")==0)*/
    settings.setValue("muspath",QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::MusicLocation);

    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);

    BackEnd backend;
    backend.setViewer(viewer);
    viewer.rootContext()->setContextProperty("backEnd", &backend);

    //Регистрация своих типов
    qRegisterMetaType<MusicList>("MusicList");
    qRegisterMetaType<LocalList>("LocalList");


    //Соединение сигналов и слотов
    MusicStorage *ms = new MusicStorage;
    QThread *mst=new QThread();
    ms->moveToThread(mst);
    mst->start();

    FileClient *fc=new FileClient();
    QThread *fct=new QThread();
    fc->moveToThread(fct);
    fc->run(fct);
    fct->start();

    FileServer *fs=new FileServer;
    QThread *fst=new QThread();
    fs->moveToThread(fst);
    fst->start();

    MusicPlayer *mp = new MusicPlayer;
    QThread *mpt=new QThread();
    mp->moveToThread(mpt);
    mpt->start();


    QObject::connect(ms,SIGNAL(needupdate(MusicList)),fs,SLOT(updatelist(MusicList)));
    QObject::connect(ms,SIGNAL(needupdate(MusicList)),&backend,SLOT(updatemuslist(MusicList)));
    QObject::connect(ms,SIGNAL(needupdate(MusicList)),mp,SLOT(updatelist(MusicList)));
    QObject::connect(fc,SIGNAL(needupdate(LocalList)),&backend,SLOT(updatehostlist(LocalList)));

    QObject::connect(&backend,SIGNAL(playpausesignal(int)),mp,SLOT(playpause(int)));
    QObject::connect(&backend,SIGNAL(prevsignal()),mp,SLOT(prev()));
    QObject::connect(&backend,SIGNAL(nextsignal()),mp,SLOT(next()));


    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
    viewer.setSource(QUrl("qrc:/qml/player/main.qml"));
    viewer.show();

    return app.exec();
}
