import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

import org.joseph.awesome 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Json Query Model")
    Column{
        anchors.fill: parent
        Button{
            id: refillButton
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Re-Fill Model")
            onClicked: MiddleMan.reFill();
        }
        Text {
            width: parent.width
            height: refillButton.height - 4
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "Is The Model Updating ? " + MiddleMan.isRunning
            color: "black"

        }


        ListView{
            width: parent.width
            height: parent.height - (refillButton.height *2)
            clip: true
            model: MiddleMan.addressModel
            delegate:
                Rectangle{
                width: parent.width
                height: 120
                color: model.active ? "#F9BC02" :"#FE2712"
                radius: 5
                border{
                    width: 1
                    color: "#80000000"
                }

                Text{
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    text: "<b>Name:</b> " +model.first + " " + model.last + " <br/><b> Id:</b> " + model.ids + " <br/><b> Image Url:</b> " + model.avatar
                          + " <br/><b>Active: </b>  " + model.active
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        model.active = !model.active
                        MiddleMan.activeChanged(index)
                    }
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
