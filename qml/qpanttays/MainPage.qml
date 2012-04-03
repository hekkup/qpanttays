// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: mainPage

    property string selectedCardDeckName: ""
    property int selectedCardDeckIndex: 0

    tools: mainPageToolBarLayout

    Column {
        anchors.fill: parent

        Item {
            id: deckListHeader
            width: parent.width
            height: childrenRect.height
            Label {
                id: deckListHeaderLabel
                font.pixelSize: 40
                text: qsTr("Card decks")
                anchors.top: parent.top
            }
            Rectangle {
                id: headerLine1
                width: parent.width
                height: 2
                color: "gray"
                anchors.top: deckListHeaderLabel.bottom
            }
        }

        ListView {
            //anchors.horizontalCenter: parent.horizontalCenter
            //anchors.top: parent.top
            id: deckListView
            //anchors.fill: parent
            height: parent.height - deckListHeader.height - mainPageToolBarLayout.height - parent.spacing - headerLine1.height
            width: parent.width
            //height: childrenRect.height

            //model: tmpListModel
            //model: fixedCardDeckListModel

            // This comes from QPanttaysDataManager:
            model: cardDeckListModel

            delegate: Component {
                id: deckListItemDelegate
                Label {
                  id: deckListItemText
                  width: deckListView.width
                  //text: deckName
                  text: name
                  font.pixelSize: 48
                  //color: "blue";
                  //width: deckListItem.width
                  //mode: deckListItem.mode
                  //role: "title"

                  MouseArea {
                      anchors.fill: parent
                      onClicked: {
                          //console.log("clicked on deck "+name+", index = "+index)
                          deckListView.currentIndex = index
                          selectedCardDeckName = name
                          selectedCardDeckIndex = index
                      }
                      onDoubleClicked: {
                          //console.log("double clicked on deck "+name+", index = "+index)
                          selectedCardDeckName = name
                          selectedCardDeckIndex = index
                          startQuerying()
                      }
                  }
                }
            } // delegate Component


            highlight: Rectangle {
                width: parent.width
                color: "gray"
                radius: 6
                //y: deckListView.currentItem.y
            }
            highlightFollowsCurrentItem: true
            highlightMoveDuration: 300

            //interactive: false

            focus: true
            clip: true

            ScrollDecorator {
                flickableItem: deckListView
            }
            pressDelay: 1000
        }
        onHeightChanged: {
            deckListView.height = height - deckListHeader.height - spacing - headerLine1.height
        }
    } // column

    ToolBarLayout {
        id: mainPageToolBarLayout
        visible: true
        ToolIcon {
            platformIconId: "toolbar-close"
            onClicked: Qt.quit();
        }
        ToolButton {
            text: qsTr("Start")
            onClicked: {
                //var fcPage = Qt.createComponent("FlashCardPage.qml")
                //pageStack.push(fcPage)
                startQuerying()
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            anchors.bottom: (parent === undefined) ? undefined : parent.bottom
            onClicked: {
                if (mainPageMenu.status === DialogStatus.Closed) {
                    mainPageMenu.open()
                    //myMenu.anchors.bottom = (parent === undefined) ? undefined : parent.anchors.top
                } else {
                    mainPageMenu.close()
                }
            }
        }
    }

    Menu {
        id: mainPageMenu
        visualParent: pageStack
        MenuLayout {
            id: myMenuLayout
            //MenuItem {
            //    text: qsTr("Import deck")
            //    onClicked: {
            //        var importWizardPageVar = Qt.createComponent("ImportWizardPage.qml")
            //        pageStack.push(importWizardPageVar)
            //    }
            //}
            MenuItem {
                text: qsTr("Settings")
                onClicked: {
                    var settingsPageVar = Qt.createComponent("SettingsPage.qml")
                    pageStack.push(settingsPageVar)
                }
            }
            MenuItem {
                text: qsTr("About")
                onClicked: {
                    var aboutPageVar = Qt.createComponent("AboutPage.qml")
                    pageStack.push(aboutPageVar)
                }
            }
        }
    }

    function startQuerying() {
        //var fcPage = Qt.createComponent("FlashCardPage.qml")
        //var fcPage = appWindow.loadedFlashCardPage
        pageStack.push(loadedFlashCardPage)
    }

}
