// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {

    Page {
        id: mainPage
        width: 100
        height: 62
        ListView {
            model: cardDeckListModel
        }
    }
}
