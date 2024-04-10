import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import DeNovoViewer 1.0
import DeNovoViewer.Boat 1.0

Item {
    Component{
        id: editBoatDialog
        EditBoatDialog{

        }
    }
    id: _root
    Layout.preferredWidth: 300
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignLeft
    Rectangle{
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        radius:5
        color: "#444444"
        Rectangle{
            id: _title
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            radius: 5
            height:25
            color: "#222222"
            Text{

                font.family: "Segoe UI"
                text:" BoatManager"
                color:"white"
            }
        }

        ListView{
            id: boatListView
            clip: true
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: _title.bottom
            height:150
            anchors.margins: 10
            model: DeNovoViewer.boatManager.boatListModel
            spacing: 3
            delegate: Component{
                Item{
                    id: _content
                    property bool button_visible: false


                    width: boatListView.width
                    anchors.margins: 20
                    height: 65
                    Column{
                        Text {
                            anchors.left:parent.left
                            anchors.margins: 10
                            font.family: "Segoe UI"
                            font.pointSize: 10
                            color:"white"
                            text: "<b>"+object.name
                        }
                        RowLayout{
                            anchors.left:parent.left
                            anchors.margins: 10
                            spacing: 10
                            Rectangle{
                                width: 10
                                height: 10
                                color: object.primaryConnected? "#5faab1": "#990000"
                            }

                            Text {

                                font.family: "Segoe UI"
                                color:"white"
                                font.pointSize: 8
                                text: object.PIP
                            }
                        }
                        RowLayout{
                            spacing: 10
                            anchors.left:parent.left
                            anchors.margins: 10
                            Rectangle{
                                width: 10
                                height: 10
                                color: object.secondaryConnected? "#5faab1": "#990000"
                            }

                            Text {

                                font.family: "Segoe UI"
                                color:"white"
                                font.pointSize: 8
                                text: object.SIP
                            }
                        }




                    }

                    MouseArea {
                        propagateComposedEvents: true
                        anchors.fill: parent
                        onClicked: {

                            boatListView.currentIndex = index
                            boatListView.focus = true
                            for(let i = 0; i < boatListView.count; i++){
                                boatListView.itemAtIndex(i).button_visible = false
                            }

                            boatListView.currentItem.button_visible = true

                            console.log(boatListView.focus)
                        }

                    }
                    Button{
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        visible: button_visible && boatListView.focus
                        text: 'edit'
                        font.family: "Segoe UI"
                        onClicked: {
                            console.log(boatListView.currentIndex)
                            editBoatDialog.createObject(dnMainWindow).open()
                        }
                    }
                }
            }
            highlight: Rectangle { color: "#2d464c"; radius: 2 }
            focus: true
        }
        Row{
            anchors.bottom: parent.bottom
            Button{

                height:40
                text: "Del"
                font.family: "Segoe UI"
                onClicked: {
                    DeNovoViewer.boatManager.deleteBoat(boatListView.currentIndex)
                    console.log(boatListView.currentIndex)
                }
            }
            Button{

                height:40
                text: "Add"
                font.family: "Segoe UI"
                onClicked: {
                    DeNovoViewer.boatManager.addBoat()
                }
            }
        }
    }
}


