import QtQuick 2.15

Item {


    VideoView{
        id: videoView0
        pipView: _pipView
        videoObjectName: "videoContent0"
    }

    VideoView{
        id: videoView1
        pipView: _pipView
        videoObjectName: "videoContent1"
    }

    VideoView{
        id: videoView2
        pipView: _pipView2
        videoObjectName: "videoContent2"
    }


    PipView{
        id: _pipView
        sizeRatio: 9/16
        anchors.left:           parent.left
        anchors.top:         parent.top
        anchors.margins:        10
        item1:                  videoView0
        item2:                  videoView1
        name: "his"
        z:1
        show:                   true
    }

    PipView{
        id: _pipView2
        sizeRatio: 4/3
        anchors.right:           parent.right
        anchors.top:         parent.top
        anchors.margins:        10
        item1:                  videoView0
        item2:                  videoView2
        name: "his"
        z:1
        show:                   true
    }
}
