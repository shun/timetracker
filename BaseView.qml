import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: root_
    width: 640
    height: 480

    property int edgemargin: 8

    function appendTrack(item) {

    }
    function cnvDatetimeToString(datetime, format) {
        if (!format) format = 'YYYY-MM-DD hh:mm:ss.SSS';
        format = format.replace(/YYYY/g, datetime.getFullYear());
        format = format.replace(/MM/g, ('0' + (datetime.getMonth() + 1)).slice(-2));
        format = format.replace(/DD/g, ('0' + datetime.getDate()).slice(-2));
        format = format.replace(/hh/g, ('0' + datetime.getHours()).slice(-2));
        format = format.replace(/mm/g, ('0' + datetime.getMinutes()).slice(-2));
        format = format.replace(/ss/g, ('0' + datetime.getSeconds()).slice(-2));
        if (format.match(/S/g)) {
            var milliSeconds = ('00' + datetime.getMilliseconds()).slice(-3);
            var length = format.match(/S/g).length;
            for (var i = 0; i < length; i++) format = format.replace(/S/, milliSeconds.substring(i, i + 1));
        }
        return format;
    }

    TextField {
        id: workitem
        x: edgemargin
        y: edgemargin
        width: root_.width - edgemargin * 2
        height: 22
        placeholderText: qsTr("What will you do ?")
        focus: true

        function regWorkItem() {
            var curtime = new Date()
//            var trackitem = cnvDatetimeToString(curtime, 'YYYY-MM-DD hh:mm') + "\t" + workitem.text
            var trackitem = cnvDatetimeToString(curtime, 'hh:mm') + "\t" + workitem.text

            tracklist.text = trackitem + "\n" + tracklist.text
            workitem.text = ""
            datastore.storeTrackItems(cnvDatetimeToString(curtime, 'YYYY-MM-DD'), tracklist.text)
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
        width: root_.width - edgemargin * 2
        height: root_.height - anchors.topMargin - edgemargin
        anchors.leftMargin: 8
        anchors.topMargin: 36
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Component.onCompleted: {

    }
}
