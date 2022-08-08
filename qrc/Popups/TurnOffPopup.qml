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

    leftPadding: 10
    rightPadding: leftPadding

    contentItem: ColumnLayout {
        id: contentColumn
        spacing: 10
        focus: true
        Layout.fillWidth: true

         Label {
            id: submit_text
            Layout.fillWidth: true
            font.pixelSize: 20
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideMiddle
            text: "Подтвердите выход из программы"

        }
         RowLayout {
             id: buttonsRow

             spacing: 15
             Layout.fillWidth: true
             Layout.preferredHeight: 50
             Layout.alignment: Qt.AlignHCenter

             Button {
                 text: "ПОДТВЕРДИТЬ"
                 Layout.preferredWidth: 150
//                 Layout.fillWidth: true
                 font.pixelSize: 15
                 onClicked: {
                     confirmTurnOff();
                 }
             }

             Button {
                 text: "ОТМЕНА"
                 Layout.preferredWidth: 150
//                 Layout.fillWidth: true
                 font.pixelSize: 15
                 onClicked: {
                     popup.close();
                 }
             }
         }
    }

    function confirmTurnOff() {
        panel.turnOff();
        popup.close();
    }
}
