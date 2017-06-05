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

        Rectangle{
           id: styles

           height: parent.height
           width: parent.width*0.2
           color: "darkgrey"


           Text{
               anchors.fill: parent
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               text: "STYLES"
               color: "white"
           }

           MouseArea{
               anchors.fill: parent
               onClicked: fileDialog.show()
           }
        }

//        Rectangle{
//           id: voices
//           anchors.left: styles.right

//           height: parent.height
//           width: parent.width*0.2
//           color: "darkgrey"


//           Text{
//               anchors.fill: parent
//               horizontalAlignment: Text.AlignHCenter
//               verticalAlignment: Text.AlignVCenter
//               text: "VOICE"
//               color: "white"
//           }

//           MouseArea{
//               anchors.fill: parent
//               onClicked: {
//                   //console.log(instruExplorer.getIntrumentCategories())
//                   voicesExplorer.visible = true
//               }
//           }
//        }

        Item{
            id: partSelect

            height: parent.height
            width: parent.width*0.8

            anchors.left: styles.right

            Timer{
                id: timer1
                interval: 500; running: false; repeat: false
                onTriggered: {
                    ombl.writeToStdin("Left on/off")
                }
            }

            Component.onCompleted: timer1.start()


            Rectangle{
               id: left

               height: parent.height
               width: parent.width*0.2
               color: "darkgrey"


               Text{
                   anchors.fill: parent
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   text: "LEFT"
                   color: "white"
               }

               MouseArea{
                   anchors.fill: parent
                   onPressAndHold: {
                       if (left.color == "#a9a9a9"){
                           left.color = "red"
                           ombl.writeToStdin("Left on/off")
                       }else{
                           left.color = "darkgrey"
                           ombl.writeToStdin("Left on/off")
                       }
                   }

                   onClicked: {
                       voicesExplorer.visible = true
                       voicesExplorer.currentChannel = 1
                   }
               }
            }

            Rectangle{
               id: right1

               height: parent.height
               width: parent.width*0.2
               color: "red"

               anchors.left: left.right


               Text{
                   anchors.fill: parent
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   text: "RIGHT 1"
                   color: "white"
               }

               MouseArea{
                   anchors.fill: parent
                   //onClicked: fileDialog.show()
                   onPressAndHold: {
                       if (right1.color == "#a9a9a9"){
                           right1.color = "red"
                       }else{
                           right1.color = "darkgrey"
                       }
                   }

                   onClicked: {
                       voicesExplorer.visible = true
                       voicesExplorer.currentChannel = 0
                   }

               }
            }

            Rectangle{
               id: right2

               height: parent.height
               width: parent.width*0.2
               color: "darkgrey"

               anchors.left: right1.right


               Text{
                   anchors.fill: parent
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   text: "RIGHT 2"
                   color: "white"
               }

               MouseArea{
                   anchors.fill: parent
                   onPressAndHold: {
                       if (right2.color == "#a9a9a9"){
                           right2.color = "red"
                       }else{
                           right2.color = "darkgrey"
                       }
                   }

                   onClicked: {
                       voicesExplorer.visible = true
                       voicesExplorer.currentChannel = 3
                   }

               }
            }

            Rectangle{
               id: bass

               height: parent.height
               width: parent.width*0.2
               color: "darkgrey"

               anchors.left: right2.right


               Text{
                   anchors.fill: parent
                   horizontalAlignment: Text.AlignHCenter
                   verticalAlignment: Text.AlignVCenter
                   text: "BASS"
                   color: "white"
               }

               MouseArea{
                   anchors.fill: parent


                   onClicked: {
                       voicesExplorer.visible = true
                       voicesExplorer.currentChannel = 2
                   }

               }
            }

        }


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

                    MouseArea{
                        anchors.fill: parent
                        onClicked: ombl.writeToStdin(getTextFromIndex(index))
                    }
                }

            }
        }

    }

    Rectangle{
        id: body2

    }


    function getTextFromFooterIndex(index){
        var text
        switch(index){
        case 0:
            text = "ACPM"
            break
        case 1:
            text = "SYNC\nSTOP"
            break
        case 2:
            text = "SYNC\nSTART"
            break
        case 3:
            text = "START\nSTOP"
            break
        case 4:
            text = "STOP"
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
        id: footer

        height: parent.height*0.1
        width: parent.width
        color: "red"

        anchors.top: body.bottom

        Row{
            Repeater{
                model: 8

                Rectangle{
                    width: footer.width/8
                    height: footer.height
                    color: "darkgrey"
                    border.width: 1

                    Text{
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: getTextFromFooterIndex(index)
                        color: "white"
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: ombl.writeToStdin("Start/ Stop")
                    }
                }

            }
        }

    }

    DefaultFileDialog {
        id: fileDialog
        z: 100
        anchors.fill: parent
        folder: "file:///home/pi/ombl"

        itemHeight: parent.height/10
        itemWidth: parent.width
        fontSize: 15
        scaledMargin: 1

        onFileSelected: ombl.writeToStdin(file)
    }

    VoicesExplorer{
        id: voicesExplorer
        anchors.fill: parent
        visible: false
        z: 200
        onRequesthide: visible = false
        onItemSelected: instruExplorer.loadIntrument(item, currentChannel)

    }

}
