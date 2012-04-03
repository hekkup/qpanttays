// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    //initialPage: FlashCardPage { }
    initialPage: MainPage { }
    //initialPage: loadedMainPage
    //initialPage: AboutPage { }
    //initialPage: ImportWizardPage { }
    //initialPage: SettingsPage { }
    //initialPage: HelpPage { }

    showStatusBar: true
    showToolBar: true

    property variant loadedFlashCardPage: FlashCardPage { }
    property variant loadedMainPage: MainPage { }

    Component.onCompleted: {
        theme.inverted = true
    }
}
