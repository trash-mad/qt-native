#include "vkchoosepeer.h"
#include <QDesktopServices>
#include <QInputDialog>

struct Chat{
    QString title = "null";
    int id = 0;
};

QString cut(QString text, int from=0){
    int startpos=text.indexOf("<message>", from);
    int endpos=text.indexOf("</message>", startpos)+10;
    return text.mid(startpos,endpos-startpos);
}

QString getPeerElementValue(QString xml,QString starttag,QString stoptag){
int startpos=xml.indexOf(starttag)+starttag.length();
int endpos=xml.indexOf(stoptag,startpos);
if(startpos==-1||endpos==-1) return "NoTAG!";
else return xml.mid(startpos,endpos-startpos);
}

Chat parse(QString text){
    Chat r;

    QString title=getPeerElementValue(text,"<title>","</title>");
    QString chatid=getPeerElementValue(text,"<chat_id>","</chat_id>");
    QString uid=getPeerElementValue(text,"<user_id>","</user_id>");
    if(chatid.compare("NoTAG!",Qt::CaseSensitive)!=0){
        //Конфа
        r.id=2000000000+chatid.toInt();
        r.title=title;
    }
    else{
        //Лс
        r.id=uid.toInt();
        r.title="id"+uid;
    }


    return r;
}

VkChoosePeer::VkChoosePeer(QObject *parent) : QObject(parent){
getpeer=new QNetworkAccessManager(this);
connect(getpeer, SIGNAL(finished(QNetworkReply*)),this, SLOT(getResponse(QNetworkReply*)));
}

void VkChoosePeer::getResponse(QNetworkReply *reply){
    QString p=reply->readAll();
    delete reply;

    int count=getPeerElementValue(p,"<count>","</count>").toInt();
    int pos=p.indexOf("<message>");

    for(int i=0;i<count;i++){
    QString temp=cut(p,pos);
    pos=pos+temp.length();
    qDebug() << parse(getPeerElementValue(temp,"<message>","</message>")).title;
    peernames << parse(getPeerElementValue(temp,"<message>","</message>")).title;
    peerids << QVariant(parse(getPeerElementValue(temp,"<message>","</message>")).id).toString();
    }
   if((peernames.count()==peerids.count())&&!(peernames.count()>0)){
        QMessageBox msg;
        msg.setText("Не могу выбрать беседу. Произошла ошибка");
        msg.exec();
        qApp->exit();
    }

    bool accepted;
    QString item = dialog->getItem(0, "Title", "Label:", peernames, 0, false, &accepted);
    if (accepted && !item.isEmpty())  emit setPeer(peerids.at(peernames.indexOf(item)));
    else emit setPeer(peerids.at(0));

}

VkChoosePeer::~VkChoosePeer(){
    if(!dialog.isNull())dialog.clear();
}


void VkChoosePeer::ChoosePeer(QString token){
    access_token=token;

    getpeer->get(QNetworkRequest(QUrl("https://api.vk.com/method/messages.getDialogs.xml?access_token="+getToken()+"&count=10&v=10")));

    //QDesktopServices::openUrl(QUrl("https://api.vk.com/method/messages.getDialogs.xml?access_token="+token+"&count=10"));
    //emit setPeer(QInputDialog::getText(NULL, "id беседы", "2000000000+chat_id", QLineEdit::Normal, "2000000000"));
}

QString VkChoosePeer::getToken(){
    return access_token;
}

void VkChoosePeer::peerChoosed(QString id){
    peer_id=id;

    emit setPeer(id);
}


