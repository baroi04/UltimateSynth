import QtQuick 2.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Item {
    signal requesthide
    property int currentChannel: 1

    property int itemRowsLen: 5
    property int itemColLen: 2
    property int currentPage: 0
    property var pages: updatePageFromVector(instruExplorer.getIntrumentCategories())

    property bool isCategoryDisplayed: true

    signal itemSelected(string item)


    function updatePageFromVector(vec){

        var itemPerPage = itemRowsLen*itemColLen
        var lastPageLen = vec.length % (itemRowsLen*itemColLen)
        var numberOfPages = (vec.length -  lastPageLen) / ( itemPerPage )
        if(lastPageLen > 0){numberOfPages++}

        var pages = new Array(numberOfPages);
        var i;
        for (i = 0; i < numberOfPages - 1; i++){
            pages[i] = vec.slice(i*itemPerPage, i*itemPerPage + itemPerPage)
        }

        pages[numberOfPages - 1] = vec.slice((numberOfPages - 1)*itemPerPage, vec.length)

        //Complete page with empty strings
        for (i = 0; i < itemPerPage - lastPageLen; i++)
        {
            pages[numberOfPages - 1].push("")
        }

        return pages
    }


    Rectangle{
        id: header
        color: "red"
        height: parent.height*0.1
        width: parent.width

        Item{
            id: leftArrow
            height: parent.height
            width: parent.height

            Image {
                id: leftImg
                anchors.fill: parent
                source: "qrc:///last-track-left-arrow.svg"
                visible: currentPage > 0
            }

            MouseArea{
                anchors.fill: parent
                onClicked: currentPage--
                enabled: currentPage > 0
            }
        }

        Text{
            id: pageTtile
            text: "Page " + (currentPage+1)
            height: parent.height
            anchors.left: leftArrow.right
            anchors.right: rightArrow.left

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 70
            fontSizeMode: Text.Fit

        }

        Item{
            id: rightArrow
            height: parent.height
            width: parent.height
            anchors.right: parent.right

            Image {
                id: rightImg
                anchors.fill: parent
                source: "qrc:///skip-track.svg"
                visible: currentPage < (pages.length-1)
            }

            MouseArea{
                anchors.fill: parent
                enabled: currentPage < (pages.length-1)
                onClicked: currentPage++
            }
        }
    }

    Rectangle{
        id: body
        color: "purple"
        height: parent.height*0.8
        width: parent.width
        anchors.top: header.bottom

        Grid{
            columns: itemColLen

            Repeater{
                model: itemRowsLen*itemColLen

                Rectangle{
                    width: body.width/itemColLen
                    height: body.height/itemRowsLen
                    color: "red"
                    border.width: 1



                    Text{
                        id: textV
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: pages[currentPage][index]
                        color: "white"
                    }

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            // Current display is categories so we now want to display intrument sof this category
                            if (isCategoryDisplayed){                                  
                                pages = updatePageFromVector(instruExplorer.getIntrumentListFromCategory(textV.text))
                                isCategoryDisplayed = false
                            //
                            }else{
                                console.log("User wants",  textV.text)
                                itemSelected(textV.text)

                                pages = updatePageFromVector(instruExplorer.getIntrumentCategories())
                                isCategoryDisplayed = true
                                requesthide()
                            }
                        }
                    }
                }

            }
        }

    }

    Rectangle{
        id: footer
        color: "yellow"
        height: parent.height*0.1
        width: parent.width
        anchors.top: body.bottom

        Button {
            id: cancelButton
            width: footer.height*0.8*1.5
            height: footer.height*0.8
            //color: "#353535"
            anchors.centerIn: parent
            text: "Cancel"
            onClicked: requesthide()
            //horizontalAlign: Text.AlignHCenter
            //onClicked: fileBrowser.selectFile("")
        }
    }
}
