import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property Component playOrEditView: PlayOrEditView{}
    StackView {
        id: stack
        initialItem: playOrEditView
        anchors.fill: parent
    }
}
