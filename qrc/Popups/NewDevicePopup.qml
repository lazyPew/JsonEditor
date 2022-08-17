import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

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

    function addDevice(text){
        panel.addDevice(text)
        devicesView.forceLayout()
    }
}
