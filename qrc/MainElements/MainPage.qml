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
            spacing: 10
            model: panel.valuesListModel
            delegate: Label{
                text: "name = " + nameRole +
                      " type = " + typeRole +
                      " value = " + valueRole
                font.pixelSize: 15
            }
            section.property: "deviceRole"
            section.criteria: ViewSection.FullString
            section.delegate: Control{

                topPadding: 10
                bottomPadding: 5

                background: Rectangle{
                    color: "transparent"
                    border.width: 1
                    border.color: "white"
                }
                contentItem: Label{
                    text: section
                    font.pixelSize: 15
                }
            }

        }
    }

}
