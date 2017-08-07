import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Item {
    id: swipeView
    property var model
    property bool isDesktopPlatform: Qt.platform.os === "windows" ||
                                     Qt.platform.os === "linux" ||
                                     Qt.platform.os === "osx"


    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        //А эта поеботана- сам статусбар
        ListView {
            id: headersListView
            Layout.fillWidth: true
            Layout.preferredHeight: 16 * Screen.logicalPixelDensity
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds
            model: swipeView.model
            currentIndex: screensListView.currentIndex

            delegate: Item {
                width: screensListView.width/screensListView.model.count//headerLabel.width + headersListView.height * 0.4
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                Text {
                    id: headerLabel
                    anchors.centerIn: parent
                    text: model.title
                    font.pixelSize: headersListView.height * 0.15
                    font.capitalization: Font.AllUppercase
                }


                Rectangle {
                    visible: index !== 0
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: 1
                    height: parent.height * 0.4
                    color: "lightgray"
                }

                Rectangle {
                    visible: index !== headersListView.count - 1
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    width: 1
                    height: parent.height * 0.4
                    color: "lightgray"
                }


                //Выделение
                Rectangle {
                    anchors.fill: parent
                    opacity: (headerMouseArea.pressed) ? 0.4 : 0
                    color: "#1e90ff"

                    Behavior on opacity {
                        NumberAnimation {
                            duration: 200
                        }
                    }
                }

                MouseArea {
                    id: headerMouseArea
                    anchors.fill: parent
                    onClicked: screensListView.currentIndex = index
                }

            }
            highlightFollowsCurrentItem: false
            highlight: Item {
                x: headersListView.currentItem.x
                width: headersListView.currentItem.width
                height: stripRectangle.height * 3
                anchors.bottom: parent.bottom

                Behavior on x {
                    NumberAnimation {
                        duration: 300
                    }
                }

                Behavior on width {
                    NumberAnimation {
                        duration: 300
                    }
                }

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: stripRectangle.height * 2
                    color: "#1e90ff"
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: stripRectangle.height
                    color: "#004d99"
                }
            }

            Rectangle {
                id: stripRectangle
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: parent.height * 0.05
                z: -1
                color: "lightgray"
            }
        }

        //Эта поеботина есть ничто иное, как фрейм, грузящий qml код
        ListView {
            id: screensListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: ListView.Horizontal
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            highlightMoveVelocity: 2000
            clip: true
            model: swipeView.model
            onCurrentItemChanged: {
                if (isDesktopPlatform)
                    currentItem.item.selected()
            }
            delegate: Loader {

                width: screensListView.width
                height: screensListView.height
                source: model.source

                Component.onCompleted: {
                    item.isFirstScreen = (index === 0)
                    item.isLastScreen = (index === screensListView.count - 1)
                }
            }
        }
    }

}
