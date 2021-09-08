import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Dialog {
    id: dialog
    title: "Title"
    standardButtons: Dialog.Ok
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
}
