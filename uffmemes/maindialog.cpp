#include "maindialog.h"


void MainDialog::setupUi(QWidget *Form)
   {
       if (Form->objectName().isEmpty())
           Form->setObjectName(QStringLiteral("Form"));
       Form->resize(359, 430);
       verticalLayout = new QVBoxLayout(Form);
       verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
       verticalLayout->setContentsMargins(0, 0, 0, 5);
       frame = new QFrame(Form);
       frame->setObjectName(QStringLiteral("frame"));
       frame->setMinimumSize(QSize(0, 75));
       frame->setStyleSheet(QLatin1String("#frame{ background-color: #00897b; color: white;\n }"));
       frame->setFrameShape(QFrame::StyledPanel);
       frame->setFrameShadow(QFrame::Raised);
       horizontalLayout = new QHBoxLayout(frame);
       horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
       horizontalLayout->setContentsMargins(9, 9, 9, 9);
       label = new QLabel(frame);
       label->setObjectName(QStringLiteral("label"));
       label->setStyleSheet(QStringLiteral("color: white;"));

       label = new QLabel(frame);
       label->setObjectName(QStringLiteral("label"));
       label->setStyleSheet(QStringLiteral("color: white;"));

       horizontalLayout->addWidget(label);

       horizontalSpacer = new QSpacerItem(202, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

       horizontalLayout->addItem(horizontalSpacer);

       pushButton = new QPushButton(frame);
       pushButton->setStyleSheet("border-image: url(:/renew.png)");

       pushButton_2 = new QPushButton(frame);
       pushButton_2->setStyleSheet("border-image: url(:/about.png)");

       horizontalLayout->addWidget(pushButton);
       horizontalLayout->addWidget(pushButton_2);

       verticalLayout->addWidget(frame);

       scrollArea = new QScrollArea(Form);
       scrollArea->setObjectName(QStringLiteral("scrollArea"));
       scrollArea->setWidgetResizable(true);
       scrollAreaWidgetContents = new QWidget();
       scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
       scrollAreaWidgetContents->setGeometry(QRect(0, 0, 357, 347));
       gridLayout = new QGridLayout(scrollAreaWidgetContents);
       gridLayout->setObjectName(QStringLiteral("gridLayout"));
       scrollArea->setWidget(scrollAreaWidgetContents);

       verticalLayout->addWidget(scrollArea);


       label->setText("УффМемы");
       label->setStyleSheet("font: 12pt/10pt sans-serif;");

       connect(pushButton,SIGNAL(clicked(bool)),this,SLOT(update()));

       addButton = new QPushButton(Dialog);
       addButton->setMaximumSize(QSize(65,70));
       addButton->setMinimumSize(QSize(65,70));
       addButton->setText("+");
       gridLayout->addWidget(addButton);
       connect(addButton,SIGNAL(clicked(bool)),this,SLOT(addItem()));
   }

MainDialog::MainDialog(QObject *parent) : QObject(parent){
    Dialog=new QDialog();
    setupUi(Dialog);



    update();

    #ifdef Q_OS_ANDROID
    Dialog->showFullScreen();
    #else
    Dialog->show();
#endif
}

void MainDialog::addItem(){
    qDebug() << "ok";

    QDir folder(folderpath);

    QString path=QFileDialog::getOpenFileName(NULL, "Выберите картинку", QDir::homePath(), "Мемасик (*.png; *.jpeg; *.gif; *.jpg; *.bmp)");
    if (QFile::exists(path))
    {
        QFile::copy(path,folder.absolutePath()+"/"+QFileInfo(QFile(path).fileName()).fileName());
        update();
    }
    else{
        QMessageBox msg;
        msg.setText("Браток, не могу скопировать. Давай сам, вот тебе путь: "+folder.absolutePath());
        msg.exec();
    }



}


void MainDialog::update(){
    int i,j,k=0;

    qDebug() << "_____________________________________________________________";
    qDebug() << QVariant(oldlenght);
    if(oldlenght!=-1){
        int oldlenghtbuf=oldlenght;
        for(int i=0;i<oldlenghtbuf;++i){
           disconnect(diarray[i],SIGNAL(needupdate()),this,SLOT(update()));
           qDebug() << QVariant(oldlenght);
           delete diarray[i];
           oldlenght--;
    }
    }



    disconnect(addButton,SIGNAL(clicked(bool)),this,SLOT(addItem()));
    delete addButton;


    QDir folder(folderpath);
    QStringList filepaths;
    QStringList filenames;

    QFileInfoList files=folder.entryInfoList();
    foreach (QFileInfo file, files){
        if(QString::compare(file.fileName(), ".", Qt::CaseSensitive)==0) continue;
        if(QString::compare(file.fileName(), "..", Qt::CaseSensitive)==0) continue;
        if(file.isDir()) continue;
        //qDebug() << file.filePath();
        filepaths << file.filePath();
        filenames << file.fileName();
    }

    if(filepaths.length()!=0){
    diarray = new DropItem*[filepaths.length()];
    oldlenght=filepaths.length();






    if(filepaths.length()<=Settings::listW){
        i=0;
        for(j=0;j<filepaths.length(); j++){
            diarray[k] = new DropItem(Dialog);
            gridLayout->addWidget(diarray[k], i, j);
            diarray[k]->setMaximumSize(QSize(65,70));
            diarray[k]->setName(filenames.at(k));
            diarray[k]->setPath(filepaths.at(k));
            connect(diarray[k],SIGNAL(needupdate()),this,SLOT(update()));
            k++;
        }
    }
    else{
        for(i=0;i<ceil((double)filepaths.length()/Settings::listW);i++)
        for(j=0;j<Settings::listW;j++){
            if(k==filepaths.length()) break;

            diarray[k] = new DropItem(Dialog);
            gridLayout->addWidget(diarray[k], i, j);
            diarray[k]->setMaximumSize(QSize(65,70));
            diarray[k]->setName(filenames.at(k));
            diarray[k]->setPath(filepaths.at(k));
            connect(diarray[k],SIGNAL(needupdate()),this,SLOT(update()));

            k++;
        }


    }


    }
    //Добавление кнопки добавить

    if(j>Settings::listW-1){
        j=0;
        i++;
    }
    else{
        if(i>0) i--;
    }

    addButton = new QPushButton(Dialog);
    addButton->setMaximumSize(QSize(65,70));
    addButton->setMinimumSize(QSize(65,70));
    addButton->setText("+");
    if(k!=0) gridLayout->addWidget(addButton, i, j);
    else gridLayout->addWidget(addButton);
    connect(addButton,SIGNAL(clicked(bool)),this,SLOT(addItem()));

}

