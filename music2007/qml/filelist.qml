import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0

ColumnLayout{
anchors.fill: parent
property string ip: backEnd.getSelectedHost()
function loadfiles(){
    console.log("ok");
    xmlModel.xml=backEnd.getFileList(ip);
}



    XmlListModel{
        id: xmlModel
        query: "/root/item"
        XmlRole { name: "name"; query: "name/string()" }
        XmlRole { name: "id"; query: "id/string()" }
    }

    ListView {
        id: view
        Layout.fillHeight: true
        Layout.fillWidth: true
        focus: true
        headerPositioning: ListView.PullBackHeader
        header: ColumnLayout{
            Label{
            Layout.fillWidth: true
            text: "Список файлов"
            font.pixelSize: 25
            }
            Text{
            text: "Пометьте файлы, которые хотите получить"
            }
        }
        model: xmlModel
        delegate: Item{
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            Rectangle {
            anchors.fill: parent
            color: model.index%2?"transparent":"whitesmoke"
            MouseArea {
            anchors.fill: parent
            onClicked: {
                img.source="qrc:/images/repeat.png"
                backEnd.downloadfile(model.name,ip,model.id)
            }

            }

            RowLayout{
                Image {
                id: img
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: height
                source: "qrc:/images/favorite.png"
                }
                ColumnLayout{
                 Layout.fillWidth: true
                 Layout.fillHeight: true
                 Text{
                     text: model.name
                     fontSizeMode: Text.Fit
                     font.pixelSize: 22
                 }
                 Text{
                     text: "id:"+model.id
                 }
                }
            }
            }
        }
    }

    Button{
        id: backbutton
        Layout.fillWidth: true
        Layout.preferredHeight: 50
        text: "Назад"
        onClicked: backEnd.load("qrc:/qml/player/main.qml")
    }

    Component.onCompleted: loadfiles();
}
