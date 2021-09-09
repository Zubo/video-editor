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

                    TextField {
                        id: circleXPosTF
                        placeholderText: "Enter X position"
                        enabled: circleEffectCB.checked
                        validator: IntValidator{
                            bottom:0;
                            top:resolution.x
                        }
                        Layout.preferredWidth: 100
                    }

                    TextField {
                        id: circleYPosTF
                        placeholderText: "Enter Y position"
                        enabled: circleEffectCB.checked
                        validator: IntValidator{
                            bottom:0;
                            top:resolution.y
                        }
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

                    TextField {
                        id: numericalXPosTF
                        placeholderText: "Enter X position"
                        enabled: numericalEffectCB.checked
                        validator: IntValidator{
                            bottom:0;
                            top:resolution.x
                        }
                        Layout.preferredWidth: 100
                    }

                    TextField {
                        id: numericalYPosTF
                        placeholderText: "Enter Y position"
                        enabled: numericalEffectCB.checked
                        validator: IntValidator{
                            bottom:0;
                            top:resolution.y
                        }
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

                    TextField {
                        id: progressBarXPosTF
                        placeholderText: "Enter X position"
                        enabled: progressBarCB.checked
                        validator: IntValidator{
                            bottom:0;
                            top:resolution.x
                        }
                        Layout.preferredWidth: 100
                    }

                    TextField {
                        id: progressBarYPosTF
                        placeholderText: "Enter Y position"
                        enabled: progressBarCB.checked
                        validator: IntValidator{
                            bottom:0;
                            top:resolution.y
                        }
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
                    circleEffectPos: Qt.point(circleXPosTF.text, circleYPosTF.text),
                    useNumericalEffect: numericalEffectCB.checked,
                    numericalEffectPos: Qt.point(numericalXPosTF.text, numericalYPosTF.text),
                    useProgressbarEffect: progressBarCB.checked,
                    progressbarEffectPos: Qt.point(progressBarXPosTF.text, progressBarYPosTF.text)
                };
                videoProcessorInterface.requestProcessing(data);
                mainView.backButtonDisabled = true;
                stack.push(mainView.videoProcessingProgressView);
            }
            enabled: circleEffectCB.checked | numericalEffectCB.checked | progressBarCB.checked
        }
    }
}
