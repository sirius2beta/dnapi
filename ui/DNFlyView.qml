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
        _index: 1
        videoObjectName: "videoContent1"
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


}
