#include <QString>
#include <QCommandLineOption>
#include <QCommandLineParser>

namespace VkMessageParser {
QString parse(QString value){
    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    QStringList list;
    //парсер пропускает первый аргумент, так что учитываем
    list << " " <<command.split(" ");

    //Добавление опций
    const  QCommandLineOption kakcaplya("цапля", "Постоять как цапля", "1");
    parser.addOption(kakcaplya);
    if (!parser.parse(list)) {
    return "NoMESSAGE!";
    }

    if(parser.isSet(kakcaplya)){
    return "Курлык";
    }
}
