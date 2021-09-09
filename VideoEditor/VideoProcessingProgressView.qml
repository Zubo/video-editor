import QtQuick 2.0
import QtQuick.Controls 2.11
import QtQuick.Layouts 1.12

Item {
    ColumnLayout {
        anchors.fill: parent

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: "Processing..."
        }

        ProgressBar {
            Layout.alignment: Qt.AlignHCenter
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
            Layout.alignment: Qt.AlignHCenter
            text: "Abort"
            onClicked: videoProcessorInterface.stopProcessing()
        }
    }

    Connections {
        target: videoProcessorInterface
        onProcessingCompleted: {
            mainView.backButtonDisabled = false;
            mainViewStack.pop();

            var dialogComponent = Qt.createComponent("qrc:/MessageDialogView.qml");

            var dialogProperties =  {
                title: "Processing successful!",
            };
            var dialogObject = dialogComponent.createObject(mainView, dialogProperties);
            dialogObject.open();
        }

        onVideoProcessingAborted:  function(msg) {
            mainView.backButtonDisabled = false;
            mainViewStack.pop();

            var dialogComponent = Qt.createComponent("qrc:/MessageDialogView.qml");

            var dialogProperties =  {
                title: msg === "" ? "Processing aborted!" : msg,
            };

            var dialogObject = dialogComponent.createObject(mainView, dialogProperties);
            dialogObject.open();

        }
    }
}
