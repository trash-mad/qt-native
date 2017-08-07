#include "filepicker.h"
#include "backend.h"
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QDebug>

FilePicker::FilePicker(){
}

void FilePicker::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
{
    qDebug() << "Started";
    const int REQUEST_CODE = 42;
    const int RESULT_OK = -1;

    if (receiverRequestCode == REQUEST_CODE && resultCode == RESULT_OK) {

        QAndroidJniObject imageUri = data.callObjectMethod(
                    "getData",
                    "()Landroid/net/Uri;");

        QAndroidJniObject imageFile = QAndroidJniObject::callStaticObjectMethod(
                    "com/example/getimage/fetch/FetchClass",
                    "getFilePath",
                    "(Landroid/content/Context;Landroid/net/Uri;)Ljava/lang/String;",
                    QtAndroid::androidActivity().object<jobject>(),
                    imageUri.object<jobject>());

        qDebug() << "Check FilePicker class, handleActivityResult function";
        qDebug() << imageFile.toString();
        parent->ImageCopied(imageFile.toString());
    }
}
