import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

ColumnLayout{
    height: 480
    width: 320
    TextArea{
       Layout.fillHeight: true
       Layout.fillWidth: true
       id: log
       text: "Press button to start server"
    }

    RowLayout{
    Layout.fillWidth: true
    Layout.margins: 10
    height: 100
        Button{
        Layout.fillWidth: true
        onClicked: backEnd.stopServer();
        text: "Stop"
        }

        Button{
        Layout.fillWidth: true
        onClicked: backEnd.startServer();
        text: "Start"
        }
    }

    Timer {
           interval: 500;
           running: true;
           repeat: true
           onTriggered: log.text=backEnd.getLog();
    }

}

