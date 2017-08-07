#include "backend.h"
#include <QAndroidJniObject>
#include <QtAndroid>

BackEnd::BackEnd(QQuickView &v){
    viewer=&v;
}

QString BackEnd::getApplist(){
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject str = QAndroidJniObject::callStaticObjectMethod("com/example/qmllauncher/worker/AppWorker", "getApplist", "(Landroid/app/Activity;)Ljava/lang/String;", activity.object<jobject>());

    qDebug() << "Value from java is " << str.toString();
    return str.toString();
}

void BackEnd::runApp(QString ID){
    qDebug() << ID;

    QAndroidJniObject string = QAndroidJniObject::fromString(ID);
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject intent =QAndroidJniObject::callStaticObjectMethod("com/example/qmllauncher/worker/AppWorker", "getAppIntent", "(Landroid/app/Activity;Ljava/lang/String;)Landroid/content/Intent;", activity.object<jobject>(), string.object<jstring>());
    QtAndroid::startActivity(intent,0);
}
