#ifndef CONTACTSFETCH_H
#define CONTACTSFETCH_H

#include <QObject>


struct Contact{
    QString name;
    QString id;
    QString phone;
    QString email;
    QString etype;
    QString note;
};

class ContactsFetch : public QObject
{
Q_OBJECT
int arrlenght=0;
QString xml;
Contact *arr;

const char *className = "org/qtproject/example/fetch/FetchClass";

public:
ContactsFetch();
int lenght();
Contact getContact(int number);

private:
void parseXML();

};

#endif // CONTACTSFETCH_H
