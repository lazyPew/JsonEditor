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
            text: "Добавить тип enum"
            icon.source: "/Icons/add"
            onClicked: addEnum()
        }
    }
    ListView{
        id: enumsView
        anchors.fill: parent
        spacing: 20
        model:panel.listOfEnums()
        interactive: false

        ScrollBar.vertical: ScrollBar {
            id:scroll
            active: ScrollBar.AlwaysOn
            wheelEnabled: true

        }

        delegate: ItemDelegate{
            width: parent.width - scroll.width
            contentItem: ColumnLayout{
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
        }

    }
    function addEnum(){
        panel.addCustomEnum()
        enumsView.forceLayout()
    }
}
