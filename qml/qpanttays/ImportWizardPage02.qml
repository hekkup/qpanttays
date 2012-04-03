// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: importWizardPage02

    tools: importWizardPageToolBarLayout

    Column {
        anchors.fill: parent
        spacing: 10

        /// @todo make title bar component
        Column {
            id: wizardPage1TitleBar
            width: parent.width
            Label {
                width: parent.width
                horizontalAlignment: Qt.AlignHCenter
                text: "Import card deck - 2/4"
            }
            Rectangle {
                width: parent.width
                height: 2
                color: "grey"
            }
        }

        Column {
            id: wizardPage2MainArea
            width: parent.width
            //height: parent.height - wizardPage1TitleBar.height
            //height: 240
            spacing: 40
            TableView {

            }

            /*Button {
                text: "Browse..."
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 50
                height: 130
                onClicked: {
                    importWizardContinueButton.enabled = !importWizardContinueButton.enabled
                    console.log("browse")
                }
            }
            Button {
                id: importWizardContinueButton
                text: "Next >"
                enabled: false
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 50
                height: 130
                onClicked: {
                    console.log("import wizard")
                }
            }*/
        }
    }
}


