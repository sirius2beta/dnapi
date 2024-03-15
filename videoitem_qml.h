#ifndef VIDEOITEM_H
#define VIDEOITEM_H


#include <QObject>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QWidget>
#include <QStandardItemModel>
#include <QQuickWindow>
#include <QQuickItem>

#include "qmlobjectlistmodel.h"

class GPBCore;
class VideoItem : public QObject
{
    Q_OBJECT
public:
    explicit VideoItem(QObject *parent = nullptr, GPBCore* core = nullptr, int index=-1, QString title=QString(), int boatID=-1, int videoNo=-1, int formatNo=-1, int PCPort=0);
    ~VideoItem();
    Q_PROPERTY(QStringList videoNoListModel READ videoNoListModel CONSTANT)
    Q_PROPERTY(int boatID READ boatID NOTIFY boatIDChanged )
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString PCPort READ PCPort NOTIFY PCPortChanged)
    //Q_PROPERTY(QString port READ port NOTIFY IPChanged)
    //Q_PROPERTY(bool primaryConnected READ primaryConnected  NOTIFY connectStatusChanged)
    //Q_PROPERTY(bool secondaryConnected READ secondaryConnected  NOTIFY connectStatusChanged)

    void initVideo(QQuickItem *widget);
    void setDisplay(WId xwinid);
    Q_INVOKABLE void play();
    Q_INVOKABLE void stop();

    Q_INVOKABLE void setProxy(bool isProxy);
    Q_INVOKABLE void setEncoder(QString encoder);
    Q_INVOKABLE void setTitle(QString title);
    Q_INVOKABLE void setPCPort(int port);
    Q_INVOKABLE void setBoatID(int ID);
    Q_INVOKABLE void setIndex(int index);
    Q_INVOKABLE void setVideoNo(int index);
    Q_INVOKABLE void setFormatNo(int no);
    Q_INVOKABLE void setProxyMode(bool p){ _proxyMode = p;}
    void setVideoFormat(QStringList videoformat);
    void setWID(WId wid){_xwinid = wid;}
    void setConnectionPriority(int connectionType);
    void setVideoInfo(bool i) { _isVideoInfo = i; }

    QString title() { return _title;   }
    int boatID() {  return _boatID; }
    int PCPort() {  return _PCPort; }
    int port() {return _proxy?(_PCPort+100):_PCPort;}
    int index() {return _index; }
    int videoNo() { return _videoNo;}
    bool isPlaying(){ return _isPlaying;}
    int connectionPriority() { return _connectionPriority;}
    bool videoInfo() { return _isVideoInfo; }
    QStringList videoNoListModel() { return _videoNoListModel; }


    QString encoder() {return _encoder;}
    QString videoFormat();
    QAbstractItemModel* videoNoModel(){ return _videoNoModel;   }
    QAbstractItemModel* qualityModel(){ return _qualityModel;   }

signals:
    void requestFormat(VideoItem* v); //set _requestFormat = true before sending
    void boatIDChanged(int ID);
    void PCPortChanged(int port);
    void titleChanged(QString title);
    void indexChanged(int index);
    void videoPlayed(VideoItem* v);
    void videoStoped(VideoItem* v);

private:
    GPBCore* _core;
    QString _title;
    int _boatID;
    int _index;
    int _videoNo;
    int _formatNo;
    int _PCPort;
    int _connectionPriority;
    WId _xwinid;
    QString _encoder;
    bool _proxy;
    bool _requestFormat;
    QQuickItem* _videoWidget;

    GstElement *_pipeline;
    GstElement *_sink;
    bool _isPlaying;
    bool _isVideoInfo;

    bool _proxyMode;
    QStringList _videoFormatList;
    QStandardItemModel* _videoNoModel;
    QStandardItemModel* _qualityModel;

    QStringList _videoNoListModel;


};

#endif // VIDEOITEM_H
