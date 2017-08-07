#include "guiwindow.h"
#include "vkreader.h"
#include "vkauth.h"
#include "vkchoosepeer.h"
#include "vkcaptcha.h"
#include "vkmessageparser.h"
#include <QApplication>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QObject>
#include <QThread>
#include <QFileDialog>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!QSslSocket::supportsSsl()){
        //Ошибка, нет библиотек openssl. Нахуя он нужен, если ключи шифрования у ФСБ я не знаю, но можно сделать так
        //Qt компилирует с OpenSSL из коробки, но из за бюрократии не может сам кидать dll к exe файлу
        //Заходим на https://indy.fulgan.com/SSL/
        //Ищем ревизию openssl по строке, возращаемой через QSslSocket::sslLibraryBuildVersionString()
        //кидаем libeay32.dll и ssleay32.dll из архива к бинарнику
        //Следует качать ревизию, соответствующую разрядности компилятора, в нашем случае MSVC2015_64bit
        QMessageBox msg;
        msg.setText("ERROR! NEED OpenSSL installed, project compiled with "+QSslSocket::sslLibraryBuildVersionString()+" so you need add some dll's.");
        msg.exec();
        qDebug()<<"Проверь main функцию, я знаю как убрать эту поебень и оставил комментарий";
        return a.exit(0);
    }

    GuiWindow w;
    VkReader vk;
    //vk лежит в отдельном потоке, в нем нельзя создавать объекты. Ну или будут злые окошки при закрытии...
    QNetworkAccessManager messagewatchdog;
    QNetworkAccessManager datasender;
    vk.setNetworkAccessManager(messagewatchdog,datasender);
    QObject::connect(&vk,SIGNAL(addLog(QString)),&w,SLOT(addLog(QString)));

    VkMessageParser vkmessageparser;
    w.addLog("Драститя! Для начала работы с УФФ ботом требуется выбрать словарь. Пример словаря можно увидеть в GitHub репо. Кодировку следует ставить UTF-8");
    bool isParsed=vkmessageparser.loadDictionary(QFileDialog::getOpenFileName(NULL, "Выберите УФФ словарь", QDir::homePath(), "UFFXML (*.uffxml)"));
    if(!isParsed){
        QMessageBox msg;
        msg.setText("Не могу распарсить словарь, проверьте!");
        msg.exec();
        return a.exit(0);
    }
    vk.setMessageParser(vkmessageparser);
    w.addLog("\nВидимо, всё нормально. Далее требуется войти в ВК");


    VkAuth vkauth;
    vkauth.Auth();

    QObject::connect(&vkauth,SIGNAL(authcompleted(QString)),&vk,SLOT(setToken(QString)));

    VkChoosePeer vkpeer;

    QObject::connect(&vk,SIGNAL(choosePeer(QString)),&vkpeer,SLOT(ChoosePeer(QString)));
    QObject::connect(&vkpeer,SIGNAL(setPeer(QString)),&vk,SLOT(setPeer(QString)));

    VkCaptcha vkcaptcha;
    QObject::connect(&vk,SIGNAL(runCaptcha(QString,QString,QString)),&vkcaptcha,SLOT(runCaptcha(QString,QString,QString)));
    QObject::connect(&vkcaptcha,SIGNAL(log(QString)),&w,SLOT(addLog(QString)));
    QObject::connect(&vkcaptcha,SIGNAL(sendData(QString)),&vk,SLOT(sendData(QString)));
    QObject::connect(&vkcaptcha,SIGNAL(restartbot()),&vk,SLOT(restartbot()));


    QThread *thread = new QThread;
    vk.moveToThread(thread);
    thread->start();


    return a.exec();

}
