import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

ColumnLayout {
    property string effectImageProviderSource;
    property bool selected: effectCB.checked
    property int xPos: xSlider.value
    property int yPos: ySlider.value

    Layout.alignment: Layout.Center
    spacing: 20

    Image {
        id: effectImage
        cache: false
        Layout.alignment: Layout.Center
        Layout.preferredWidth: 100
        Layout.preferredHeight: 100
        fillMode: Image.PreserveAspectFit
        source: effectImageProviderSource

        Connections {
            target: circleEffectTimer
            onTimerEventProcessingCompleted: {
                // force image reload
                effectImage.source = "";
                effectImage.source = effectImageProviderSource;
            }
        }
    }


    RowLayout {
        Layout.alignment: Layout.Center
        spacing: 20
        Text {
            Layout.preferredWidth: 40
            Layout.alignment: Layout.Center
            text: "X: " + Math.floor(xSlider.value)
        }

        Slider {
            id: xSlider
            enabled: effectCB.checked
            from: 0
            to: resolution.x
            Layout.preferredWidth: 100
        }
    }

    RowLayout {
        Layout.alignment: Layout.Center
        spacing: 20
        Text {
            Layout.preferredWidth: 40
            Layout.alignment: Layout.Center
            text: "Y: " + Math.floor(ySlider.value)
        }

        Slider {
            id: ySlider
            enabled: effectCB.checked
            from: 0
            to: resolution.y
            Layout.preferredWidth: 100
        }
    }

    CheckBox {
        Layout.preferredHeight: 30
        Layout.alignment: Layout.Center
        id: effectCB
        checked: false
    }
}
