import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    RowLayout {
        anchors.centerIn: parent
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        spacing: 40

        Button {
            icon.source: "qrc:/Images/raw-videos.png"
            icon.color: transparent
            icon.width: 100
            icon.height: 100

            text: qsTr("Raw Videos")

            ToolTip.visible: hovered
            ToolTip.text: qsTr("Edit or play raw videos")
        }

        Button {
            icon.source: "qrc:/Images/edited-videos.png"
            icon.color: transparent
            icon.width: 100
            icon.height: 100

            text: qsTr("Edited Videos")

            ToolTip.visible: hovered
            ToolTip.text: qsTr("Play edited videos")
        }
    }
}
