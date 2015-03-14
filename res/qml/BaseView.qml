import QtQuick 2.3
import QtQuick.Controls 1.2
import "."

Rectangle {
    id: root_

    signal selectedDate(string date)

    function selectDate(date_) {
        cal.selectedDate = date_
        var s = datastore.getTrackItems(date_)
        tracklist.text = s
    }

    TextField {
        id: workitem
        x: Const.cEDGE_MARGIN
        y: Const.cEDGE_MARGIN
        width: root_.width - Const.cEDGE_MARGIN * 2 - cal.width
        height: 22
        placeholderText: qsTr("What will you do ?")
        focus: true

        function regWorkItem() {
            var s = ""
            var curtime = new Date()
            var strtoday = Util.cnvDatetimeToString(curtime, 'YYYY-MM-DD')
            var trackitem = Util.cnvDatetimeToString(curtime, 'hh:mm') + "\t" + workitem.text

            console.log(Qt.formatDate(cal.selectedDate, "yyyy-MM-dd"))
            console.log(strtoday)
            if (Qt.formatDate(cal.selectedDate, "yyyy-MM-dd") != strtoday)
            {
                cal.selectedDate = strtoday
                s = datastore.getTrackItems(Qt.formatDate(cal.selectedDate, "yyyy-MM-dd"))
                tracklist.text = s
            }


            tracklist.text = trackitem + "\n" + tracklist.text
            workitem.text = ""
            datastore.storeTrackItems(Util.cnvDatetimeToString(curtime, 'YYYY-MM-DD'), tracklist.text)
        }

        Keys.onReturnPressed: {
            regWorkItem()
        }

        Keys.onEnterPressed: {
            regWorkItem()
        }
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
            var s = datastore.getTrackItems(date_)
            tracklist.text = s
            root_.selectedDate(date_)
        }

        onDoubleClicked: {
            datastore.storeTrackItems(Qt.formatDate(cal.selectedDate, "yyyy-MM-dd"), tracklist.text)
        }
    }

    Component.onCompleted: {
        var date_ = Qt.formatDate(cal.selectedDate, "yyyy-MM-dd")
        var s = datastore.getTrackItems(date_)
        tracklist.text = s
        root_.selectedDate(date_)
    }
}
