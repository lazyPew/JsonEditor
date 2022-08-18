import QtQuick 2.10
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import "../Popups"
import ValueObjectsModule 1.0

ItemDelegate{
    id: delegate

    // TODO remake this class using dynamic creation with createQmlObject()

    property int fontSize: 15
    property bool editable: isEditableRole
    property bool canBeNull: isNullRole

    property var deviceValue: deviceRole

    signal nullValue()
    signal deviceChanged()
    signal deleteValue()
    signal outOfRange()

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
                    onActivated: {
                        typeCodeRole = currentIndex
                        enumCombo.currentIndex = 0
                        clearTextFields()
                    }
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
                    currentIndex: panel.listOfEnums.indexOf(typeRole)
                    model: panel.listOfEnums
                    enabled: isEditableRole
                    onActivated: {
                        typeRole = currentText
//                        console.log(typeRole)
//                        console.log(typeCodeRole)
                        enumValueCombo.currentIndex = 0
                        defaultCombo.currentIndex = 0
                    }
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
                        id: valueField
                        Layout.fillWidth:true
                        visible: typeCombo.currentIndex !== ValueObject.EnumType
                        color: textColor
                        text: JSON.stringify(valueRole)
                        onEditingFinished: {
                            if(!canBeNull && !text.length){
                                text = JSON.stringify(valueRole)
                                nullValue()
                            }

                            else if(isNumberType() && checkRange(text)){
                                console.log("check" + checkRange(text))
                                console.log("isnumb" + isNumberType())
                                text = JSON.stringify(valueRole)
                                outOfRange()
                            }
                            else
                                valueRole = JSON.parse(text)
                        }


                    }

                    ComboBox{
                        id: enumValueCombo
                        visible: typeCombo.currentIndex === ValueObject.EnumType
                        Layout.fillWidth:true
                        model: panel.valuesListOfEnum(enumCombo.currentText)
                        displayText: JSON.stringify(valueRole)
                        onActivated: {
                            console.log(valueRole )

                            displayText = currentText
                            valueRole = JSON.parse(displayText)
                            console.log(valueRole )
                        }
                    }
                }


                Label{
                    id:defaultLabel
                    text: "Значение по умолчанию : "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                RowLayout{
                    Layout.fillWidth:true
                    TextField{
                        id: defaultField
                        Layout.fillWidth:true
                        visible: typeCombo.currentIndex !== ValueObject.EnumType
                        color: textColor
                        text: defaultValueRole !== undefined ? (JSON.stringify(defaultValueRole)) : ""
                        onEditingFinished: {
                            defaultValueRole = text
                        }
                    }

                    ComboBox{
                        id: defaultCombo
                        visible: typeCombo.currentIndex === ValueObject.EnumType
                        Layout.fillWidth:true
                        model: panel.valuesListOfEnum(enumCombo.currentText)
                        displayText: JSON.stringify(defaultValueRole)
                        onActivated: {
                            defaultValueRole = JSON.parse(currentText)
                            displayText = JSON.stringify(defaultValueRole)
                        }
                        onVisibleChanged: {
                            if(visible)
                                currentIndex = 1
                        }
                    }
                }


                Label{
                    id:regexLabel
                    visible: isStringType()
                    text: "Регулярное выражение: "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    id:regexField
                    visible: isStringType()
                    text: JSON.stringify(regexRole)
                    Layout.fillWidth:true
                    enabled: editable
                    color: textColor
                    onEditingFinished: {
                        regexRole = text
                    }
                }

                Label{
                    id: minValueLabel
                    visible: isNumberType()
                    text: "Мин. значение диапазона: "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    id: minValueField
                    visible: isNumberType()
                    text: minRole !== undefined ? (minRole) : ""
                    Layout.fillWidth:true
                    enabled: editable
                    color: textColor
                    onEditingFinished: {
                        minRole = text
                    }
                    validator: DoubleValidator{notation: DoubleValidator.StandardNotation}
                }

                Label{
                    id: maxValueLabel
                    visible: isNumberType()
                    text: "Макс. значение диапазона: "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    id: maxValueField
                    visible: isNumberType()
                    text: maxRole !== undefined ? (maxRole) : ""
                    Layout.fillWidth:true
                    enabled: editable
                    color: textColor
                    onEditingFinished: {
                        maxRole = text
                    }
                    validator: DoubleValidator{notation: DoubleValidator.StandardNotation}
                }

                Label{
                    id:exceptLabel
                    visible: isNumberType()
                    text: "Исключение из диапазона: "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    id:exceptField
                    visible: isNumberType()
                    text: JSON.stringify(exceptRole)
                    Layout.fillWidth:true
                    enabled: editable
                    color: textColor
                    onEditingFinished: {
                        exceptRole = text
                    }
                }

                Label{
                    id:unitsLabel
                    visible: isNumberType()
                    text: "Единицы измерения: "
                    wrapMode: Text.WordWrap
                    Layout.leftMargin: 10
                    font.pixelSize: fontSize
                }

                TextField{
                    id:unitsField
                    visible: isNumberType()
                    text: JSON.stringify(unitsRole)
                    Layout.fillWidth:true
                    enabled: editable
                    color: textColor
                    onEditingFinished: {
                        unitsRole = text
                    }
                }
            }

            Item{
                Layout.fillWidth: true
            }

            ToolButton{
                Layout.alignment: Qt.AlignRight
                scale: mainWindow.iconScaler
                enabled: editable && valueField.text.length
                icon.source: canBeNull
                      ? "/Icons/null"
                      : "/Icons/nonull"
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
                    enableForCombos()
                    isEditableRole = editable
                }
            }

            ToolButton{
                Layout.alignment: Qt.AlignRight
                scale: mainWindow.iconScaler
                icon.source: "/Icons/delete"
                icon.color: "red"
                width:implicitWidth
                onClicked:
                {
                    deleteValue()
                }

            }
        }

        Label{
            id:descLabel
            text: "Описание : "
            wrapMode: Text.WordWrap
            Layout.leftMargin: 10
            font.pixelSize: fontSize
        }

        TextArea{
            id:descArea
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

    function clearTextFields(){
        valueField.text = ""//JSON.stringify(valueRole)
        defaultField.text = ""//JSON.stringify(defaultRole)
        maxValueField.text = ""//JSON.stringify(maxRole)
        minValueField.text = ""//JSON.stringify(minRole)
        unitsField.text = ""//JSON.stringify(unitsRole)
        regexField.text = ""//JSON.stringify(regexRole)
    }

//    function setValue(text){
//        if(!canBeNull && !text.length){
//            valueRole = JSON.stringify(valueRole)
//            nullValue()
//        }
//        else if(!checkRange(text)){
//            console.log()
//            outOfRange()
//        }
//        else
//            valueRole = text
//        console.log("!checkRange(text)" + !checkRange(text))
//    }

    function checkRange(text){
//        for(var i = 0; i < exceptRole.length; ++i)
//            console.log(exceptRole[i])
//        console.log(typeof(exceptRole))
//        console.log("value = " + text)
//        console.log("max = " + maxRole)
//        console.log("min = " + minRole)
//        console.log("except = " + exceptRole)
//        console.log("text morethan maxRole " + (text > maxRole))
//        console.log("text lessthan minRole " + (text < minRole))
//        console.log("index in except " + exceptRole.indexOf(JSON.parse(text)))
        if(maxRole !== undefined && text > maxRole){
            valueRole = (maxRole)
            return true
        }
        if(minRole !== undefined && text < minRole){
            valueRole = (minRole)
            return true
        }
        if(exceptRole !== undefined && exceptRole.indexOf(JSON.parse(text)) > -1){
            return true
        }
        console.log("check is success")
        return false

    }

    function isStringType(){
        if(typeCombo.currentIndex === ValueObject.IpStringType
                || typeCombo.currentIndex === ValueObject.DomenType
                || typeCombo.currentIndex === ValueObject.GnssStringType)
            return true
        else
            return false
    }

    function isNumberType(){
        if(typeCombo.currentIndex === ValueObject.IntType
                || typeCombo.currentIndex === ValueObject.FloatType
                || typeCombo.currentIndex === ValueObject.IpDigitType)
            return true
        else
            return false
    }
}
