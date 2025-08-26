import QtQuick

Item {
    id: bullet
    visible: true
    width: 10
    height: 30
    x: model.x
    y: model.y

    Image {
        anchors.fill: parent
        source: "qrc:/bullet/bullet.png"
    }
}
