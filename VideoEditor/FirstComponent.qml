import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: firstRect

    Rectangle {
        x: 100
        y: 50
        height: 100
        width: 50
        color: "lightblue"
        Rectangle {
            x: 0
            y: 5
            height: 10
            width: 5
            color: "red"
        }
        Button {
            x: 200
            text: "Go to second rect"
            onClicked: stack.push(comp2)
        }
    }
}
