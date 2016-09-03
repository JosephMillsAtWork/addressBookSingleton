import QtQuick 2.5
import QtQuick.Controls 1.4
import org.joseph.awesome 1.0


Item {
    Component.onCompleted: {
        JSONModels.modelType = JSONModels.Address
        JSONModels.reFill();
    }
    Column{
        anchors.fill: parent
        Button{
            id: refillButton
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Re-Fill Model")
            onClicked: JSONModels.reFill();
        }
        Text {
            width: parent.width
            height: refillButton.height - 4
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "Is The Model Updating ? " + JSONModels.isRunning
            color: "black"

        }


        ListView{
            width: parent.width
            height: parent.height - (refillButton.height *2)
            clip: true
            model: JSONModels.addressModel
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
                        JSONModels.activeChanged(index)
                    }
                }
            }
        }
    }
}
