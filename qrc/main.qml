import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import "MainElements"
import "Popups"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 700
    title: qsTr("Редактор JSON")
    property double iconScaler: 1.2

    header: MainHeader{
        id: mainHeader
    }

    SwipeView {
        id: stackView
        anchors.fill: parent
        currentIndex: 1

        DevicePage{
            id: devicePage
            onGoToMain: stackView.currentIndex = 1
        }

        MainPage{
            id: mainPage
            onGoToEnum: stackView.currentIndex = 2
            onGoToDevice: stackView.currentIndex = 0
        }

        EnumPage{
            id: enumPage
            onGoToMain: stackView.currentIndex = 1

        }
    }

    NewDevicePopup{
        id: newDevicePopup
    }

    TurnOffPopup{
        id: turnOffPopup
    }

    OpenFilePopup{
        id: openFilePopup
    }
    SavePopup{
        id: savePopup
    }
}
