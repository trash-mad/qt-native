import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

ColumnLayout{
    height: 480
    width: 320
    Text{
        Layout.fillHeight: true
        Layout.fillWidth: true
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        text: "main2.qml"
    }
    Button{
        Layout.fillWidth: true
        height: 75
        text: "Load main.qml"
        onClicked: backEnd.load("qrc:/main.qml")
    }
}
