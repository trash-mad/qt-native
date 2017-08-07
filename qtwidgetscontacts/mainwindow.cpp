#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fetch = new ContactsFetch();

    ui->lineEdit->setText(fetch->getContact(index).name);
    ui->lineEdit_2->setText(fetch->getContact(index).email);
    ui->lineEdit_3->setText(fetch->getContact(index).phone);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(index<fetch->lenght()){
        index++;
        ui->lineEdit->setText(fetch->getContact(index).name);
        ui->lineEdit_2->setText(fetch->getContact(index).email);
        ui->lineEdit_3->setText(fetch->getContact(index).phone);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(index>1){
        index--;
        ui->lineEdit->setText(fetch->getContact(index).name);
        ui->lineEdit_2->setText(fetch->getContact(index).email);
        ui->lineEdit_3->setText(fetch->getContact(index).phone);
    }
}
