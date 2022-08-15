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

    MainPage{
        id: mainPage
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: mainPage

        function changeToPage(item){
            while (stackView.currentItem != mainPage){
                stackView.pop()
            }
            if (item !== currentItem){
                stackView.push(item)
            }
        }

        clip: true
        onCurrentItemChanged: {
            if (stackView.depth > 0) {
                currentItem.forceActiveFocus()
            }
        }
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
