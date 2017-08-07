#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtQuick/QQuickView>

class BackEnd : public QObject
{
Q_OBJECT

QQuickView *viewer;

public:
BackEnd(QQuickView &v);


public slots:
void load(const QString str);

private slots:
void loadnewurl(const QUrl &url){
viewer->setSource(url);
}
};

#endif // BACKEND_H
