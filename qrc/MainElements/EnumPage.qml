import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2


Page {
    id: root

    ListView{
        id: valuesView
        anchors.fill: parent
        spacing: 20
        model:panel.listOfEnums()

    }
}
