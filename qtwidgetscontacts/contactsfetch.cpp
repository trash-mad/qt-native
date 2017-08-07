#include "contactsfetch.h"
#include <QDebug>
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QXmlStreamReader>

using namespace std;

ContactsFetch::ContactsFetch(){

    //Request permissions
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject::callStaticObjectMethod(className, "requestPermissions", "(Landroid/app/Activity;)Ljava/lang/String;", activity.object<jobject>());


    //Get DATA from Java
    QAndroidJniObject contacts = QAndroidJniObject::callStaticObjectMethod(className, "readContacts", "(Landroid/app/Activity;)Ljava/lang/String;", activity.object<jobject>());
    xml=contacts.toString();

    //Get count of contacts and create array
    arrlenght=xml.count("<item>")+1;
    arr=new Contact[arrlenght];

    //Parse DATA to Contact struct
    parseXML();
}

int ContactsFetch::lenght(){
    return arrlenght;
}

Contact ContactsFetch::getContact(int number){
    return arr[number];
}

void ContactsFetch::parseXML()
{
     int index=1;

     QByteArray buff = QByteArray::fromStdString(xml.toStdString());
     QXmlStreamReader reader;
     reader.addData(buff);
     if (reader.readNextStartElement()) {
            if (reader.name() == "root"){
                while(reader.readNextStartElement()){
                    if(reader.name() == "item"){
                        while(reader.readNextStartElement()) {

                                 QString name=reader.name().toString();
                                 QString value=reader.readElementText();
                                 if(name.compare("name")==0) arr[index].name=value;
                                 if(name.compare("id")==0) arr[index].id=value;
                                 if(name.compare("phone")==0) arr[index].phone=value;
                                 if(name.compare("email")==0) arr[index].email=value;
                                 if(name.compare("etype")==0) arr[index].etype=value;
                                 if(name.compare("note")==0) arr[index].note=value;

                        }
                        index++;
                        qDebug() << "------------------------------------------";
                    }
                    else
                        reader.skipCurrentElement();
                }
            }

     }
}
