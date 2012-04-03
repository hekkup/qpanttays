// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: helpPage

    // TODO when in landscape mode, enable vertical flick and change column verticalCenterOffset to 0

    tools: helpPageToolBarLayout

    Flickable {
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent

        Column {
            width: parent.width
            Label {
                text: qsTr("Card deck files")
                font.pixelSize: 40
            }
            Label {
                id: cardDeckFileHelpText
                width: parent.width
                text:
"On start, QPanttays reads all *.CSV (Comma Separated Values) files \
in ~/.qpanttays and ~/MyDocs/.qpanttays folders and lists them as card decks. \
The file names without extension are used as card deck names. The CSV files \
must have the following format:\n\
\n\
\"fact1\",\"fact2\",\"fact3\"\n\
(double quoted facts)\n\
\n\
Actually the number of facts is not limited, however font size settings are \
only supported to up to 3 facts. Currently you have to create and edit the \
card deck files on PC, then transfer them to these folders. Many flashcard \
and spreadsheet programs can export CSV files so it's \
possible to use them for this task."
            }
        } // Column
    } // Flickable
    ScrollDecorator {
        flickableItem: cardDeckFileHelpText
    }

    ToolBarLayout {
        id: helpPageToolBarLayout
        ToolIcon {
            platformIconId: "toolbar-back"
            onClicked: {
                pageStack.pop()
            }
        }
    }
}

