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
                    Layout.fillWidth:true
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
                    Layout.fillWidth:true
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
                    Layout.fillWidth:true
                    currentIndex: typeCodeRole
                    enabled: isEditableRole
                    model: valueTypes
                    onActivated: typeCodeRole = currentIndex
                }


                Label{
                    text: "Тип Enum : "
                    visible: typeCombo.currentIndex === ValueObject.EnumType
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                ComboBox{
                    id:enumCombo
                    visible: typeCombo.currentIndex === ValueObject.EnumType
                    Layout.fillWidth:true
                    currentIndex: panel.listOfEnums().indexOf(typeRole)
                    model: panel.listOfEnums()
                    enabled: isEditableRole
                    onActivated: typeRole = currentIndex
                }

                Label{
                    text: "Значение : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                RowLayout{
                    Layout.fillWidth:true
                    TextField{
                        id: valueText
                        Layout.fillWidth:true
                        visible: typeCombo.currentIndex !== ValueObject.EnumType
                        color: textColor
                        text: JSON.stringify(valueRole)
                        onEditingFinished: {
                            if(!canBeNull && !text.length){
                                text = JSON.stringify(valueRole)
                                nullValue()
                            }else
                                valueRole = text
                        }
                    }
                    ComboBox{
                        id: enumValueCombo
                        visible: typeCombo.currentIndex === ValueObject.EnumType
                        Layout.fillWidth:true
                        model: panel.valuesListOfEnum(enumCombo.currentText)
                        displayText: JSON.stringify(valueRole)
                        onActivated: {
                            valueRole = JSON.parse(currentText)
                            displayText = JSON.stringify(valueRole)
                        }

                    }
                }


                Label{
                    text: "Значение по умолчанию : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                RowLayout{
                    Layout.fillWidth:true
                    TextField{
                        id: defaultText
                        Layout.fillWidth:true
                        visible: typeCombo.currentIndex !== ValueObject.EnumType
                        color: textColor
                        text: JSON.stringify(defaultRole)
                        onEditingFinished: {
                            defaultRole = text
                        }
                    }
                    ComboBox{
                        id: defaultCombo
                        visible: typeCombo.currentIndex === ValueObject.EnumType
                        Layout.fillWidth:true
                        model: panel.valuesListOfEnum(enumCombo.currentText)
                        displayText: JSON.stringify(defaultRole)
                        onActivated: {
                            defaultRole = JSON.parse(currentText)
                            displayText = JSON.stringify(defaultRole)
                        }

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
                    console.log(panel.listOfEnums)
                    console.log(panel.valuesListOfEnum())
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
                    enableForCombos()
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
            enabled: editable
            Layout.fillWidth:true
            clip: true
            onEditingFinished: {
                descRole = text
            }
        }
    }
    function enableForCombos(){
        deviceCombo.enabled = editable
        typeCombo.enabled = editable
        enumCombo.enabled = editable
        enumValueCombo.enabled = editable

    }
}
