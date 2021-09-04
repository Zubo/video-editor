import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: mainView
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property Component playOrEditView: PlayOrEditView{}
    property Component rawVideoView: VideoDirectoryView{ directoryPath: executableRoot + "/Videos/Raw"; showEdit: true }
    property Component editedVideoView: VideoDirectoryView{ directoryPath: executableRoot + "/Videos/Edited" }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action { text: "Import raw videos..."; }
        }
    }

    ColumnLayout {
        Rectangle {
            id: backButtonBar
            Layout.preferredWidth: mainView.width
            Layout.preferredHeight: backButton.height
            Layout.minimumHeight: 20

            Button {
                id: backButton
                text: "Back"
                enabled: stack.depth > 1
                onClicked: stack.pop()
            }
        }

        Rectangle {
            Layout.preferredWidth: mainView.width
            Layout.preferredHeight: mainView.height - menuBar.height

            StackView {
                id: stack
                initialItem: playOrEditView
                anchors.fill: parent
            }
        }

    }
}
