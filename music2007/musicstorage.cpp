#include "musicstorage.h"

#include <QDir>
#include <QDebug>

MusicStorage::MusicStorage(QObject *parent) : QObject(parent){
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkupdate()));
    timer->start(5000);
}

MusicStorage::~MusicStorage(){
    timer->disconnect(timer,SIGNAL(timeout()),this,SLOT(checkupdate()));
    timer->stop();
    timer->deleteLater();
}

int MusicStorage::scannewfiles(QString path){
QDir dir(path);
int updatecount=0;
foreach( QFileInfo fi, dir.entryInfoList())
{
    QString fn = fi.absoluteFilePath();
    if( fi.isDir())
    {
    if( fi.fileName()=="." || fi.fileName()=="..") continue;
        updatecount+=scannewfiles(fn);
    }

    bool isExist=false;
    for(int i=0;i<itemlist.count();i++)  if(QString::compare(itemlist.at(i).path, fi.absoluteFilePath())==0){
        isExist=true;

    }

    if( fi.isFile() && (fi.fileName().indexOf(".mp3",Qt::CaseInsensitive)!=-1) && !isExist)
    {
           updatecount++;
           musiccount++;
           MusicItem item;
           item.name=fi.fileName();
           item.path=fi.absoluteFilePath();
           item.id=musiccount;
           itemlist << item;

    }
}
return updatecount;
}

int MusicStorage::scanoldfiles(){
    int updatecount=0;
    for(int i=0;i<itemlist.count();i++){
            QFileInfo file(itemlist.at(i).path);
            if(!(file.exists() && file.isFile())){
                updatecount++;
                itemlist.removeAt(i);
            }
    }
    return updatecount;
}

void MusicStorage::checkupdate(){
    QSettings settings;
    //Проверяет наличие новых файлов. Кроме этого нужно удалить старые
    int ret=scannewfiles(settings.value("muspath","C:/test").toString())+scanoldfiles();

    if(ret>0) emit needupdate(itemlist);
    if(ret>0) qDebug() << QVariant(ret);

    return;
}
