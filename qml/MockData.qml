import QtQuick 2.5
import QtQuick.Controls 1.4

import org.joseph.awesome 1.0
Item {
    Component.onCompleted: {
        MiddleMan.modelType = MiddleMan.MockData
        MiddleMan.reFill();
    }
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
            model: MiddleMan.mockModel
            delegate:
                Rectangle{
                width: parent.width
                height: 120
                color:  "#F9BC02"
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
                    text: "<b> Id:</b> " + model.cId
                          + "<br/><b>Name:</b> " +model.uname
                          + " <br/><b> BitCoin Address:</b> " + model.bitcoinAddress
                          + " <br/><b>Credit card number : </b>  " + model.ccName
                          + " <br/><b>Credit card Type : </b>  " + model.ccNumber
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        MiddleMan.activeChanged(index)
                    }
                }
            }
        }
    }
}
