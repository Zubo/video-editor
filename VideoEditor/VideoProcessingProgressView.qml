import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
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

    Button {
        text: "Abort"
        onClicked: {
            videoProcessorInterface.stopProcessing();
            stack.pop();
        }
    }

    Connections {
        target: videoProcessorInterface
        onProcessingCompleted: {
            var dialogComponent = Qt.createComponent("qrc:/MessageDialogView.qml");
            var dialogObject = dialogComponent.createObject(mainView);
            dialogObject.open();
        }
    }
}
