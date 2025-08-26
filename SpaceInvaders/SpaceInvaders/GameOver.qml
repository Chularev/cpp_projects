import QtQuick
import QtQuick.Layouts

Rectangle {
    id: gameOver
    visible: false
    anchors.fill: parent
    color: "black"
    opacity: 0.8
    z: 100

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 80
        Text {
            id: textGameOver
            anchors.centerIn: parent
            color: "blue"
            text: qsTr("Game Over\n" + textBoard.text)
            font.pixelSize: 50
        }
        RowLayout {
            spacing: 20
            Rectangle {
                id: closeBtn
                radius: 20
                width: 300
                height: 60
                Text {
                    text: qsTr("close")
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered: {
                        closeBtn.color = "blue"
                    }
                    onExited: {
                        closeBtn.color = "white"
                    }

                    onClicked: {
                        Qt.quit()
                    }
                }
            }
            Rectangle {
                id: restartBtn
                radius: 20
                width: 300
                height: 60
                Text {
                    text: qsTr("restart")
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered: {
                        restartBtn.color = "blue"
                    }
                    onExited: {
                        restartBtn.color = "white"
                    }

                    onClicked: {
                        controller.restartGame();
                        gameOver.visible = false
                    }
                }
            }
        }
    }

    Connections {
        target: controller
        onGameOver:
        {
            gameOver.visible = true
        }
    }


}
