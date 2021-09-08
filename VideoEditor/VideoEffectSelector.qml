import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: videoEffectSelector

    ColumnLayout {
        spacing: 10
        anchors.fill: parent
        RowLayout {
            spacing: 100

            ColumnLayout {
                Layout.alignment: Layout.Center
                spacing: 20

                Image {
                    id: circleEffectImg
                    cache: false
                    Layout.alignment: Layout.Center
                    Layout.preferredHeight: 150
                    fillMode: Image.PreserveAspectFit
                    source: "image://circle-effect/-"

                    Connections {
                        target: circleEffectTimer
                        onTimerEventProcessingCompleted: {
                            // force image reload
                            circleEffectImg.source = "";
                            circleEffectImg.source = "image://circle-effect/-";
                        }
                    }
                }

                CheckBox {
                    Layout.alignment: Layout.Center
                    id: circleEffectCB
                    checked: false
                }
            }

            ColumnLayout {
                Layout.alignment: Layout.Center
                spacing: 20

                Image {
                    id: numberEffectImg
                    cache: false
                    Layout.alignment: Layout.Center
                    Layout.preferredHeight: 150
                    fillMode: Image.PreserveAspectFit
                    source: "image://number-effect/-"

                    Connections {
                        target: numberEffectTimer
                        onTimerEventProcessingCompleted: {
                            // force image reload
                            numberEffectImg.source = "";
                            numberEffectImg.source = "image://number-effect/-";
                        }
                    }
                }

                CheckBox {
                    id: numericalEffectCB

                    Layout.alignment: Layout.Center
                    checked: false
                }
            }

            Layout.alignment: Layout.Center
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
                    useCircleEffect: circleEffectCB.checked,
                    useNumericalEffect: numericalEffectCB.checked
                };
                videoProcessorInterface.requestProcessing(data);
                stack.push(mainView.videoProcessingProgressView);
            }
            enabled: circleEffectCB.checked | numericalEffectCB.checked
        }
    }
}
