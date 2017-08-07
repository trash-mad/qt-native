/* Первый пример парсинга сообщений. Если приходит новое сообщение, вызывается parse()
 *
 * Этот метод использует парсер коммандной строки. Первое слово игнорируется, комманды следует
 * начинать с дефиса(-)
 *
 * Пример: Уффбот -цапля
 *
 *
#include <QString>
#include <QCommandLineOption>
#include <QCommandLineParser>

namespace VkMessageParser {
QString parse(QString value){
    QCommandLineParser parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    QStringList list;
    //парсер пропускает первый аргумент, так что учитываем
    list << " " <<value.split(" ");

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
*/
