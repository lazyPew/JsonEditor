import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

Page {
    id: root

    ColumnLayout{
        anchors.fill: parent

        ListView{
            id: valuesView
            Layout.fillHeight: true
            Layout.margins: 4
            interactive: false
            spacing: 2
            model: panel.valuesListModel
            delegate: Label{
                text: nameRole + deviceRole
            }


        }
    }

}
