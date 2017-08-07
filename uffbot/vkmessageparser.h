#ifndef VKMESSAGEPARSER_H
#define VKMESSAGEPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>

class VkMessageParser : public QObject
{
Q_OBJECT

QStringList myOptions;
QStringList myAnswers;

public:
explicit VkMessageParser(QObject *parent = 0);
~VkMessageParser();
bool loadDictionary(const QString path);
QString parseString(QString value);
private:
QString compareStrings(QStringList list);
QString removesymbols(QString value, QStringList symbols);



public slots:
};

#endif // VKMESSAGEPARSER_H
