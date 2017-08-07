#include "guiwindow.h"


GuiWindow::GuiWindow(){
Dialog=new QDialog();
setupUi(Dialog);
Dialog->show();
}

GuiWindow::~GuiWindow(){
delete Dialog;
}

void GuiWindow::addLog(QString log){
    textoutput->setText(textoutput->toPlainText()+log);
    QScrollBar *sb = textoutput->verticalScrollBar();
    sb->setValue(sb->maximum());
}


void GuiWindow::setupUi(QDialog *Dialog){
if (Dialog->objectName().isEmpty())
Dialog->setObjectName(QStringLiteral("Dialog"));
Dialog->resize(400, 300);
verticalLayout = new QVBoxLayout(Dialog);
verticalLayout->setContentsMargins(0, 0, 0, 0);
textoutput = new QTextBrowser(Dialog);
textoutput->setStyleSheet(QLatin1String("background-color: black;\n color: white;"));
verticalLayout->addWidget(textoutput);
}
