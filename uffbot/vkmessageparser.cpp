/* Третий пример парсинга сообщений. Варианты ответа вшиты во внешний xml файл
 *
 * Этот метод использует 3 QStringList и двумя циклами сравнивает каждое слово из первого цикла
 * с тегом из второго и выводит ответ из третьего, если они совпадают
 *
 * Пример: Марья Ивановна, вы сегодня очень красива
 * Ответ: Кто вы-то, еп твою мать!
 *
 * Бот видит соответствия и дает цитату
 *
 *
 *
 *
 * ПРИ ПЕРЕДЕЛЫВАНИИ ПОД СВОЙ КОД СТОИТ УЧИТЫВАТЬ, ЧТО ЭТО КЛАСС
 * ТУТ ВСЁ ТАКЖЕ ВЫЗЫВАЕТСЯ parseString(), но уже не на прямую, а через слот!!!
 */

#include "vkmessageparser.h"


VkMessageParser::VkMessageParser(QObject *parent) : QObject(parent){
}

VkMessageParser::~VkMessageParser(){
}

bool VkMessageParser::loadDictionary(const QString path){
    QFile fo(path);
    fo.open((QIODevice::ReadOnly)| QIODevice::Text);
    QTextStream out(&fo);
    out.setCodec("UTF-8");

    QByteArray buff = QByteArray::fromStdString(out.readAll().toStdString());

    QXmlStreamReader reader;
    reader.addData(buff);
    if (reader.readNextStartElement()) {
    if (reader.name() == "root"){
    while(reader.readNextStartElement()){
    if(reader.name() == "item"){
    while(reader.readNextStartElement()) {
    QString name=reader.name().toString();
    QString value=reader.readElementText();
    if(name.compare("uffoption")==0) myOptions << value;
    if(name.compare("uffanswer")==0) myAnswers << value;
    }
    }
    else reader.skipCurrentElement();
    }
    }
    }

    if((myOptions.count()==myAnswers.count())&&(myOptions.count()>0)) return true;
    return false;
}

QString VkMessageParser::removesymbols(QString value, QStringList symbols){
QString ret=value;
for(int i=0;i<symbols.length();i++){
    ret.remove(symbols.at(i),Qt::CaseInsensitive);
}
return ret;
}

QString VkMessageParser::compareStrings(QStringList list){
    for(int i=0;i<list.length();i++){
    for(int j=0; j<myOptions.length();j++){
        if(list.at(i).compare(myOptions.at(j),Qt::CaseInsensitive)==0) return myAnswers.at(j);
    }
    }
    return "NoMESSAGE!";
}

QString VkMessageParser::parseString(QString value){
    QStringList symbols;
    QString ret;
    symbols << "," << "." << "!" << "-" << "?";
    ret=removesymbols(value,symbols);

    QStringList letterlist;
    letterlist << ret.split(" ");

    return compareStrings(letterlist);
}
