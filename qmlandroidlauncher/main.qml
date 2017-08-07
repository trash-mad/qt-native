import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.XmlListModel 2.0

ColumnLayout{
    function lol(){
    xmlModel.xml=backEnd.getApplist();
    }



    XmlListModel {
        id: xmlModel
        query: "/root/item"

        XmlRole { name: "name"; query: "name/string()" }
        XmlRole { name: "path"; query: "path/string()" }
    }

    ListView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 10
        boundsBehavior: Flickable.StopAtBounds

        model: xmlModel

        delegate: RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        Text{
            Layout.fillWidth: true
            text: model.path
        }
        Button{
            text: "Run app"
            width: 250
            onClicked: backEnd.runApp(model.name);
        }
        }


    }
    Component.onCompleted: lol();
}
