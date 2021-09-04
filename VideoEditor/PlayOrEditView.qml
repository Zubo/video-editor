import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    RowLayout {
        anchors.centerIn: parent
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        spacing: 40

        Button {
            icon.source: "qrc:/Images/raw-videos.png"
            icon.color: "transparent"
            icon.width: mainView.width / 3
            icon.height: mainView.height / 3

            text: qsTr("Raw Videos")

            onClicked: stack.push(mainView.rawVideoView)

            ToolTip.visible: hovered
            ToolTip.text: qsTr("Edit or play raw videos")
        }

        Button {
            icon.source: "qrc:/Images/edited-videos.png"
            icon.color: "transparent"
            icon.width: mainView.width / 3
            icon.height: mainView.height / 3

            text: qsTr("Edited Videos")

            onClicked: stack.push(mainView.editedVideoView)

            ToolTip.visible: hovered
            ToolTip.text: qsTr("Play edited videos")
        }
    }
}
