import QtQuick

Window {
    width: 1800
    height: 1000
    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height

    visible: true
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        visible: true
        gradient: Gradient
           {
               GradientStop { position: 0.0; color: "#132330"}
               GradientStop { position: 1.0; color: "black"}
           }
        FontLoader {
            id: fBold
            source: "qrc:/font/Doto-Bold.ttf"
        }

        GameOver {

        }

        Item {
            id: move
            visible: true
            focus: true
            Image {
                id: player
                anchors.fill: parent
                source: "qrc:/player/rocket.png"
            }
            AnimatedImage{
                id: truster
                source: "qrc:/player/thruster.gif"
                width: 20
                height: 35
                anchors.top: player.bottom
                anchors.horizontalCenter: player.horizontalCenter
                playing: true
            }

            width: 50
            height: 50

            x: controller.x //(parent.width - width) / 2
            y: controller.y //parent.height - height - 10

            Keys.onPressed: function(event)
                            {
                                truster.playing = true
                                if (event.key === Qt.Key_Left) {
                                    controller.moveLeft()
                                }
                                if (event.key === Qt.Key_Right) {
                                    controller.moveRight()
                                }

                                if (event.key === Qt.Key_Down) {
                                    controller.moveDown()
                                }

                                if (event.key === Qt.Key_Up) {
                                    controller.jumpInit()
                                }

                                if (event.key === Qt.Key_Space) {
                                    controller.fireBullet()
                                }


                            }
            Keys.onReleased: function(event)
            {
                truster.playing = true
                if(event.key === Qt.Key_Left || event.key === Qt.Key_Right)
                {
                    controller.stopMovement()
                }
            }
        }
        Text {
            id: textBoard
            padding: 15
            text: qsTr("Score: " + controller.score)

            /*
            font.family: fBold.font.family
            font.weight: fBold.font.weight
            font.styleName: fBold.font.styleName
            */

            font.pixelSize: 20
            color: "white"
        }
        Repeater {
            model: controller.getBullets
            delegate: Bullet{}
        }
        Repeater {
            model: controller.getEnemies
            delegate: Enemy{}
        }
    }
}
