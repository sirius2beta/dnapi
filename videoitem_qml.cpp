//#include "dnapplication.h"
#include "dncore.h"
#include "videoitem_qml.h"
#include <QDebug>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQmlEngine>

#define HEARTBEAT 0x10
#define FORMAT 0x20
#define COMMAND 0x30
#define QUIT 0x40

VideoItem::VideoItem(QObject *parent, DNCore* core, int index, QString title, int boatID, int videoNo, int formatNo, int PCPort)
    : QObject{parent},
      _core(core),
      _title(title),
      _boatID(boatID),
      _index(index),
    _videoIndex(videoNo),
    _formatNo(formatNo),
    _PCPort(PCPort),
    _connectionPriority(0),
    _encoder(QString("h264")),
    _proxy(false),
    _requestFormat(true),
    _isPlaying(false),
    _isVideoInfo(false)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

VideoItem::~VideoItem()
{

    if(_isPlaying == false){

    }else{
        gst_element_set_state (_pipeline, GST_STATE_NULL);
        gst_object_unref (_pipeline);
        gst_object_unref (_sink);
    }
}
void VideoItem::initVideo(QQuickItem *widget)
{
    _videoWidget = widget;

    QString gstcmd;
     if(_encoder == "h264"){
         gstcmd = QString("udpsrc port=%1 ! application/x-rtp, media=video, clock-rate=90000, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert  !\
          glupload ! qmlglsink name=sink").arg(QString::number(_PCPort));
     }else{
          gstcmd = QString("udpsrc port=%1 ! application/x-rtp, media=video, clock-rate=90000, payload=96 ! rtpjpegdepay ! jpegdec ! videoconvert  !\
          glupload ! qmlglsink name=sink").arg(QString::number(_PCPort));
     }

    if(!_isPlaying){
        _pipeline= gst_parse_launch(gstcmd.toLocal8Bit(), NULL);
        _sink = gst_bin_get_by_name((GstBin*)_pipeline,"sink");
        g_object_set(_sink, "widget", widget, NULL);
        gst_element_set_state (_pipeline, GST_STATE_PLAYING);

    }


    _isPlaying = true;
}

void VideoItem::setTitle(QString title)
{
    _title = title;
    emit titleChanged(title);
}

void VideoItem::setPCPort(int port)
{
    _PCPort = port;
    emit PCPortChanged(port);
}

void VideoItem::setBoatID(int ID)
{

    if(_core->boatManager()->getBoatbyID(ID) == 0){
        qDebug()<<"**Fatal:: VideoItem::setBoatID: ID out of range";
        return;
    }

    if(_boatID != ID){
        //stop();
        //new list model
        _videoNoListModel.clear();
        _qualityListModel.clear();
        emit videoNoListModelChanged(_videoNoListModel);
        emit qualityListModelChanged(_qualityListModel);

        _boatID = ID;
        _requestFormat = true;
        emit requestFormat(this);

    }

}

void VideoItem::setIndex(int index)
{
    _index = index;
    emit indexChanged(index);
}

void VideoItem::setVideoIndex(int index)
{
    if(index >= _videoNoListModel.size()){
        qDebug()<<"**Fatal:: VideoItem::setVideoNo: index out of range";
        return;
    }
    _videoIndex = index;
    _qualityListModel.clear();

    QList<int> h = _videoFormatList[_videoNoListModel.at(index).toInt()];
    qDebug()<<"VideoItem::h: "<<h.size();
    for(int i = 0; i< h.size(); i++){
        _qualityListModel<<QString::number(h[i]);
    }
    if(_qualityListModel.size() > 0){
        _formatNo = 0;
    }
    emit qualityListModelChanged(_qualityListModel);
}

void VideoItem::setVideoFormat(QByteArray data)
{
    if(!_requestFormat) return;
    _requestFormat = false;
    QString currentvideoNo = QString();
    qDebug()<<" VideoItem::setVideoNo: got videoFormat";
    _videoFormatList.clear();
    int videoNo;
    int formatNo;
    int readorder = 0;
    if(data.size()%2 != 0 || data.size()/2 == 0){
        qDebug()<<"**Fatal::VideoItem::setVideoNo: wrong format message:"<<data.size();
        return;
    }
    for(int i = 0; i < data.size(); i+=2){
        videoNo = int(data[i]);
        formatNo = int(data[i+1]);
        _videoFormatList[videoNo].append(formatNo);
    }

    QMap<int, QList<int>>::const_iterator h = _videoFormatList.constBegin();
    while(h != _videoFormatList.constEnd()){
        _videoNoListModel<<QString::number(h.key());
        emit videoNoListModelChanged(_videoNoListModel);
        ++h;
    }

    if(_videoNoListModel.size() >0){
        setVideoIndex(0);
    }
}

void VideoItem::setFormatNo(int no)
{
    if(no >= _qualityListModel.size()){
        qDebug()<<"**Fatal:: VideoItem::setFormatNo: index out of range";
        return;
    }
    _formatNo = no;
}

void VideoItem::setDisplay(WId xwinid)
{
    _xwinid = xwinid;
}

void VideoItem::setConnectionPriority(int connectionType)
{
    qDebug()<<"VideoItem:: connectionTypeChanged: index:"<<_index<<", pre:"<<_connectionPriority<<", now:"<<connectionType;
    qDebug()<<"isPlaying:"<<(_isPlaying?"yes":"no");
    if(_connectionPriority != connectionType){
        _connectionPriority = connectionType;
        if(_isPlaying){
            qDebug()<<"VideoItem:: connectionTypeChanged:STOP & PLAY";
            stop();
            play();
        }else{
        }
    }

}

void VideoItem::play()
{
    qDebug()<<"VideoItem::play, videoIndex:"<<_videoIndex<<", formatNo:"<<_formatNo;
    if(_boatID == -1 || _videoIndex == -1 || _formatNo == -1) return;


    _isPlaying = true;
    emit videoPlayed(this);
}

void VideoItem::stop()
{   
    if(_isPlaying){
        //_isPlaying = false;
        //emit videoStoped(this);
    }

}

void VideoItem::setProxy(bool isProxy)
{
    _proxy = isProxy;

}

void VideoItem::setEncoder(QString encoder)
{
    if(_encoder != encoder){
        _encoder = encoder;
        QString gstcmd;

        if(_encoder == "h264"){
            gstcmd = QString("udpsrc port=%1 ! application/x-rtp, media=video, clock-rate=90000, payload=96 ! rtph264depay ! avdec_h264 ! videoconvert  !\
             glimagesink name=mySink2").arg(QString::number(_PCPort));
        }else{
             gstcmd = QString("udpsrc port=%1 ! application/x-rtp, media=video, clock-rate=90000, payload=96 ! rtpjpegdepay ! jpegdec ! videoconvert  !\
             glimagesink name=mySink2").arg(QString::number(_PCPort));
        }
        gst_element_set_state (_pipeline, GST_STATE_NULL);

        _pipeline= gst_parse_launch(gstcmd.toLocal8Bit(), NULL);
        _sink = gst_bin_get_by_name((GstBin*)_pipeline,"mySink2");
        gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (_sink), _xwinid);
        gst_element_set_state (_pipeline,
            GST_STATE_PLAYING);

        if(_videoWidget != nullptr){
            g_object_set(_sink, "widget", _videoWidget, NULL);
        }
    }
}

QString VideoItem::videoFormat()
{
    if(_formatNo == -1){
        qDebug()<<"**Warning: VideoItem::videoFormat: _formatNo = -1";
        return QString("");
    }
    return _qualityListModel[_formatNo];

}
