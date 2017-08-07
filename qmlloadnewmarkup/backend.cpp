#include "backend.h"
#include <QtQuick/QQuickView>

BackEnd::BackEnd(QQuickView &v){
viewer=&v;
}

void BackEnd::load(const QString str){
    QUrl url(str);
    QMetaObject::invokeMethod(this, "loadnewurl", Qt::QueuedConnection, Q_ARG(QUrl, url));
}
