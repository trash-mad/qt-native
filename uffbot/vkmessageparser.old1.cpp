/* Второй пример парсинга сообщений. Варианты ответа вшиты в бинарник
 *
 * Этот метод ищет соответствия через QStringList с ответами и цикл. Позволяет просто
 * вшить в бота свою логику и дать клиенту
 *
 * Пример: Марья Ивановна, вы сегодня очень красива
 * Ответ: Кто вы-то, еп твою мать!
 *
 * Бот видит соответствия и дает цитату
 *
#include <QString>
#include <QStringList>
#include <QDebug>

namespace VkMessageParser {
QString removesymbols(QString value, QStringList symbols){
QString ret=value;
for(int i=0;i<symbols.length();i++){
    ret.remove(symbols.at(i),Qt::CaseInsensitive);
}
return ret;
}

QString compare(QStringList list){
    QStringList myOptions;
    myOptions << "вы" << "/погода" << "какие";
    for(int i=0;i<list.length();i++){
        switch(myOptions.indexOf(list.at(i).toLower())){
          case 0:
            return "Кто вы-то, еп твою мать!";
            qDebug() << "вы";
            break;

          case 1:
            return "Да мне вообще всеравно, какая погода. Чё там твориться, мне всеравно...";
            break;

          case 2:
            return "И это знать надо! Это классика блядь!";
            break;

        }
    }
return "NoMESSAGE!";
}

QString parse(QString value){
    QStringList symbols;
    QString ret;
    symbols << "," << "." << "!";
    ret=removesymbols(value,symbols);

    QStringList letterlist;
    letterlist << ret.split(" ");

    return compare(letterlist);

    //return "NoMESSAGE!";
}
}
*/
