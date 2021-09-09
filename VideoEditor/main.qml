import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: mainView
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    title: qsTr("Video Processor")

    property Component playOrEditView: PlayOrEditView{}
    property Component rawVideoView: VideoDirectoryView{ directoryPath: rawVideosDirectoryPath; showEdit: true }
    property Component editedVideoView: VideoDirectoryView{ directoryPath: editedVideosDirectoryPath }
    property Component videoEffectSelector: VideoEffectSelectorView{}
    property Component videoProcessingProgressView: VideoProcessingProgressView{}

    property string selectedVideoSrcPath: ""
    property bool backButtonDisabled: false

    Component {
        id: importFileDialogComponent
        FileDialog {
            title: "Select videos to import"
            nameFilters: [ "Video files(*.mp4 *.mkv)"]
            selectMultiple: true
            onAccepted: {
                console.log("You choese: " + fileUrls);
                videoImporterInterface.importFiles(fileUrls)
            }

            Component.onCompleted: visible = true
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            Action {
                text: "Import raw videos..."
                onTriggered: {
                    var dialog = importFileDialogComponent.createObject(mainView)
                }
            }
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
                enabled: !backButtonDisabled && (mainViewStack.depth > 1)
                onClicked: mainViewStack.pop()
            }
        }

        Rectangle {
            Layout.preferredWidth: mainView.width
            Layout.preferredHeight: mainView.height - menuBar.height

            StackView {
                id: mainViewStack
                initialItem: playOrEditView
                anchors.fill: parent
            }
        }

    }
}
