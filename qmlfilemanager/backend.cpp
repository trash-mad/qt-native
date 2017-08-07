#include "backend.h"
#include <QDebug>
#include <QStringList>
#include <QStandardPaths>
#include <QList>
#include <QSysInfo>

#include <QProcess>

BackEnd::BackEnd(){

    //Получение rootpath
    #if defined(Q_OS_ANDROID)
    rootpath=getenv("EXTERNAL_STORAGE");
    #elif defined(Q_OS_WIN)
    rootpath="C:\\";
    #else
    rootpath=QDir::homePath();
    #endif

    path.setPath(rootpath);

}


QString BackEnd::getDir(QString command){
qDebug() << path.absolutePath();
bool rp;
QString xml="<root>";

QString::compare(path.absolutePath(), rootpath, Qt::CaseSensitive)==0?rp=true:rp=false;
if((QString::compare(command, "/up", Qt::CaseSensitive))==0&&!rp) path.cdUp();
else if((QString::compare(command, "/list", Qt::CaseSensitive)!=0)) path.cd(command);
QFileInfoList files=path.entryInfoList();
foreach (QFileInfo file, files){
    if((QString::compare(file.fileName(), ".", Qt::CaseSensitive)!=0)&&(QString::compare(file.fileName(), "..", Qt::CaseSensitive)!=0)){
    xml+="<item>";
        if (file.isDir()){
            xml+="<type>Dir</type>";
        }
        else{
           xml+="<type>File</type>";
        }
        xml+="<name>"+file.fileName()+"</name></item>";
    }
}
xml+="</root>";
return xml;
}
