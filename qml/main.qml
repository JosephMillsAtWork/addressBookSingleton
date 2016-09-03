import QtQuick 2.5
import QtQuick.Window 2.0
import Material.ListItems 1.0 as ListItems
import QtQuick.Controls 1.4

import org.joseph.awesome 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Column{
        anchors.fill: parent
        Button{
            id: searchBar
            width: parent.width / 1.07
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Re-Fill Model")
            onClicked: MiddleMan.reFill();
        }
        Text {
            width: parent.width
            height: searchBar.height - 4
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "Is The Model Updating ? " + MiddleMan.isRunning
            color: "black"

        }


        ListView{
            width: parent.width
            height: parent.height - (searchBar.height *2)
            clip: true
            model: MiddleMan.addressModel
            delegate:
                Rectangle{
                width: parent.width
                height: 120
                color: "#c3c3c3"
                radius: 5
                border{
                    width: 1
                    color: "#80000000"
                }

                Text{
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: model.first + " " + model.last + " <b> Id:</b> " + model.ids + " <b> Image Url:</b> " + model.avatar
                }
            }
        }
    }


    // Here we add more connection points to read the signals and slots

    Connections{
        target: MiddleMan
        onIsRunningChanged:{
            console.log("Running changed to  " + MiddleMan.isRunning)
        }
    }


}
