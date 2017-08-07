import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0

SwipeScreen {
    id: screen
    //onSelected: usernameTextField.forceActiveFocus()

    Connections {
           target: backEnd
           onUpdateMusList: xmlModel.xml=xml;
    }

    XmlListModel{
    id: xmlModel
    query: "/root/item"
    XmlRole { name: "name"; query: "name/string()" }
    XmlRole { name: "path"; query: "path/string()" }
    XmlRole { name: "id"; query: "id/string()" }
    }

    ListView {
        Layout.fillWidth: true
        Layout.fillHeight: true
        id: view
        focus: true
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
                if(playerindex!=index) playerindex=index;
                backEnd.playpause(index);

            }
            }


            RowLayout{
                ColumnLayout{
                 Layout.fillWidth: true
                 Layout.fillHeight: true

                 Label {
                     text: model.name.substring(0,15)+"..."
                     font.pixelSize: 22
                 }
                 Text {
                     text: model.path.substring(0,30)+"..."

                 }
                }
            }
            }
        }


    }


}
