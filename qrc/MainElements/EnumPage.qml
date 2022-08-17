import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2
import Qt.labs.handlers 1.0

Page {
    id: root

    signal goToMain()

    header: RowLayout{
        Layout.fillWidth: true
        height: 50
        ToolButton{
            id:nextPage
            text: "<- Назад"
            Layout.preferredHeight: 43
            Layout.fillWidth: true
            onClicked: goToMain()
        }
        ToolButton{
            id: addEnumButton
            Layout.fillWidth: true
            Layout.preferredHeight: 43
            text: "Добавить новое перечисление"
            icon.source: "/Icons/add"
            onClicked: newEnumPopup.open()

        }
    }
    ListView{
        id: enumsView
        anchors.fill: parent
        spacing: 20
        model:panel.listOfEnums
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
                ColumnLayout{
                    Layout.fillWidth:true
                    Layout.fillHeight:true
                    TapHandler{
                        onTapped: area.focus = false}
                    Label{
                        Layout.fillWidth:true
                        text: modelData
                        wrapMode: Text.WordWrap
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 20
                    }
                    TextArea{
                        id: area
                        Layout.fillWidth:true
                        text: JSON.stringify(panel.valuesListOfEnum(modelData))
                        onEditingFinished: panel.updateCustomEnum(modelData, JSON.parse(text))
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignRight
                    scale: mainWindow.iconScaler
                    icon.source: "/Icons/delete"
                    icon.color: enabled ? "red" : "grey"
                    width:implicitWidth
                    onClicked: {
                        removeEnumPopup.enumName = modelData
                        removeEnumPopup.open()
                    }
                }
            }
        }
    }


    Popup{
        id: removeEnumPopup
        x: (mainWindow.width - width ) / 2
        y: (mainWindow.contentItem.height - height) / 2
        width: mainWindow.width / 2
        height: contentColumn.implicitHeight
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose

        property string enumName
        contentItem: ColumnLayout{
            id: contentColumn
            Layout.fillWidth: true
            Label{
                Layout.fillWidth: true
                font.pixelSize: 15
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideMiddle
                text: "При удалении данного перечисления будут также удалены все связанные с ним значения.\nПодтвердить удаление?"
            }

            RowLayout {
                id: buttonsRow
                Layout.alignment: Qt.AlignHCenter

                Button {
                    text: "ПОДТВЕРДИТЬ"
                    Layout.preferredWidth: 150
                    font.pixelSize: 15
                    onClicked: {
                        panel.removeCustomEnum(removeEnumPopup.enumName);
                        removeEnumPopup.close();
                    }
                }

                Button {
                    text: "ОТМЕНА"
                    Layout.preferredWidth: 150
                    font.pixelSize: 15
                    onClicked: {
                        removeEnumPopup.close();
                    }
                }
            }
        }
    }

    Connections{
        target: newEnumPopup
        onEnumAdded: enumsView.forceLayout()

    }
}
