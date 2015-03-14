import QtQuick 2.3
import QtQuick.Controls 1.2
import "."

Rectangle {
    id: root_

    signal selectedDate(string date)

    function selectDate(date_) {
        cal.selectedDate = date_
        var s = datastore.getTrackSummary(date_)
        tracklist.text = s
    }

    TextArea {
        id: tracklist
        width: root_.width - Const.cEDGE_MARGIN * 2 - cal.width
        height: root_.height - anchors.topMargin - Const.cEDGE_MARGIN
        anchors.leftMargin: 8
        anchors.topMargin: 36
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Calendar {
        id:cal
        weekNumbersVisible: true

        x:root_.width - cal.width
        y: Const.cEDGE_MARGIN
        onClicked: {
            var date_ = Qt.formatDate(cal.selectedDate, "yyyy-MM-dd")
            var s = datastore.getTrackSummary(date_)
            tracklist.text = s
            root_.selectedDate(date_)
        }
    }
}

