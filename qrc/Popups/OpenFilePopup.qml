import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Popup {
    id: popup
    x: (mainWindow.width - width ) / 2
    y: (mainWindow.contentItem.height - height) / 2
    width: mainWindow.width / 2
    height: contentColumn.implicitHeight + topPadding + bottomPadding
    modal: true
    focus: true

    contentItem: ColumnLayout {
        id: contentColumn
        spacing: 10
        Layout.fillWidth: true

        Label {
           id: submitText
           Layout.fillWidth: true
           font.pixelSize: 20
           wrapMode: Text.Wrap
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideMiddle
           text: "Введите путь до файла"
        }


        Label {
           id: errorText
           Layout.fillWidth: true
           font.pixelSize: 13
           wrapMode: Text.Wrap
           visible: false
           color: "orange"
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           elide: Text.ElideMiddle
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
                Layout.preferredWidth: 150
                font.pixelSize: 15
                onClicked: {
                    confirmOpen();
                }
            }

            Button {
                text: "ОТМЕНА"
                Layout.preferredWidth: 150
                font.pixelSize: 15
                onClicked: {
                    popup.close();
                }
            }
        }
    }

    function confirmOpen() {
        panel.openJsonFile(textField.text);
    }

    Connections{
        target: panel
        onOpeningFailed:{
            errorText.text = errorExplanation
            errorText.visible = true
            errorTimer.restart()
        }
        onFileNameChanged: popup.close();
    }

    Timer{
        id: errorTimer
        interval: 3000
        onTriggered: errorText.visible = false
    }
}
