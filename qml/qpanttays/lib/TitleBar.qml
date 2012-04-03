// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Component {
    property string text: ""
    property int pixelSize: 40
    Item {
        anchors.fill: parent
        Label {
            width: parent.width
            font.pixelSize: pixelSize
            text: text
            anchors.top: parent.top
        }
        Rectangle {
            width: parent.width
            height: 2
            color: "gray"
            anchors.bottom: parent.bottom
        }
    }
}
