#include "vkauth.h"

VkAuth::VkAuth(QObject *parent) : QObject(parent){
    viewer = new QWebEngineView;
    //webview.page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    viewer->setWindowTitle("Вход в вк");
    viewer->setWindowFlags(Qt::WindowTitleHint);
    connect(viewer,SIGNAL(loadFinished(bool)),this,SLOT(checkUrl()));
}

VkAuth::~VkAuth(){
    if(!viewer.isNull()) viewer.clear();
}

void VkAuth::Auth(){
viewer->setUrl(QUrl(QString("http://oauth.vk.com/authorize?client_id="+id.toString()+"redirect_uri=https://oauth.vk.com/blank.html&response_type=token&scope=messages&display=mobile")));
viewer->show();
}

void VkAuth::checkUrl(){
QUrl url(viewer->url().toString());
if(url.toString().contains("access_token")){
viewer->setHtml("OK");
url = url.toString().replace("#", "?");
QUrlQuery query(url);
access_token=QString(query.queryItemValue("access_token"));
viewer->hide();
emit authcompleted(access_token);
}
}
