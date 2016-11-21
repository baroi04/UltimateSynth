import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function getTextFromIndex(index){
        var text
        switch(index){
        case 0:
            text = "Intro A"
            break
        case 1:
            text = "Main A"
            break
        case 2:
            text = "Fill In + Main A"
            break
        case 3:
            text = "Ending A"
            break
        case 4:
            text = "Intro B"
            break
        case 5:
            text = "Main B"
            break
        case 6:
            text = "Fill In + Main B"
            break
        case 7:
            text = "Ending B"
            break
        case 8:
            text = "Intro C"
            break
        case 9:
            text = "Main C"
            break
        case 10:
            text = "Fill In + Main C"
            break
        case 11:
            text = "Ending C"
            break
        case 12:
            text = "Intro D"
            break
        case 13:
            text = "Main D"
            break
        case 14:
            text = "Fill In + Main D"
            break
        case 15:
            text = "Ending D"
            break
        default:
            text = ""

        }

        return text

    }

    Rectangle{
        id: header

        height: parent.height*0.1
        width: parent.width
        color: "blue"
    }

    Rectangle{
        id: body

        height: parent.height*0.8
        width: parent.width
        color: "yellow"

        anchors.top: header.bottom

        Grid{
            Repeater{
                model: 16

                Rectangle{
                    width: body.width/4
                    height: body.height/4
                    color: "purple"
                    border.width: 1

                    Text{
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: getTextFromIndex(index)
                        color: "white"
                    }
                }

            }
        }

    }

    Rectangle{
        id: footer

        height: parent.height*0.1
        width: parent.width
        color: "red"

        anchors.top: body.bottom
    }


}
