import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


ItemDelegate{
    id: delegate
    property int fontSize: 15
    property bool editable: isEditableRole

    contentItem: RowLayout{
        Layout.fillWidth:true
        Layout.fillHeight:true
        GridLayout{
            columns: 2
            Layout.fillWidth:true
            Layout.fillHeight:true
            Label{
                text: "name = "
                wrapMode: Text.WordWrap
                Layout.leftMargin: 10
                font.pixelSize: fontSize
            }
            TextEdit{
                text: nameRole
                enabled: editable
                color: "white"
                onEditingFinished: {
                    console.log(text)
                    nameRole = text}
            }
            Label{
                text: "type = "
                wrapMode: Text.WordWrap
                Layout.leftMargin: 10
                font.pixelSize: fontSize
            }
            ComboBox{
                id:combo
                currentIndex: typeCodeRole
                enabled: isEditableRole
                model: valueTypes
                onCurrentIndexChanged: typeCodeRole = currentIndex
            }
//            TextEdit{
//                color: "white"
//                text: typeRole
//            }
            Label{
                text: "value = "
                wrapMode: Text.WordWrap
                Layout.leftMargin: 10
                font.pixelSize: fontSize
            }
            TextEdit{
                color: "white"
                text: JSON.stringify(valueRole)
                enabled: editable
            }

        }
        ToolButton{
            Layout.alignment: Qt.AlignRight
            icon.source: editable
                  ? "/Icons/unlock"
                  : "/Icons/lock"
            width:implicitWidth
            onClicked:
            {
                editable = !editable
                combo.enabled = editable
                isEditableRole = editable
            }
        }

    }
//    Component.onCompleted: console.log(JSON.stringify(valueRole))



//    RowLayout{
//        id: row
//        Layout.fillWidth: true
//        Layout.preferredHeight: parent.height
//        Layout.maximumHeight: parent.height

//        ColumnLayout{
//            id: nameSerialColumn
//            Layout.alignment: Qt.AlignTop
//            Layout.preferredWidth: delegate.width / 2

//            Layout.margins: {
//                leftMargin:5
//            }

//            spacing:1
//            Label{
//                text: iconSet.drive + " " + diskName
//                font.pixelSize: 20
//                font.bold: true
//                height:2
//            }

//            Item{
//                Layout.fillHeight: true
//            }

//            Label{
//                text:"Серийный номер: " + serial
//                Layout.fillHeight: true
//                Layout.fillWidth: true
//                font.pixelSize: 15
//                wrapMode: Text.Wrap
//                horizontalAlignment: Text.AlignLeft
//                verticalAlignment: Text.AlignVCenter
//                elide: Text.ElideMiddle
//            }
//        }

//        Item{
//            Layout.fillWidth: true
//        }

//        ColumnLayout{
//            Layout.preferredWidth: delegate.width/2

//            Layout.margins: {
//                rightMargin:10
//                topMargin:5
//                bottomMargin:5
//            }
//            RowLayout{
//                Label{
//                    text: (available < 1024*1024)
//                        ?
//                            (used/(1024)).toFixed(2) + " / " + (maxSize/(1024)).toFixed(2) + " GB"
//                        : (used/(1024*1024)).toFixed(2) + " / " + (maxSize/(1024*1024)).toFixed(2) + " TB"
//                    font.pixelSize: 15

//                }
//                Item{
//                    Layout.fillWidth: true
//                }
//                Label{
//                    text:"(" + percent + "%)"
//                    font.pixelSize: 15
//                }
//            }

//            Item{
//                Layout.fillHeight: true
//            }
//            ProgressBar {
//                id: sizeLine
//                value: percent / 100
//                padding: 2
//                Layout.fillWidth:true

//                background: Rectangle {
//                    implicitHeight: 20
//                    color: colorPalette.availableSizeColor
//                    radius: 5
//                }

//                contentItem: Item {
//                    Rectangle {
//                        width: sizeLine.visualPosition * parent.width
//                        height: parent.height
//                        radius: 4
//                        color: (percent < 85)
//                               ? colorPalette.mainColor : colorPalette.attentionColor
//                    }
//                }
//            }
//        }
//    }
}

//ItemDelegate{
//    id: delegate
//    width: parent.width
//    property int fontSize: 15

//    contentItem: GridLayout{
//        columns: 2
//        Label{
//            text: "name = "
//            wrapMode: Text.WordWrap
//            Layout.leftMargin: 10
//            font.pixelSize: fontSize
//        }
//        TextEdit{
//            text: nameRole
//            onEditingFinished: {
//                console.log(text)
//                nameRole = text}
//        }
//        Label{
//            text: "type = "
//            wrapMode: Text.WordWrap
//            Layout.leftMargin: 10
//            font.pixelSize: fontSize
//        }
//        TextEdit{
//            text: typeRole
//        }
//        Label{
//            text: "value = "
//            wrapMode: Text.WordWrap
//            Layout.leftMargin: 10
//            font.pixelSize: fontSize
//        }
//        TextEdit{
//            text: JSON.stringify(valueRole)
//        }
//    }

//    Component.onCompleted: console.log(JSON.stringify(valueRole))
//}
