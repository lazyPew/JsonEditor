import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Popup{
    id: newEnumPopup
    x: (mainWindow.width - width ) / 2
    y: (mainWindow.contentItem.height - height) / 2
    width: mainWindow.width / 2
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    signal enumAdded()

    contentItem: ColumnLayout{
        Layout.fillWidth: true
        height: implicitHeight
        Label{
            Layout.fillWidth: true
            font.pixelSize: 20
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideMiddle
            text: "Введите имя добавляемого enum:"
        }

        Label {
            id: nameExistsLabel
            visible: false
            text: "Данный enum уже существует"
            font.family: "fontello"
            height: implicitHeight
            color: "orange"
            Layout.fillWidth: true
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
        }

        Label {
            id: endsWithEnumLabel
            visible: false
            text: "Имя должно заканчиваться на \"_enum\""
            font.family: "fontello"
            height: implicitHeight
            color: "orange"
            Layout.fillWidth: true
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
        }

        TextField{
            id: textField
            focus: true
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
                    addEnum(textField.text);
                }
            }
            Button {
                text: "ОТМЕНА"
                Layout.preferredWidth: 150
                font.pixelSize: 15
                onClicked: {
                    newEnumPopup.close();
                }
            }
        }
    }
    onClosed: textField.text = ""

    Timer{
        id: nameExistsTimer
        interval: 3000
        onTriggered: nameExistsLabel.visible = false
    }

    Timer{
        id: endsWithEnumTimer
        interval: 3000
        onTriggered: endsWithEnumLabel.visible = false
    }

    function addEnum(text){
        if(text.endsWith("_enum")){
            if(!panel.addCustomEnum(text)){
                nameExistsLabel.visible = true
                nameExistsTimer.restart()
            }
            else{
                enumAdded()
                newEnumPopup.close()
            }
        }
        else{
            endsWithEnumLabel.visible = true
            endsWithEnumTimer.restart()
        }
    }
}
