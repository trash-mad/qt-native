#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QAndroidJniObject>
#include <QString>
#include "filepicker.h"

class BackEnd : public QObject
{
Q_OBJECT
public:
FilePicker *fp;
BackEnd();
static QString filepath;
void ImageCopied(const QString &url){
emit sendToQml(url);
}

signals:
    void sendToQml(const QString &url);

public slots:
void getImages();
};

#endif // BACKEND_H
