import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Button{
    property string filename: "name"
    property string filetype: "File"
    anchors.left: parent.left
    anchors.right: parent.right
    background: Rectangle { color: "transparent"; }

    RowLayout{
    anchors.fill: parent

    Image {
    source: "qrc:/images/"+filetype.toLowerCase()+".png"
    }
    Text{
    Layout.fillWidth: true
    text: filename
    }
}
}
