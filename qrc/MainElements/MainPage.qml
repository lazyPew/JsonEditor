import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

import "../ControlElements"

Page {
    id: root

    header: RowLayout{
        Layout.fillWidth: true
        height: 50
        ToolButton{
            id: exitButton
            Layout.fillWidth: true
            Layout.preferredHeight: 43
            text: "Добавить пустое значение"
            scale: mainWindow.iconScaler
            icon.source: "/Icons/add"
            onClicked: addValue()
        }
    }
    ListView{
        id: valuesView
        anchors.fill: parent
        clip: true
        spacing: 20

        Layout.margins: 4
        interactive: false
        ScrollBar.vertical: ScrollBar {
            id:scroll
            active: ScrollBar.AlwaysOn
            wheelEnabled: true

        }

        delegate:
            ElementDelegate{
            width: parent.width - scroll.width
            onNullValue: nullIsNotAllowedPopup.open()
            onDeviceChanged: {
                valuesView.forceLayout()
            }
            onDeleteValue: removeValue(index)

        }
        section.property: "deviceRole"
        section.criteria: ViewSection.FullString
        section.labelPositioning:
            ViewSection.InlineLabels | ViewSection.CurrentLabelAtStart
        section.delegate: Control{
            width: parent.width - scroll.width

            topPadding: 5
            bottomPadding: 5

            background: Rectangle{
                color: Material.background
                border.width: 1
                border.color: "white"
            }

            contentItem: Label{
                text: section
                font.pixelSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignHCenter

            }
        }
    }
    Component.onCompleted: valuesView.model = panel.valuesListModel
    //    }
    Popup{
        id: nullIsNotAllowedPopup
        x: (mainWindow.width - width ) / 2
        y: (mainWindow.contentItem.height - height) / 2
        width: mainWindow.width / 2
        modal: true
        focus: true
        contentItem: ColumnLayout{
            Layout.fillWidth: true
            Label{
                Layout.fillWidth: true
                font.pixelSize: 20
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideMiddle
                text: "Данное значение не может быть пустым!"
            }
            Button{
                text: "OK"
                Layout.preferredWidth: 80
                Layout.alignment: Qt.AlignHCenter
                height:implicitHeight
                onClicked: nullIsNotAllowedPopup.close()
            }
        }
    }
    function addValue(){
        panel.addEmptyValueObject()
        valuesView.forceLayout()
    }
    function removeValue(index){
        panel.removeValueObject(index)
        valuesView.forceLayout()
    }
}
