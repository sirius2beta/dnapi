import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import DeNovoViewer 1.0
import DeNovoViewer.Boat 1.0

Item {
    Layout.preferredWidth: 500
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignLeft
    ListModel {
        id: demoModel2
        ListElement {
            name: "Cabin Temperature"
            number: "26.45"
            unit: "℃"
        }
        ListElement {
            name: "Battery cell 1"
            number: "19.3"
            unit: "V"
        }
        ListElement {
            name: "Battery cell 2"
            number: "19.5"
            unit: "V"
        }
        ListElement {
            name: "Battery cell 3"
            number: "19.3"
            unit: "V"
        }
        ListElement {
            name: "CPU temperature"
            number: "40.5"
            unit: "C"
        }
        ListElement {
            name: "Dissolved oxgen saturation"
            number: "13.22"
            unit: "%"
        }
        ListElement {
            name: "Dissolved oxgen saturation"
            number: "13.22"
            unit: "%"
        }
        ListElement {
            name: "Resistivity"
            number: "45.23"
            unit: "%"
        }
    }
    Component {
        id: sensorDelegate
        Item {
            width: _sensorListView.width; height: 35
            RowLayout{

                Text {
                    Layout.preferredWidth: 150
                    wrapMode: Text.WordWrap
                    font.family: "Segoe UI"
                    font.pointSize: 10
                    lineHeight: 0.6
                    color:"#b8bbc0"
                    text: name
                }
                Item {
                    Layout.fillWidth: true
                }

                Text {
                    Layout.preferredWidth: 50
                    font.family: "Segoe UI"
                    font.pointSize: 12
                    color:"white"
                    text: number
                }
                Item {
                    Layout.preferredWidth: 10
                }
                Text {
                    Layout.preferredWidth: 50
                    font.family: "Segoe UI"
                    font.pointSize: 10
                    color:"#b8bbc0"
                    text: unit
                }
            }
        }
    }
    Rectangle{
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        radius:5
        color: "#292b2d"
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
                text:" BoatStatus"
                color:"white"
            }
        }
        RowLayout{
            anchors.top: _title.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10
            Item{
                Layout.preferredWidth: 150
                Layout.fillHeight: true

                Image {
                    height: parent.height-40
                    fillMode: Image.PreserveAspectFit
                    id: _thumbnail2
                    source: "qrc:/res/topview.png"
                }
            }


            ListView{
                Layout.preferredWidth: 300
                Layout.preferredHeight: parent.height
                id: _sensorListView
                clip: true
                model: demoModel2
                delegate: sensorDelegate

            }
            Item{
                Layout.fillWidth: true
            }
        }



    }

}
