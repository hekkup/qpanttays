// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: settingsPage

    tools: settingsPageToolBarLayout

    Component.onCompleted: {
        dataManager.loadCardDeckConfig(0);
    }

    //Flickable {
        //flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent

        Column {
            width: parent.width
            Label {
                text: qsTr("Facts with large font")
                font.pixelSize: 40
            }
            Label {
                width: parent.width
                text: qsTr("Which of the available facts in a flashcard will be shown with large font")
                font.pixelSize: 24
            }
            Row {
                width: parent.width
                Label {
                    text: "Fact 1"
                    font.pixelSize: 40
                }
                CheckBox {
                    id: fact1WithLargeFont
                    anchors.right: parent.right
                    checked: cardDeckConfig[0]
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        dataManager.setLargeFactFont(0, !cardDeckConfig[0])
                        //console.log("cardDeckConfig[0] = " + cardDeckConfig[0])
                    }
                }
            }
            Row {
                width: parent.width
                Label {
                    text: "Fact 2"
                    font.pixelSize: 40
                }
                CheckBox {
                    id: fact2WithLargeFont
                    anchors.right: parent.right
                    checked: cardDeckConfig[1]
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        dataManager.setLargeFactFont(1, !cardDeckConfig[1])
                        //console.log("cardDeckConfig[1] = " + cardDeckConfig[1])
                    }
                }
            }
            Row {
                width: parent.width
                Label {
                    text: "Fact 3"
                    font.pixelSize: 40
                }
                CheckBox {
                    id: fact3WithLargeFont
                    anchors.right: parent.right
                    checked: cardDeckConfig[2]
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        dataManager.setLargeFactFont(2, !cardDeckConfig[2])
                        //console.log("cardDeckConfig[2] = " + cardDeckConfig[2])
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 2
                color: "gray"
            }

            Row {
                width: parent.width
                Label {
                    text: "Toggle theme"
                    font.pixelSize: 40
                }
                CheckBox {
                    id: toggleThemeCheckbox
                    anchors.right: parent.right
                    checked: !theme.inverted
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        theme.inverted = !theme.inverted
                    }
                }
            }
        } // Column
    //} // Flickable

    ToolBarLayout {
        id: settingsPageToolBarLayout
        ToolIcon {
            platformIconId: "toolbar-back"
            onClicked: {
                pageStack.pop()
            }
        }
    }
}
