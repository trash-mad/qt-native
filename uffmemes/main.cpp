#include "maindialog.h"
#include <QApplication>
#include <QTime>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("tripolskypetr");
    QApplication::setOrganizationDomain("github.com/tripolskypetr");
    QApplication::setApplicationName("ZS_Share");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainDialog md;


    return a.exec();
}
