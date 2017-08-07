import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0

SwipeScreen {
    id: screen
    //onSelected: usernameTextField.forceActiveFocus()

    Connections {
           target: backEnd
           onUpdateHostList: xmlModel.xml=xml;
    }

    XmlListModel{
    id: xmlModel
    query: "/root/item"
    XmlRole { name: "ip"; query: "ip/string()" }
    }

    ListView {
        Layout.fillWidth: true
        Layout.fillHeight: true
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
                        backEnd.setSelectedHost(model.ip);
                        backEnd.load("qrc:/qml/filelist.qml");
                    }
                 }
                 Label{
                     anchors.fill: parent
                     text: model.ip
                     fontSizeMode: Text.Fit
                     font.pixelSize: 30
                     verticalAlignment: Qt.AlignVCenter
                 }

            }
        }

    }


}
