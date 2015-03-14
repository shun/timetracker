import QtQuick 2.3
import QtQuick.Controls 1.2
import "."

Rectangle {
    id: root_

    signal changemode(string mode)

    Button {
        id:btn_tracking
        width: 80
        height: root_.height
        text: "Tracking"
        x:0
        y:0

        onClicked: {
            changemode(text)
        }
    }

    Button {
        id:btn_summary
        width: 80
        height: root_.height
        text: "Summary"
        x:btn_tracking.width
        y:0

        onClicked: {
            changemode(text)
        }
    }
}

