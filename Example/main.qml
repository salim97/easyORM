import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Component.onCompleted: {
        for( var i = 0 ; i < clients.rowCount() ; i++ )
        {
            clients.selectRow(i)
//            var tmp = JSON.parse(clients.currentRowToJSON());
            console.log(clients.currentRowToJSON().first_name)
        }
    }
    Item {
        anchors.fill: parent

    }
}
