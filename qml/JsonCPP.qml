import QtQuick 2.5
import Material.ListItems 1.0 as ListItems
import QtQuick.Controls 1.4

import org.joseph.awesome 1.0
Item {
    TextField{
        id: searchBar
        width: parent.width / 1.07
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Search Contacts . . . . ")
    }
    ListView{
        width: parent.width
        height: parent.height - (searchBar.height *2)
        anchors.top: searchBar.bottom
        anchors.topMargin: searchBar.height
        model: MiddleMan.addressModel
        delegate: ListItems.Subtitled{
            text: model.first + " " + model.last
            subText: "<b>Id:</b> " + model.ids + "<b> Image Url:</b> " + model.avatar
        }
    }
}
