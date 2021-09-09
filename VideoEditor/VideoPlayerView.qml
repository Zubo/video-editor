import QtQuick 2.0
import QtMultimedia 5.12

Item {
    property string videoPath;
    MediaPlayer {
        id: videoPlayer
        source: videoPath
        autoPlay: true
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 15

        VideoOutput {
            anchors.fill:parent
            source: videoPlayer
        }
    }
}
