import QtQuick 2.7
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.XmlListModel 2.0

ColumnLayout{
anchors.fill: parent
height: 480
width: 320

XmlListModel {
     id: xmlModel
     source: "https://api.vk.com/method/messages.getDialogs.xml?access_token="+backEnd.getToken()+"&count=10&v=10"
     query: "/response/items/dialog/message"
     XmlRole { name: "title"; query: "title/string()" }
     XmlRole { name: "chatid"; query: "chat_id/string()" }
     XmlRole { name: "userid"; query: "user_id/string()" }
 }



 ListView {
     Layout.fillHeight: true
     Layout.fillWidth: true
     spacing: 5
     model: xmlModel
     delegate:
     RowLayout{
     anchors.left: parent.left
     anchors.right: parent.right
     Text{
     MouseArea{
         anchors.fill: parent;
         onClicked: (model.chatid=="")?Qt.openUrlExternally("http://vk.com/id"+model.userid):false;
     }

     Layout.fillWidth: true
     text: (model.chatid=="")?"id"+model.userid:"chat"+model.title;
     font.pointSize: 10
     }
     Button{
         text: "Выбрать чат"
         width: 250
         onClicked: {
             if(model.chatid == ""){
                 //это человек
                 backEnd.peerChoosed(model.userid)
             }
             else{
                 backEnd.peerChoosed(2000000000+parseInt(model.chatid))
             }
         }
     }
     }
}
}

