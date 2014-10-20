import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: root_
    width: 640
    height: 480

    property int edgemargin: 8

    TextField {
        id: workitem
        x: edgemargin
        y: edgemargin
        width: root_.width - edgemargin * 2
        height: 22
        placeholderText: qsTr("Text Field")
    }

    TextArea {
        id: tracklist
        width: root_.width - edgemargin * 2
        height: root_.height - anchors.topMargin - edgemargin
        anchors.leftMargin: 8
        anchors.topMargin: 36
        anchors.top: parent.top
        anchors.left: parent.left
    }
}
