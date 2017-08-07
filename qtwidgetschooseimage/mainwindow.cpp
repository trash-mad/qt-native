#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fp.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QtAndroid>
#include <QString>
#include <QByteArray>
#include <QtAndroidExtras/QAndroidActivityResultReceiver>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    QAndroidJniObject intent = QAndroidJniObject::callStaticObjectMethod(
                       "com/example/qtwidgetschooseimage/fetch/FetchClass",
                       "createChooseImageIntent",
                       "()Landroid/content/Intent;");

    qDebug() << "ok";

     const int REQUEST_CODE = 42;

    //if (intent.isValid())
        QtAndroid::startActivity(intent, REQUEST_CODE,fp);
    //else
    //    qWarning() << "Unable to resolve activity";

}

void MainWindow::setBase64(QString b){
    //ui->label->setText(b);
    QByteArray by = QByteArray::fromBase64(b.toUtf8());
    QImage image = QImage::fromData(by, "JPEG");
    ui->label->setPixmap(QPixmap::fromImage(image));
}
