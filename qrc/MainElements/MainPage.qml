import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.5

import "../ControlElements"

Page {
    id: root

//    ColumnLayout{

        ListView{
            anchors.fill: parent
//            width: parent.width
            clip: true
//            height: implicitHeight
            ScrollBar.vertical: ScrollBar {
                id:scroll
                wheelEnabled: true
            }
            id: valuesView
            Layout.margins: 4
            interactive: false
            spacing: 10
            model: panel.valuesListModel
            delegate: ElementDelegate{
                width: parent.width - scroll.width
            }
            section.property: "deviceRole"
            section.criteria: ViewSection.FullString
            section.delegate: Control{

                topPadding: 5
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
//    }

}
