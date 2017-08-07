import QtQuick 2.5
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

ColumnLayout{
property int playerindex: 0
Rectangle{
    id: statusbar
    Layout.fillWidth: true
    height: 120

    ColumnLayout{
    anchors.fill: parent
    RowLayout{
        id: "titlerow"
        Layout.fillWidth: true
        Layout.preferredHeight: statusbar.height/3
        MouseArea{
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: height
            DrawerButton{ id: drawericon; anchors.centerIn: parent }
            onClicked:  drawericon.state=drawericon.state==="menu"?"back":"menu"
        }
        Text {
            text: "Музыка 2007"
            font.pixelSize: titlerow * 0.25
        }

    }
    RowLayout{
        id: "pprow"
        Layout.fillWidth: true
        Layout.preferredHeight: statusbar.height/3
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        ToolButton {
        Layout.preferredHeight: parent.height*0.75
        Layout.preferredWidth: height
        contentItem:Image {
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: height
        source: "qrc:/images/previous.png"
        //ColorOverlay { anchors.fill: parent; source: parent; color: "#1e90ff" }
        }
        onClicked: backEnd.prev();
        }

        ToolButton {
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: height
        contentItem: Image {
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: height
        source: "qrc:/images/play.png"
        }
        onClicked: backEnd.playpause(playerindex);
        }

        ToolButton {
        Layout.preferredHeight: parent.height*0.75
        Layout.preferredWidth: height
        contentItem: Image {
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: height
        source: "qrc:/images/next.png"
        }
        onClicked: backEnd.next();
        }


    }
    }



}

SwipeList {
    Layout.fillHeight: true
    Layout.fillWidth: true
    model: ListModel {
        ListElement {
            title: "Список музыки"
            source: "ListScreen.qml"
        }

        ListElement {
            title: "Доступные"
            source: "LocalScreen.qml"
        }
    }
}

Component.onCompleted: backEnd.update();
}
