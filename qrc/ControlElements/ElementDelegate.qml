import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11


ItemDelegate{
    id: delegate
    property int fontSize: 15
    property bool editable: isEditableRole
    property bool canBeNull: isNullRole
    property var textColor: editable
                            ? "white"
                            : "grey"

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
                color: textColor
                onEditingFinished: {
                    nameRole = text
                }
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

            Label{
                text: "value = "
                wrapMode: Text.WordWrap
                Layout.leftMargin: 10
                font.pixelSize: fontSize
            }
            TextEdit{
                color: textColor
                text: JSON.stringify(valueRole)
                enabled: editable
            }

        }
        Item{
            Layout.fillWidth: true
        }
        ToolButton{
            Layout.alignment: Qt.AlignRight
            scale: mainWindow.iconScaler
            enabled: editable
            icon.source: canBeNull
                  ? "/Icons/null2"
                  : "/Icons/nonull2"
            width:implicitWidth
            onClicked:
            {
                canBeNull = !canBeNull
                isNullRole = canBeNull
            }
        }

//        ComboBox{
//            currentIndex: deviceRole
//            enabled: editable
//            model: panel.listOfDevices
//            onCurrentIndexChanged: {
//                console.log(currentIndex)
//                console.log(currentText)
//                console.log(deviceRole)
//                deviceRole = currentIndex
//            }
//        }

        ToolButton{
            Layout.alignment: Qt.AlignRight
            scale: mainWindow.iconScaler
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
}
