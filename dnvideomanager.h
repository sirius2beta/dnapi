﻿#ifndef DNVIDEOMANAGER_H
#define DNVIDEOMANAGER_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QHostAddress>
#include <QQuickItem>
#include <gst/gst.h>

#ifdef DNAPI_QML
#include "videoitem_qml.h"
#else
#include "videoitem.h"
#endif


class GPBCore;

class DNVideoManager : public QObject
{
    Q_OBJECT
public:

    explicit DNVideoManager(QObject *parent = nullptr, GPBCore* core = nullptr);
    void init();
    ~DNVideoManager();
    void initVideo();
    void initGstreamer(int argc, char* argv[]);
    void setVideoTest(QQuickItem* widget);
    void addVideoItem(int index, QString title, int boatID, int videoNo, int formatNo, int PCPort);
    VideoItem* getVideoItem(int index) { return videoList[index];}
    int size() { return videoList.size();  }


public slots:
    void onPlay(VideoItem* videoItem);
    void onStop(VideoItem* videoItem);
    void onBoatAdded();
    void onRequestFormat(VideoItem* videoItem);
    void setVideoFormat(int ID, QStringList videoformat);
    void onConnectionChanged(int connectionType);
    void connectionChanged(int ID);
signals:
    void sendMsg(QHostAddress addr, char topic, QByteArray command);

private:
    QVector<VideoItem*> videoList;
    QSettings* settings;
    GPBCore* _core;
    GstElement *_testpipeline;
    GstElement *_testsink;

};

#endif // DNVIDEOMANAGER_H
