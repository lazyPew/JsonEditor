import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.5

ItemDelegate{
    id: delegate
    width: parent.width
    property int fontSize: 15

    contentItem: GridLayout{
        columns: 2
        Label{
            text: "name = "
            wrapMode: Text.WordWrap
            Layout.leftMargin: 10
            font.pixelSize: fontSize
        }
        TextEdit{
            text: nameRole
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
        TextEdit{
            text: typeRole
        }
        Label{
            text: "value = "
            wrapMode: Text.WordWrap
            Layout.leftMargin: 10
            font.pixelSize: fontSize
        }
        TextEdit{
            text: JSON.stringify(valueRole)
        }
    }

    Component.onCompleted: console.log(JSON.stringify(valueRole))
}
