import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

import org.joseph.awesome 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Json Query Model")
    TabView{
        anchors.fill: parent
        Tab{
            active: true
            title: "Address book"
            source: "qrc:/AddressModel.qml"
        }
        Tab{
            title: "Mock Data"
            source: "qrc:/MockData.qml"
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
