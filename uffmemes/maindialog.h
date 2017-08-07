#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QObject>
#include <QDialog>
#include <QPointer>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QWidget>

#include <QFileInfoList>
#include <QDir>

#include <QFileDialog>

#include "dropitem.h"


#include "settings.cpp"

class MainDialog : public QObject
{
Q_OBJECT

QString folderpath="C:/memes";

QPointer<QDialog> Dialog;
QVBoxLayout *verticalLayout;
QFrame *frame;
QHBoxLayout *horizontalLayout;
QLabel *label;
QSpacerItem *horizontalSpacer;
QPushButton *pushButton;
QPushButton *pushButton_2;
QPushButton *addButton;
QScrollArea *scrollArea;
QWidget *scrollAreaWidgetContents;
QGridLayout *gridLayout;

DropItem **diarray;
int oldlenght=-1;


private:
    void setupUi(QWidget *Form);


public:
    explicit MainDialog(QObject *parent = 0);

signals:

public slots:
    void addItem();
    void update();

};

#endif // MAINDIALOG_H
