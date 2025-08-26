import QtQuick

Item {
    property var enemyImg: [
        "qrc:/enemy/enemy1.png",
        "qrc:/enemy/enemy2.png",
        "qrc:/enemy/enemy3.png",
        "qrc:/enemy/enemy4.png",
        "qrc:/enemy/enemy5.png"
    ]
    id: enemy
    visible: true
    width: 40
    height: 40
    x: model.x
    y: model.y

    Image {
        anchors.fill: parent
        source: enemyImg[model.type]
    }
}
