import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Page {
    id: root

    signal goToMain()

    header: RowLayout{
        Layout.fillWidth: true
        height: 50
        ToolButton{
            id: addEnumButton
            Layout.fillWidth: true
            Layout.preferredHeight: 43
            text: "Добавить устройство"
            icon.source: "/Icons/add"
            onClicked: newDevicePopup.open()
        }

        ToolButton{
            id:nextPage
            text: "Назад ->"
            Layout.preferredHeight: 43
            Layout.fillWidth: true
            onClicked: goToMain()
        }
    }
    ListView{
        id: devicesView
        anchors.fill: parent
        spacing: 10
        model: panel.listOfDevices
        interactive: false

        ScrollBar.vertical: ScrollBar {
            id:scroll
            active: ScrollBar.AlwaysOn
            wheelEnabled: true

        }

        delegate: ItemDelegate{
            width: parent.width - scroll.width
            contentItem: RowLayout{
                Layout.fillWidth: true
                Label{
                    Layout.fillWidth:true
                    text: modelData
                    wrapMode: Text.WordWrap
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 15
                }
                ToolButton{
                    Layout.alignment: Qt.AlignRight
                    enabled: panel.listOfDevices.length > 1
                    scale: mainWindow.iconScaler
                    icon.source: "/Icons/delete"
                    icon.color: enabled ? "red" : "grey"
                    width:implicitWidth
                    onClicked: panel.removeDevice(index)
                }
            }
        }
    }
}
