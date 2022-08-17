import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Page {
    id: root

    signal goToMain()
    signal deviceRemoved()

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
                    onClicked: {
                        removeDevicePopup.deviceIndex = index
                        removeDevicePopup.open()
                    }
                }
            }
        }
    }

    Popup{
        id: removeDevicePopup
        x: (mainWindow.width - width ) / 2
        y: (mainWindow.contentItem.height - height) / 2
        width: mainWindow.width / 2
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose

        property int deviceIndex
        contentItem: ColumnLayout{
            Layout.fillWidth: true
            height: implicitHeight
            Label{
                Layout.fillWidth: true
                font.pixelSize: 15
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideMiddle
                text: "При удалении данного устройства будут также удалены все связанные с ним значения.\nПодтвердить удаление?"
            }
            RowLayout {
                id: buttonsRow
                Layout.alignment: Qt.AlignHCenter

                Button {
                    text: "ПОДТВЕРДИТЬ"
                    Layout.preferredWidth: 150
                    font.pixelSize: 15
                    onClicked: {
                        panel.removeDevice(removeDevicePopup.deviceIndex);
                        removeDevicePopup.close();
                    }
                }
                Button {
                    text: "ОТМЕНА"
                    Layout.preferredWidth: 150
                    font.pixelSize: 15
                    onClicked: {
                        removeDevicePopup.close();
                    }
                }
            }
        }
    }


    Connections{
        target: newDevicePopup
        onClosed: devicesView.forceLayout()
    }
}
