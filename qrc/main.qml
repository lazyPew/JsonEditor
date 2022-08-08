import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

import "MainElements"
import "Popups"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Редактор JSON")

    header: MainHeader{
        id: mainHeader
    }

    MainPage{
        id: mainPage
        anchors.fill: parent
    }

//    ScrollView {
//        anchors.fill: parent

//    }

    TurnOffPopup{
        id: turnOffPopup
    }

    OpenFilePopup{
        id: openFilePopup
    }
}
