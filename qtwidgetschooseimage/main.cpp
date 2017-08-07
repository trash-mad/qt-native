#include "mainwindow.h"
#include "fp.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;

    FP fp;
    fp.parent=&w;
    w.fp=&fp;

    w.show();



    return a.exec();
}
