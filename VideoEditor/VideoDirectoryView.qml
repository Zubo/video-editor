import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
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
            nameFilters: ["*.mp4"]
            folder: "file:///" + directoryPath
        }

        delegate: Column {
            ColumnLayout {
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter;
                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 120

                    Button {
                        icon.source: "qrc:/Images/raw-videos.png"
                        icon.color: "transparent"
                        icon.width: width
                        icon.height: height
                        anchors.fill: parent
                        anchors.margins: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter;
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 10

                    Text {
                        text: fileName.length > 22 ? fileName.substring(0, 22) + "..." : fileName
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        wrapMode: "WordWrap"
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter;
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 40
                    visible: showEdit

                    Button {
                        anchors.fill: parent
                        icon.source: "qrc:/Images/edit-video.png"
                        icon.color: "transparent"
                        text: "Edit"
                    }
                }
            }
        }
    }
}
