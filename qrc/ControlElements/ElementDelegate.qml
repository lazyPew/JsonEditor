import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import "../Popups"
import ValueObjectsModule 1.0

ItemDelegate{
    id: delegate
    property int fontSize: 15
    property bool editable: isEditableRole
    property bool canBeNull: isNullRole

    property var deviceValue: deviceRole

    signal nullValue()
    signal deviceChanged()

    property var textColor: editable
                            ? "white"
                            : "grey"

    contentItem: ColumnLayout{
        Layout.fillWidth:true
        Layout.fillHeight:true
        RowLayout{
            Layout.fillWidth:true
            Layout.fillHeight:true
            GridLayout{
                columns: 2
                Layout.fillWidth:true
                Layout.fillHeight:true
                Label{
                    text: "Устройство : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }
                ComboBox{
                    id:deviceCombo
                    displayText: deviceRole
                    model: panel.listOfDevices
                    onActivated: {
                        if(deviceRole != currentText){
                            deviceRole = currentText
                            displayText = currentText
                            deviceChanged()
                        }
                    }
                }
                Label{
                    text: "Имя значения : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    text: nameRole
                    enabled: editable
                    color: textColor
                    onEditingFinished: {
                        nameRole = text
                    }
                }

                Label{
                    text: "Тип значения : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                ComboBox{
                    id:typeCombo
                    currentIndex: typeCodeRole
                    enabled: isEditableRole
                    model: valueTypes
                    onCurrentIndexChanged: typeCodeRole = currentIndex
                }

                Label{
                    text: "Значение : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    id: valueText
                    color: textColor
                    text: JSON.stringify(valueRole)
                    enabled: editable
                    onEditingFinished: {
                        if(!canBeNull && !text.length){
                            text = JSON.stringify(valueRole)
                            nullValue()
                        }else
                            valueRole = text
                    }
                }

            }
            Item{
                Layout.fillWidth: true
            }

            ToolButton{
                Layout.alignment: Qt.AlignRight
                scale: mainWindow.iconScaler
                enabled: editable && valueText.text.length
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
                    deviceCombo.enabled = editable
                    typeCombo.enabled = editable
                    isEditableRole = editable
                }
            }
        }
        Label{
            text: "Описание : "
            wrapMode: Text.WordWrap
            Layout.leftMargin: 10
            font.pixelSize: fontSize
        }

        TextArea{
            wrapMode: TextEdit.Wrap

            Layout.fillWidth:true
            clip: true
            onEditingFinished: {
                descRole = text
            }
        }
    }
}
