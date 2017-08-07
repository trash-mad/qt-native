import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Column{
    Button{
        text: "Enable proximity wakelock"
        onClicked: text=backEnd.callJava();
    }

}
