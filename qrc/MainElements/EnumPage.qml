import QtQuick 2.11
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
        id: valuesView
        anchors.fill: parent
        spacing: 20
        model:panel.listOfEnums()
        delegate: Label{
            text: modelData
        }
    }
    function addEnum(){
        panel.addEmptyValueObject()
        valuesView.forceLayout()
    }
}
