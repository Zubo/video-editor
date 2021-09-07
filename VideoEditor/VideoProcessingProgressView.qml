import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    anchors.fill: parent
    ProgressBar {
        anchors.fill: parent
        id: videoProcessingProgressBar
        value: 0.0

        Connections {
            target: videoProcessorInterface
            onProgressChanged: function (val) {
                videoProcessingProgressBar.value = val;
            }
        }
    }

}
