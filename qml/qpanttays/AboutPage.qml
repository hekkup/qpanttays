// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: aboutPage

    // TODO when in landscape mode, enable vertical flick and change column verticalCenterOffset to 0

    tools: aboutPageToolBarLayout

    Flickable {
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent
        enabled: aboutPage.rotation ? false : true

        Column {
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: aboutPage.rotation ? -64 : 0

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "icons/qpanttays80.png"
            }
            Label {
                text: "QPanttays"
                font.pixelSize: 32
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                text: qsTr("v. 0.1")
                font.pixelSize: 24
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                text: "H. Pitkala <hpitkala@hotmail.com>"
                font.pixelSize: 24
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                text: " "
                font.pixelSize: 24
            }
            Label {
                text: qsTr("The always diligent alphabet rooster will bring you a lot of nice time of learning.")
                font.pixelSize: 24
                width: parent.width - 48
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                text: " "
                font.pixelSize: 24
            }
            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "icons/creative-commons-by-license-88x31.png"
            }
            Label {
                text: " "
                font.pixelSize: 8
            }
            Label {
                text: qsTr("Licensed under Creative Commons Attribution 3.0 Unported License, http://creativecommons.org/licenses/by/3.0/")
                font.pixelSize: 16
                width: parent.width - 48
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Label {
                text: " "
                font.pixelSize: 16
            }
            Label {
                text: qsTr("Welcome to join the development at https://github.com/hekkup/qpanttays")
                font.pixelSize: 16
                width: parent.width - 48
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
            }
        } // Column
    } // Flickable

    ToolBarLayout {
        id: aboutPageToolBarLayout
        ToolIcon {
            platformIconId: "toolbar-back"
            onClicked: {
                pageStack.pop()
            }
        }
    }
}
