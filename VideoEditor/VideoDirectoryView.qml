import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.1

Item {
    property string directoryPath
    property bool showEdit: false

    GridView {
        id: grid
        anchors.fill: parent
        clip: true
        cellWidth: 150
        cellHeight: showEdit ? 200 : 160

        model: FolderListModel {
            id: filefolderModel
            showDirs: false
            showDirsFirst: false
            nameFilters: ["*.mkv", "*.mp4"]
            folder: "file://" + ((directoryPath[0] === '/') ? directoryPath : ("/" + directoryPath))
        }


        delegate: Column {
            ColumnLayout {
                spacing: 10

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter;
                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 80

                    Button {
                        Image {
                            id: img
                            anchors.fill: parent
                            anchors.margins: 5
                            cache: false
                            source: "file:///" + filePath.substr(0, filePath.lastIndexOf(".")) + ".png"

                            Connections {
                                target: thumbnailGeneratorInterface
                                onGeneratingEnded: {
                                    img.source = ""
                                    img.source = "file:///" + filePath.substr(0, filePath.lastIndexOf(".")) + ".png"
                                }
                            }
                        }

                        anchors.fill: parent
                        onClicked: stack.push("qrc:/VideoPlayerView.qml", { videoPath: ("file:///" + filePath) })
                    }
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter;
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 25

                    Text {
                        text: fileName.length > 15 ? fileName.substring(0, 15) + "..." : fileName
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter;
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    visible: showEdit

                    Button {
                        anchors.fill: parent
                        icon.source: "qrc:/Images/edit-video.png"
                        icon.color: "transparent"
                        text: "Edit"
                        onClicked: {
                            mainView.selectedVideoSrcPath = filePath;
                            stack.push(mainView.videoEffectSelector);
                        }
                    }
                }
            }
        }
    }
}
