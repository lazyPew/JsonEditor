import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

ToolBar {
    id: root
    property var fontSize: Qt.application.font.pixelSize * 1.6

    width: parent.width

    RowLayout{
        anchors.fill: parent
        ToolButton{
            id: exitButton
            scale: mainWindow.iconScaler
            icon.source: "/Icons/exit"
            font.pixelSize: root.fontSize
            onClicked: turnOffPopup.open()
        }

        Item{
            Layout.fillWidth: true
        }

        ToolButton{
            id: saveButton
            scale: mainWindow.iconScaler
            icon.source: "/Icons/save"
            font.pixelSize: root.fontSize
            onClicked: savePopup.open()
        }

        ToolButton{
            id: openButton
            scale: mainWindow.iconScaler
            icon.source: "/Icons/open"
            font.pixelSize: root.fontSize
            onClicked: openFilePopup.open()//panel.openJsonFile(":/testJson")
        }
    }
}
