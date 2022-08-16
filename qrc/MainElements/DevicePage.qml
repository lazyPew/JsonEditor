import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2


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
                    onClicked:
                    {
                        panel.removeDevice(index)
                    }
                }
            }
        }

    }

    Popup{
        id: newDevicePopup
        x: (mainWindow.width - width ) / 2
        y: (mainWindow.contentItem.height - height) / 2
        width: mainWindow.width / 2
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose

        contentItem: ColumnLayout{
            Layout.fillWidth: true
            Label{
                Layout.fillWidth: true
                font.pixelSize: 20
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideMiddle
                text: "Введите имя добавляемого устройства:"
            }

            TextField{
                id: textField
                Layout.fillWidth: true
            }
            RowLayout {
                id: buttonsRow
                Layout.alignment: Qt.AlignHCenter

                Button {
                    text: "ПОДТВЕРДИТЬ"
                    enabled: textField.text.length
                    Layout.preferredWidth: 150
                    font.pixelSize: 15
                    onClicked: {
                        addDevice(textField.text);
                        newDevicePopup.close();
                    }
                }
                Button {
                    text: "ОТМЕНА"
                    Layout.preferredWidth: 150
                    font.pixelSize: 15
                    onClicked: {
                        newDevicePopup.close();
                    }
                }
            }
        }
        onClosed: textField.text = ""

    }
    function addDevice(text){
        panel.addDevice(text)
        devicesView.forceLayout()
    }
}
