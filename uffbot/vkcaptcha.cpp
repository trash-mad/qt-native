#include "vkcaptcha.h"

VkCaptcha::VkCaptcha(QObject *parent) : QObject(parent){
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(getResponse(QNetworkReply*)));
    dialog=new QDialog;
    dialog->resize(290, 282);
    dialog->setWindowTitle("Captcha");
    verticalLayout = new QVBoxLayout(dialog);
    captcha = new QLabel(dialog);
    captcha->setAlignment(Qt::AlignCenter);
    verticalLayout->addWidget(captcha);
    lineEdit = new QLineEdit(dialog);
    verticalLayout->addWidget(lineEdit);
    sendcaptcha = new QPushButton(dialog);
    sendcaptcha->setText("Enter");
    verticalLayout->addWidget(sendcaptcha);
    dialog->setWindowFlags(Qt::WindowTitleHint);
    connect(sendcaptcha,SIGNAL(clicked(bool)),this,SLOT(captchaEntered()));
}

VkCaptcha::~VkCaptcha(){
    if(!dialog.isNull()) dialog.clear();
    if(!manager.isNull()) manager.clear();
}

void VkCaptcha::captchaEntered(){
    dialog->hide();
    emit sendData("https://api.vk.com/method/messages.send.xml?access_token="+access_token+"&peer_id="+peer_id+"&message=Бот выпал, прилетела каптча...&v=10&captcha_sid="+captcha_sid+"&captcha_key="+lineEdit->text());
    emit restartbot();
}

void VkCaptcha::getResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
    log("\nПотеря соединения при вводе каптчи. Повторная попытка");
    runCaptcha(captcha_sid,peer_id,access_token);
    return;
    }
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);
    captcha->setPixmap(pixmap);
    dialog->show();
    dialog->setFocus();
}

void VkCaptcha::runCaptcha(QString sid,QString id,QString token){
    captcha_sid=sid;
    peer_id=id;
    access_token=token;
    manager->get(QNetworkRequest(QUrl(QString("http://api.vk.com/captcha.php?sid="+captcha_sid+"&s=1"))));
}
