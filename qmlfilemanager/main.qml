import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0

ColumnLayout{
    height: 480
    width: 320
    function getlist(){
        filemodel.xml=backEnd.getDir("/list");
    }


    ListView{
        id: filelist
        model: filemodel
        Layout.fillWidth: true
        Layout.fillHeight: true
        delegate:
            FileItem{
            filename: name
            filetype: type
            onClicked: if(type=="Dir")filemodel.xml=backEnd.getDir(name);
            }
    }



    XmlListModel {
        id: filemodel
        query: "/root/item"
        XmlRole { name: "name"; query: "name/string()" }
        XmlRole { name: "type"; query: "type/string()" }
        Component.onCompleted: getlist()
    }

    RowLayout{
    Layout.fillWidth: true
    height: 75
        Button{
           text: "Back"
           Layout.fillWidth: true
           onClicked: filemodel.xml=backEnd.getDir("/up");
        }
        Button{
            text: "Update"
            Layout.fillWidth: true
            onClicked: getlist();
        }
    }

}
