#include "vkreader.h"


QString getElementValue(QString xml,QString starttag,QString stoptag){
int startpos=xml.indexOf(starttag)+starttag.length();
int endpos=xml.indexOf(stoptag,startpos);
if(startpos==-1||endpos==-1) return "NoTAG!";
else return xml.mid(startpos,endpos-startpos);
}

int getType(QString xml){
    if(xml.indexOf("<type>sticker</type>")>-1) return -3;
    if(xml.indexOf("<action>chat_invite_user</action>")>-1) return -2;
    if(xml.indexOf("<action>chat_kick_user</action>")>-1) return -1;
    if(xml.indexOf("<error>")>-1) return 0;
    if(xml.indexOf("<body>")>-1) return 1;
    if(xml.indexOf("<response>")>-1) return 2;
    return 3;
}

VkReader::VkReader(QObject *parent) : QObject(parent){
    userid=QInputDialog::getText(NULL, "Введите id приложения", "Требуется id для игнорирования сообщений от бота. Введите.", QLineEdit::Normal, "420092478");
}

VkReader::~VkReader(){
    if(!messagewatchdog.isNull()) messagewatchdog.clear();
    if(!datasender.isNull()) datasender.clear();
    if(!parser.isNull()) parser.clear();
}


void VkReader::setNetworkAccessManager(QNetworkAccessManager &mwd, QNetworkAccessManager &ds){
    datasender = &ds;
    messagewatchdog = &mwd;
    connect(datasender, SIGNAL(finished(QNetworkReply*)),this, SLOT(getResponse(QNetworkReply*)));
    connect(messagewatchdog, SIGNAL(finished(QNetworkReply*)),this, SLOT(getResponse(QNetworkReply*)));
}

void VkReader::setToken(QString token){
    addLog("\nОтлично, вы вошли. Ваш токен:"+token);
    access_token=token;
    Sleep(1000);
    addLog("\nТеперь нужно выбрать беседу для засирания");
    Sleep(500);
    emit choosePeer(access_token);
}

void VkReader::setPeer(QString peer){
    peer_id=peer;
    addLog("\nОтлично, чат выбран. Его идентефикатор:"+peer);
    Sleep(1000);
    addLog("\nОтправляю тестовое сообщение в чат...");
    QString url="https://api.vk.com/method/messages.send.xml?access_token="+getToken()+"&peer_id="+getPeer()+"&message=УффБот подключился к беседе...&v=10";
    sendData(url);
    Sleep(1000);
    addLog("\nЗапускаю WatchDog");
    messagewatchdog->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.getHistory.xml?access_token="+getToken()+"&peer_id="+getPeer()+"&count=1&v=10")));
}

void VkReader::restartbot()
{
    log("\nПерезапуск бота...");
    isrunning=true;
    messagewatchdog->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.getHistory.xml?access_token="+getToken()+"&peer_id="+getPeer()+"&count=1&v=10")));
}

void VkReader::sendData(QString param){
datasender->get(QNetworkRequest(QUrl(param)));
}

void VkReader::getResponse(QNetworkReply *reply){
    //TODO: ПАРСИНГ ОШИБОК ВКОНТАКТЕ
    QString value=reply->readAll();
    delete reply;
    int type=getType(value);

    switch (type)  {
    case -3:{
        int thisdate=getElementValue(value,"<date>","</date>").toInt();
        if((thisdate>lastdate)&&(userid.compare(getElementValue(value,"<from_id>","</from_id>"),Qt::CaseInsensitive)!=0)){
        lastdate=thisdate;
        log("\nБраток скинул стикер");
        }
        if(isrunning) QMetaObject::invokeMethod(this, "messagewatchdogcycle", Qt::QueuedConnection);
        break;
    }
    case -2:{
        //Добавили братишку
        int thisdate=getElementValue(value,"<date>","</date>").toInt();
        if((thisdate>lastdate)&&(userid.compare(getElementValue(value,"<from_id>","</from_id>"),Qt::CaseInsensitive)!=0)){
        lastdate=thisdate;
        log("\nБратишку добавили: id"+getElementValue(value,"<action_mid>","</action_mid>"));
        }
        if(isrunning) QMetaObject::invokeMethod(this, "messagewatchdogcycle", Qt::QueuedConnection);
        break;
    }
    case -1:{
        //Кикнули братишку
        int thisdate=getElementValue(value,"<date>","</date>").toInt();
        if((thisdate>lastdate)&&(userid.compare(getElementValue(value,"<from_id>","</from_id>"),Qt::CaseInsensitive)!=0)){
        lastdate=thisdate;
        log("\nБратишку кикнули: id"+getElementValue(value,"<action_mid>","</action_mid>"));
        }
        if(isrunning) QMetaObject::invokeMethod(this, "messagewatchdogcycle", Qt::QueuedConnection);
        break;
    }

    case 0:{
        //ошибка/капча
        QString errorcode=getElementValue(value,"<error_code>","</error_code>");
        if(errorcode.toInt()==14){
           isrunning=false;
           emit runCaptcha(getElementValue(value,"<captcha_sid>","</captcha_sid>"),peer_id,access_token);
        }
        else{
           log("\nAPI VK ВЕРНУЛО ОШИБКУ "+errorcode);
           qDebug() << value;
        }
        break;
    }

    case 1:{
        int thisdate=getElementValue(value,"<date>","</date>").toInt();
        if((thisdate>lastdate)&&(userid.compare(getElementValue(value,"<from_id>","</from_id>"),Qt::CaseInsensitive)!=0)){
        lastdate=thisdate;
        QString text=getElementValue(value,"<body>","</body>");
        log("\nПринято сообщение <<"+text+">> date="+QString::number(lastdate));
        QString answer=parser->parseString(text);
                if(!answer.compare("NoMESSAGE!",Qt::CaseSensitive)==0){
                    qDebug()<<answer.compare("NoMESSAGE!",Qt::CaseSensitive);
                    sendData("https://api.vk.com/method/messages.send.xml?access_token="+getToken()+"&peer_id="+getPeer()+"&message="+answer+"&v=10");
        }
        }

        if(isrunning) QMetaObject::invokeMethod(this, "messagewatchdogcycle", Qt::QueuedConnection);
        break;
    }
    case 2:{
        //успешная отправка сообщения
        QString errorcode=getElementValue(value,"<response>","</response>");
        log("\nСообщение успешно доставлено. Код сообщения: "+errorcode);
        break;
    }
    default:{
        QMessageBox msg;
        msg.setText("\nAPI VK вернуло строку "+value+", продолжение работы невозможно!");
        qApp->exit();
        break;
    }
    }



}

void VkReader::messagewatchdogcycle(){
Sleep(500);
if(isrunning) messagewatchdog->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.getHistory.xml?access_token="+getToken()+"&peer_id="+getPeer()+"&count=1&v=10")));
}

