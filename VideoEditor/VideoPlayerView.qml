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
        color: "black"
        anchors.fill: parent

        VideoOutput {
            anchors.fill:parent
            source: videoPlayer
        }
    }
}
