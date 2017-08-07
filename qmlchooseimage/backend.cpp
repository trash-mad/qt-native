#include "backend.h"
#include <QDebug>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QString>
#include <QAndroidActivityResultReceiver>

BackEnd::BackEnd(){
}



void BackEnd::getImages(){

    QAndroidJniObject intent = QAndroidJniObject::callStaticObjectMethod(
                    "com/example/getimage/fetch/FetchClass",
                    "createChooseImageIntent",
                    "()Landroid/content/Intent;");

    const int REQUEST_CODE = 42;
    QtAndroid::startActivity(intent, REQUEST_CODE, fp);
}
