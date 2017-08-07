#include "musicstorage.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

MusicStorage::MusicStorage(QObject *parent) : QObject(parent){
    itemlist << scanlocalstorage(settings.value("muspath","C:/test").toString());
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updatelist()));
    timer->start(15000);
}

QList<MusicItem> MusicStorage::getList(){
    isReading=true;
    foreach (MusicItem item, itemlist) {
        qDebug() << item.path;
    }
    isReading=false;
    return itemlist;
}

QString MusicStorage::getXmlList(){
    isReading=true;
    QString xmllist="<root>";
    foreach (MusicItem item, itemlist) {
        xmllist+="<item><name>"+item.name+"</name><path>"+item.path+"</path><id>"+item.id+"</id></item>";
    }
    xmllist+="</root>";
    isReading=false;
    return xmllist;
}

QList<MusicItem> MusicStorage::scanlocalstorage(QString path){
QDir dir(path);
QList<MusicItem> templist;
foreach( QFileInfo fi, dir.entryInfoList())
{
QString fn = fi.absoluteFilePath();
if( fi.isDir())
{
if( fi.fileName()=="." || fi.fileName()=="..") continue;
templist << scanlocalstorage(fn);
}
if( fi.isFile() && (fi.fileName().indexOf(".mp3",Qt::CaseInsensitive)!=-1))
{
MusicItem item;
item.setValue(fi.fileName(),fi.absoluteFilePath(),1);
templist.append(item);
}
}
return templist;
}

void MusicStorage::updatelist(){
    if(isReading) return;
    QList<MusicItem> templist;
    templist << scanlocalstorage(settings.value("muspath","C:/test").toString());
    itemlist.clear();
    itemlist << templist;
}
