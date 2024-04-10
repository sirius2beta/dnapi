import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

import DeNovoViewer 1.0
import DeNovoViewer.Boat 1.0

import org.freedesktop.gstreamer.GLVideoItem 1.0

Item {
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    property bool controlHide: true
    property int _index: 0
    property VideoItem videoItem
    function setIndex(index){
        _index = index
        videoItem = DeNovoViewer.videoManager.getVideoItem(index)
        videoItem.setBoatID(DeNovoViewer.boatManager.getIDbyInex(_boatNo.currentIndex))
        console.log("init listview index:",_boatNo.currentIndex)
    }

    Rectangle{
        id: background
        anchors.fill: parent
        color: "#333333"
        radius:10
        clip: true
        GstGLVideoItem {
            id: video
            objectName: "videoContent"
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
        }
        Item{
            anchors.fill: parent

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                height: 80
                fillMode: Image.PreserveAspectFit
                id: _thumbnail2
                source: "qrc:/res/videoMiddleIndicater.png"
            }
        }

        Rectangle{
            id: _toggle
            anchors.bottom: _control.top
            anchors.horizontalCenter: parent.horizontalCenter

            height:30
            width:100
            radius:8
            color: "#333333"
            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 8
                color: "#333333"
            }

            Text {
                anchors.centerIn: parent
                id: _text
                color: "#888888"
                text: "▲"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    controlHide = controlHide?false:true
                    _control.height = controlHide?0:60
                    _text.text = controlHide?"▲":"▼"
                }
            }
        }

        Rectangle{
            id: _control
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height:0
            color: "#333333"
            clip: true
            Button{
                id: _playButton
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 5
                height: _videoNo.height
                font.family: "Segoe UI"
                text: "Play"
                onClicked: {
                    if(videoItem){
                        videoItem.play()
                        console.log("play")
                    }
                }

            }
            ComboBox{
                id: _qualityNo

                anchors.right: _playButton.left
                anchors.bottom: parent.bottom
                anchors.margins: 5
                font.family: "Segoe UI"
                model: videoItem?videoItem.formatListStringModel:0
                Connections{
                    function onActivated(index) {
                        videoItem.setFormatNo(index)
                        console.log("set formatNo:", index)
                    }
                }
            }

            ComboBox{
                id: _videoNo
                anchors.right: _qualityNo.left
                anchors.bottom: parent.bottom
                anchors.margins: 5
                font.family: "Segoe UI"
                model: videoItem?videoItem.videoNoListModel:0
                Connections{
                    function onActivated(index) {
                        videoItem.setVideoIndex(index)
                        console.log("set videoIndex: ", index)
                    }
                }

            }

            ComboBox {
                id: _boatNo
                anchors.right: _videoNo.left
                anchors.bottom: parent.bottom
                anchors.margins: 5
                editable: false
                model: DeNovoViewer.boatManager.boatListModel
                displayText: (currentIndex!=-1)?DeNovoViewer.boatManager.boatListModel.get(currentIndex).name:""
                font.family: "Segoe UI"
                Connections {
                    function onActivated(index) {
                        videoItem.setBoatID(DeNovoViewer.boatManager.getIDbyInex(index))
                        console.log("listview index:",_boatNo.currentIndex)
                    }

                }
                Connections{
                    target: DeNovoViewer.boatManager
                    function onBoatAdded() {
                        if(_boatNo.currentIndex == -1){
                            _boatNo.currentIndex = 0
                        }
                    }
                }

                delegate: ItemDelegate  {
                    width: _boatNo.width;
                    height: 30
                    Text {
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 10
                        text: object.name
                        font.pointSize: 10
                        color: "white"
                        font.family: "Segoe UI"
                    }
                    //required property string modelData
                }

            }
        }
    }

    Component.onCompleted: {
        setIndex(_index)
    }




}
