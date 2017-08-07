#include "backend.h"
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QString>

#include <QDebug>

BackEnd::BackEnd(){
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject::callStaticObjectMethod("com/example/proximitywakelock/wakelock/WLenabler", "setWakelock", "(Landroid/app/Activity;)Ljava/lang/String;", activity.object<jobject>());
}


QString BackEnd::callJava(){
QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
QAndroidJniObject r;

if(isRunning){
r=QAndroidJniObject::callStaticObjectMethod("com/example/proximitywakelock/wakelock/WLenabler", "stopWakelock", "(Landroid/app/Activity;)Ljava/lang/String;", activity.object<jobject>());
}
else{
r=QAndroidJniObject::callStaticObjectMethod("com/example/proximitywakelock/wakelock/WLenabler", "startWakelock", "(Landroid/app/Activity;)Ljava/lang/String;", activity.object<jobject>());
}
isRunning=!isRunning;
return r.toString();;
}



