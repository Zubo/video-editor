import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    id: videoEffectSelecton

    property var resolution: videoProcessorInterface.getVideoResolution(mainView.selectedVideoSrcPath)
    ColumnLayout {
        Layout.margins: 15

        spacing: 10
        anchors.fill: parent

        Text {
            Layout.maximumHeight: 10
            Layout.alignment: Layout.Center
            text: "Editing file: " + mainView.selectedVideoSrcPath
        }

        RowLayout {
            Layout.alignment: Layout.Center
            spacing: 50

            VideoEffectOptions {
                id: circleEffectSelector
                effectImageProviderSource: "image://circle-effect/-"
            }

            VideoEffectOptions {
                id: numericalEffectSelector
                effectImageProviderSource: "image://number-effect/-"
            }

            VideoEffectOptions {
                id: progressbarEffectSelector
                effectImageProviderSource: "image://progressbar-effect/-"
            }
        }

        Button {
            Layout.alignment: Layout.Center
            Layout.preferredWidth: 100
            Layout.preferredHeight: 60
            Layout.margins: 10
            text: "Apply"
            onClicked: {
                var data = {
                    srcPath: mainView.selectedVideoSrcPath,
                    useCircleEffect: circleEffectSelector.selected,
                    circleEffectPos: Qt.point(circleEffectSelector.xPos, circleEffectSelector.yPos),
                    useNumericalEffect: numericalEffectSelector.selected,
                    numericalEffectPos: Qt.point(numericalEffectSelector.xPos, numericalEffectSelector.yPos),
                    useProgressbarEffect: progressbarEffectSelector.selected,
                    progressbarEffectPos: Qt.point(progressbarEffectSelector.xPos, progressbarEffectSelector.yPos)
                };
                videoProcessorInterface.requestProcessing(data);
                mainView.backButtonDisabled = true;
                stack.push(mainView.videoProcessingProgressView);
            }
            enabled: circleEffectSelector.selected | numericalEffectSelector.selected | progressbarEffectSelector.selected
        }
    }
}
