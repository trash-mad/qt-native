#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QUrl>

#include "backend.h"


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQuickView viewer;

    viewer.setTitle(QStringLiteral("FairFun"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    BackEnd backend(viewer);

    viewer.rootContext()->setContextProperty("backEnd", &backend);

    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    viewer.setSource(QUrl("qrc:/main.qml"));

    viewer.show();
    return app.exec();
}
