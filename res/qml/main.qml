import QtQuick 2.3
import QtQuick.Controls 1.2
import "."

ApplicationWindow {
    id: root_
    visible: true
    width: Const.cSCREEN_WIDTH
    height: Const.cSCREEN_HEIGHT
    title: qsTr("TimeTracker - Tracking")

    property string selecteddate: ""
    property int viewmode: Const.cVIEWMODE_TRACKING
    property bool ticktack: true

    onWidthChanged: {
        root_.width = arg
    }
    onHeightChanged: {
        root_.height = arg
    }

    function updateTitle() {
        var curtime = new Date()
        var strtime = ""
        if (root_.ticktack)
        {
            strtime = Util.cnvDatetimeToString(curtime, '[YYYY-MM-DD hh:mm]')
        }
        else
        {
            strtime = Util.cnvDatetimeToString(curtime, '[YYYY-MM-DD hh mm]')
        }
        root_.ticktack = !root_.ticktack

        root_.title = strtime + " TimeTracker"
        var str = ""

        if (root_.viewmode == Const.cVIEWMODE_TRACKING)
        {
            str = strtime + " TimeTracker - Tracking"
        }
        else if (root_.viewmode == Const.cVIEWMODE_SUMMARY)
        {
            str = strtime + " TimeTracker - Summary"
        }

        if (str != root_.title)
        {
            root_.title = str
//            console.log("update : " + "[" + root_.title + "]" + "[" + str + "]")
        }
    }

    Timer {
        id:tmr
        interval: 500; running: true; repeat: true

        onTriggered: {
            updateTitle()
        }
    }

    ModeView {
        id:modeView
        x:0
        y:0
        width:root_.width
        height:Const.cMODEMENU_HEIGHT

        onChangemode: {
            if (mode == "Tracking")
            {
                baseView.selectDate(selecteddate)
                baseView.visible = true;
                summaryView.visible = false;
                root_.viewmode = Const.cVIEWMODE_TRACKING
                updateTitle()
            }
            else if (mode == "Summary")
            {
                summaryView.selectDate(selecteddate)
                baseView.visible = false;
                summaryView.visible = true;
                root_.viewmode = Const.cVIEWMODE_SUMMARY
                updateTitle()
            }
        }
    }

    BaseView {
        id: baseView
        visible: true
        x:0
        y:modeView.height
        width:root_.width
        height:root_.height - Const.cMODEMENU_HEIGHT

        onSelectedDate: {
            selecteddate = date
        }
    }

    SummaryView {
        id:summaryView
        visible: false
        x:0
        y:modeView.height
        width:root_.width
        height:root_.height - Const.cMODEMENU_HEIGHT

        onSelectedDate: {
            selecteddate = date
        }
    }
}
