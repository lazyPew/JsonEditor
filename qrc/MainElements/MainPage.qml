import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

import "../ControlElements"

Page {
    id: root

    Flickable{
        id:mainColumn
        anchors.fill: parent

        ListView{
            id: valuesView
            anchors.fill: parent

            clip: true
            spacing: 20
            ScrollBar.vertical: ScrollBar {
                id:scroll
                wheelEnabled: true
            }
            Layout.margins: 4
            interactive: false
            delegate: ElementDelegate{
                width: parent.width - scroll.width
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
    }
    Component.onCompleted: valuesView.model = panel.valuesListModel

}
