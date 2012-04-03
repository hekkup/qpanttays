// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

import Qt 4.7

Page {
    id: flashCardPage
    //anchors.fill: parent

    tools: flashCardPageToolBarLayout

    property int currentFlatArrayIndex: 0  // TODO: this is a deprecating variable

    property int currentCardIndex: 0
    property int currentFactIndex: 0

    //orientationLock: PageOrientation.LockLandscape
    property bool inPortrait: appWindow.inPortrait

    property bool answerButtonsLeft: false

    // horizontal swipe variables
    // x position of mouse pressed on flash card area
    property int cardXPressed: 0
    // min. required swipe length
    property int horizontalSwipeMinLength: 40

    // wordList[][] (= card deck) will be received from C++ side
    // cardDeckConfig[] will be received from C++ side
    property string deckName: ""
    property int deckIndex: -1
    property bool currentDeckLoaded: false
    property int wordListLength: 0
    property string currentFactText: ""
    //property bool currentFactLargeFont: cardDeckConfig[flashCardPage.currentFactIndex]

    //property variant factWithLargeFont: [ true, false, false ]
    //property variant flashCardFactsWithLargeFonts

    onVisibleChanged: {
        console.log("flashCardPage.onVisibleChanged")
        if (deckName !== loadedMainPage.selectedCardDeckName) {
            currentDeckLoaded = false
        }

        if (!currentDeckLoaded) {
            deckName = loadedMainPage.selectedCardDeckName
            deckIndex = loadedMainPage.selectedCardDeckIndex

            // load card deck -> wordList[][]
            dataManager.flashCardPageLoaded(deckIndex)
            currentDeckLoaded = true

            currentFactIndex = 0
            currentCardIndex = 0
            wordListLength = wordList.length
            flashCardPage.currentFactText =
                wordList[flashCardPage.currentCardIndex][flashCardPage.currentFactIndex]
        }
        // load card deck config -> cardDeckConfig[]
        dataManager.loadCardDeckConfig(deckIndex)
    }

    function startupFunction() {
        //flashCardPage.flashCardFactsWithLargeFonts = createFactFontSizeArray()
        flashCardLayoutLoader.sourceComponent = flashCardPage.inPortrait ? portraitLayoutComponent : landscapeLayoutComponent
    }

    function createFactFontSizeArray() {
        var fontSizeArray = []
        fontSizeArray[0] = true
        fontSizeArray[1] = false
        fontSizeArray[2] = false
        return fontSizeArray;
    }

    Component.onCompleted: startupFunction()

    Component {
        id: previousButtonComponent
        Button {
            id: previousButton
            text: "<"
            font.pixelSize: 96
            onClicked: previousButtonClicked()
            width: 322
        }
    }
    Component {
        id: nextButtonComponent
        Button {
            id: nextButton
            text: ">"
            font.pixelSize: 96
            onClicked: nextButtonClicked()
            width: 322
        }
    }

    // landscape buttons
    Component {
        id: answerButtonColumnComponent
        Column {
            id: answerButtonColumn
            spacing: 6
            Loader {
                height: parent.height / 2 - parent.spacing
                width: parent.width
                sourceComponent: nextButtonComponent
            }
            Loader {
                height: parent.height / 2 - parent.spacing
                width: parent.width
                sourceComponent: previousButtonComponent
            }
        }
    }

    // portrait buttons
    Component {
        id: answerButtonRowComponent
        Row {
            id: answerButtonRow
            spacing: 6
            Loader {
                //width: (parent === undefined) ? undefined : (parent.width / 2 - parent.spacing)
                width: parent.width / 2 - parent.spacing
                height: parent.height
                sourceComponent: previousButtonComponent
                onLoaded: {
                    console.log("answerButtonRow previous button loaded, item.width = "+item.width)
                    //item.width = 322
                }
            }
            Loader {
                //width: (parent === undefined) ? undefined : (parent.width / 2 - parent.spacing)
                width: parent.width / 2 - parent.spacing
                height: parent.height
                sourceComponent: nextButtonComponent
                onLoaded: {
                    console.log("answerButtonRow next button loaded, item.width = "+item.width)
                    //item.width = 322
                }
            }
        }
    }

    // flash card view: both landscape and portrait
    Component {
        id: flashCardViewComponent
        Item {
            Label {
                id: flashCardViewLabel
                text: flashCardPage.currentFactText
                anchors.centerIn: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                //font.pixelSize: (flashCardPage.currentFactIndex === 0) ? 96 : 48
                //font.pixelSize: (JS_GLOBALS.flashCardFactsWithLargeFonts[flashCardPage.currentFactIndex] === undefined) ? 48 :
                //        (JS_GLOBALS.flashCardFactsWithLargeFonts[flashCardPage.currentFactIndex] ? 96 : 48)
                font.pixelSize: cardDeckConfig[flashCardPage.currentFactIndex] ? 96 : 48
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
            MouseArea {
                anchors.fill: parent
                // browse gesture: horizontal swipe left or right
                onPressed: {
                    flashCardPage.cardXPressed = mouseX
                    //console.log("flashCardViewComponent onPressed: pos.x = "+mouseX)
                }
                onReleased: {
                    var distance = mouseX - flashCardPage.cardXPressed
                    //console.log("flashCardViewComponent onReleased: distance = "+distance)
                    if (flashCardPage.cardXPressed > 0) {
                        flashCardPage.cardXPressed = 0
                        var toRight = (distance > 0) ? true : false
                        if (Math.abs(distance) >= flashCardPage.horizontalSwipeMinLength) {
                            if (toRight) {
                                previousButtonClicked()
                            } else {
                                nextButtonClicked()
                            }
                        }
                    }
                }
            } // MouseArea
        } // Item
    }

    // portrait layout
    Component {
        id: portraitLayoutComponent
        Column {
            id: portraitLayoutColumn
            Item {
                width: parent.width
                height: parent.height
                Loader {
                    id: portraitFlashCardViewLoader
                    width: parent.width
                    height: parent.height / 5 * 4
                    sourceComponent: flashCardViewComponent
                    anchors.top: parent.top
                }
                Loader {
                    id: answerButtonRowLoader
                    width: parent.width
                    height: parent.height / 5 * 1
                    anchors.bottom: parent.bottom
                    sourceComponent: answerButtonRowComponent
                }
            }
        }
    }

    // landscape layout
    Component {
        id: landscapeLayoutComponent
        Row {
            id: landscapeLayoutRow
            Item {
                width: parent.width
                height: parent.height
                //color: "blue"
                Loader {
                    id: landscapeFlashCardViewLoader
                    width: parent.width / 5 * 4
                    height: parent.height
                    sourceComponent: flashCardViewComponent
                    anchors.left: (flashCardPage.answerButtonsLeft) ? undefined : parent.left
                    anchors.right: (flashCardPage.answerButtonsLeft) ? parent.right : undefined
                }
                Loader {
                    id: answerButtonColumnLoader
                    width: parent.width / 5 * 1
                    height: parent.height
                    anchors.left: (flashCardPage.answerButtonsLeft) ? parent.left : undefined
                    anchors.right: (flashCardPage.answerButtonsLeft) ? undefined : parent.right
                    sourceComponent: answerButtonColumnComponent
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        //spacing: 5
        // status bar
        Column {
            id: flashCardStatusBar
            //height: parent.height / 10 * 1
            width: parent.width
            Label {
                id: cardCounterLabel
                width: parent.width
                text: flashCardPage.cardCounterText()
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 40
                //color: "black"
            }
            Rectangle {
                width: parent.width
                height: 2
                color: "grey"
                //anchors.bottom: parent.bottom
            }
        }

        Item {
            id: flashCardArea
            width: parent.width
            height: parent.height - flashCardStatusBar.height // - flashCardPageToolBarLayout.height
            //height: flashCardAreaHeight()
            Loader {
                anchors.fill: parent
                id: flashCardLayoutLoader
            }
        }
    } // Column

    ToolBarLayout {
        id: flashCardPageToolBarLayout
        ToolIcon {
            platformIconId: "toolbar-back"
            onClicked: {
                pageStack.pop()
            }
        }
        ToolButton {
            text: qsTr("+10")
            onClicked: {
                var newCardIndex = flashCardPage.currentCardIndex + 10
                if (newCardIndex >= wordList.length) {
                    newCardIndex = 0
                }
                flashCardPage.currentCardIndex = newCardIndex
                flashCardPage.currentFactText =
                        wordList[flashCardPage.currentCardIndex][flashCardPage.currentFactIndex]
            }
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: {
                if (flashCardPageMenu.status === DialogStatus.Closed) {
                    flashCardPageMenu.open()
                } else {
                    flashCardPageMenu.close()
                }
            }
        }
    }

    Menu {
        id: flashCardPageMenu
        visualParent: pageStack
        MenuLayout {
            id: flashCardPageMenuLayout
            MenuItem {
                text: qsTr("Toggle landscape buttons")
                onClicked: {
                    flashCardPage.answerButtonsLeft = !flashCardPage.answerButtonsLeft
                }
            }
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

    function cardCounterText() {
        var len = flashCardPage.wordListLength
        var idx = flashCardPage.currentCardIndex + 1
        return idx + " / " + len
    }

    function nextButtonClicked() {
        if (flashCardPage.currentFactIndex >= ((wordList[flashCardPage.currentCardIndex]).length - 1)) {
            if (flashCardPage.currentCardIndex >= (wordList.length - 1)) {
                flashCardPage.currentCardIndex = 0;
            } else {
                flashCardPage.currentCardIndex += 1
            }
            flashCardPage.currentFactIndex = 0
        } else {
            flashCardPage.currentFactIndex += 1
        }
        flashCardPage.currentFactText =
                wordList[flashCardPage.currentCardIndex][flashCardPage.currentFactIndex]
        //console.debug("card = "+flashCardPage.currentCardIndex+", fact = "+flashCardPage.currentFactIndex)
    }

    function previousButtonClicked() {
        if (flashCardPage.currentFactIndex <= 0) {
            if (flashCardPage.currentCardIndex <= 0) {
                flashCardPage.currentCardIndex = wordList.length - 1;
            } else {
                flashCardPage.currentCardIndex -= 1
            }
            flashCardPage.currentFactIndex = (wordList[flashCardPage.currentCardIndex]).length - 1
        } else {
            flashCardPage.currentFactIndex -= 1
        }
        flashCardPage.currentFactText =
                wordList[flashCardPage.currentCardIndex][flashCardPage.currentFactIndex]
        //console.debug("card = "+flashCardPage.currentCardIndex+", fact = "+flashCardPage.currentFactIndex)
    }

    onCurrentCardIndexChanged: {
        cardCounterLabel.text = flashCardPage.cardCounterText()
    }

    onInPortraitChanged: {
        loadFlashCardLayout()
    }

    onAnswerButtonsLeftChanged: {
        loadFlashCardLayout()
    }

    function loadFlashCardLayout() {
        if (flashCardPage.inPortrait) {
            console.log("loadFlashCardLayout(): changing layout to portrait")
            flashCardLayoutLoader.sourceComponent = undefined
            flashCardLayoutLoader.sourceComponent = portraitLayoutComponent
        } else {
            console.log("loadFlashCardLayout(): changing layout to landscape")
            flashCardLayoutLoader.sourceComponent = undefined
            flashCardLayoutLoader.sourceComponent = landscapeLayoutComponent
        }
    }



} // Page
