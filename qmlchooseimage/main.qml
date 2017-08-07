import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0


ColumnLayout{

    Connections {
       target: backEnd
       onSendToQml: {
           image.source="file://"+url;
       }
    }
    Image{
       id: image
       Layout.fillHeight: true
       Layout.fillWidth: true
    }

    Button{
        Layout.fillWidth: true
        height: 75
        text: "Choose photo"
        onClicked: backEnd.getImages();
    }
}
