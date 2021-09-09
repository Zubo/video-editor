import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtMultimedia 5.12

Item {
    id: videoEffectSelecton

    property var resolution: videoProcessorInterface.getVideoResolution(mainView.selectedVideoSrcPath)
    ColumnLayout {
        Layout.margins: 15

        spacing: 10
        anchors.fill: parent

        Text {
            Layout.alignment: Layout.Center
            text: "Editing file: " + mainView.selectedVideoSrcPath
        }

        RowLayout {
            Layout.alignment: Layout.Center
            spacing: 100

            ColumnLayout {
                Layout.alignment: Layout.Center
                spacing: 20

                Image {
                    id: circleEffectImg
                    cache: false
                    Layout.alignment: Layout.Center
                    Layout.preferredHeight: 100
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


                RowLayout {
                    Layout.alignment: Layout.Center
                    spacing: 20
                    Text {
                        Layout.alignment: Layout.Center
                        text: "X: " + Math.floor(circleXSlider.value)
                    }

                    Slider {
                        id: circleXSlider
                        enabled: circleEffectCB.checked
                        from: 0
                        to: resolution.x
                        Layout.preferredWidth: 100
                    }
                }

                RowLayout {
                    Layout.alignment: Layout.Center
                    spacing: 20
                    Text {
                        Layout.alignment: Layout.Center
                        text: "Y: " + Math.floor(circleYSlider.value)
                    }

                    Slider {
                        id: circleYSlider
                        enabled: circleEffectCB.checked
                        from: 0
                        to: resolution.y
                        Layout.preferredWidth: 100
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
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100
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


                RowLayout {
                    Layout.alignment: Layout.Center
                    spacing: 20
                    Text {
                        Layout.alignment: Layout.Center
                        text: "X: " + Math.floor(numericalValueXSlider.value)
                    }

                    Slider {
                        id: numericalValueXSlider
                        enabled: numericalEffectCB.checked
                        from: 0
                        to: resolution.x
                        Layout.preferredWidth: 100
                    }
                }

                RowLayout {
                    Layout.alignment: Layout.Center
                    spacing: 20
                    Text {
                        Layout.alignment: Layout.Center
                        text: "Y: " + Math.floor(numericalValueYSlider.value)
                    }

                    Slider {
                        id: numericalValueYSlider
                        enabled: numericalEffectCB.checked
                        from: 0
                        to: resolution.y
                        Layout.preferredWidth: 100
                    }
                }

                CheckBox {
                    id: numericalEffectCB

                    Layout.alignment: Layout.Center
                    checked: false
                }
            }

            ColumnLayout {
                Layout.alignment: Layout.Center
                spacing: 20

                Image {
                    id: progressEffectImg
                    cache: false
                    Layout.alignment: Layout.Center
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: 200
                    source: "image://progressbar-effect/-"

                    Connections {
                        target: numberEffectTimer
                        onTimerEventProcessingCompleted: {
                            // force image reload
                            progressEffectImg.source = "";
                            progressEffectImg.source = "image://progressbar-effect/-";
                        }
                    }
                }

                RowLayout {
                    Layout.alignment: Layout.Center
                    spacing: 20
                    Text {
                        Layout.alignment: Layout.Center
                        text: "X: " + Math.floor(progressbarXSlider.value)
                    }

                    Slider {
                        id: progressbarXSlider
                        enabled: progressBarCB.checked
                        from: 0
                        to: resolution.x
                        Layout.preferredWidth: 100
                    }
                }

                RowLayout {
                    Layout.alignment: Layout.Center
                    spacing: 20
                    Text {
                        Layout.alignment: Layout.Center
                        text: "Y: " + Math.floor(progressbarYSlider.value)
                    }

                    Slider {
                        id: progressbarYSlider
                        enabled: progressBarCB.checked
                        from: 0
                        to: resolution.y
                        Layout.preferredWidth: 100
                    }
                }


                CheckBox {
                    id: progressBarCB

                    Layout.alignment: Layout.Center
                    checked: false
                }
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
                    useCircleEffect: circleEffectCB.checked,
                    circleEffectPos: Qt.point(circleXSlider.value, circleYSlider.value),
                    useNumericalEffect: numericalEffectCB.checked,
                    numericalEffectPos: Qt.point(numericalValueXSlider.value, numericalValueYSlider.value),
                    useProgressbarEffect: progressBarCB.checked,
                    progressbarEffectPos: Qt.point(progressbarXSlider.value, progressbarYSlider.value)
                };
                videoProcessorInterface.requestProcessing(data);
                mainView.backButtonDisabled = true;
                stack.push(mainView.videoProcessingProgressView);
            }
            enabled: circleEffectCB.checked | numericalEffectCB.checked | progressBarCB.checked
        }
    }
}
