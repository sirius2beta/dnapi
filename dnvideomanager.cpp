#include "dnvideomanager.h"
//#include "dnapplication.h"
#include "gpbcore.h"
#include "dntypes.h"
#include "QGCApplication.h"
#include <QQmlEngine>
#include <QQuickItem>


DNVideoManager::DNVideoManager(QObject *parent, GPBCore* core)
    : QObject{parent},
      _core(core)
{
    QCoreApplication::setOrganizationName("Ezosirius");
    QCoreApplication::setApplicationName("GPlayer_v1");
    settings = new QSettings;

}

DNVideoManager::~DNVideoManager()
{
    gst_element_set_state (_testpipeline, GST_STATE_NULL);
    gst_object_unref (_testpipeline);

}

void DNVideoManager::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    int window_count = 4;
    QString _config = _core->config();
    for(int i = 0; i < window_count; i++){
        //create settings if first time opened
        if(settings->value(QString("%1/w%2/in_port").arg(_config,QString::number(i))) == QVariant()){
            QList<QString> formatlist = {"video0", "YUYV", "640-480-15", "nan", "80", "192.168.0.100", "5200"};
            settings->setValue(QString("%1/w%2/boat_name").arg(_config,QString::number(i)),QString("unknown"));
            settings->setValue(QString("%1/w%2/in_port").arg(_config,QString::number(i)),5200+i);
            settings->setValue(QString("%1/w%2/title").arg(_config,QString::number(i)),QString("window%1").arg(i));
            settings->setValue(QString("%1/w%2/videoinfo").arg(_config,QString::number(i)), 1);
            settings->setValue(QString("%1/w%2/formatno").arg(_config,QString::number(i)), 0);
        }
        QString title = settings->value(QString("%1/w%2/title").arg(_config,QString::number(i))).toString();

        int PCPort = 5201+i;

        addVideoItem(i, title, -1, -1, -1, PCPort);

    }


}

void DNVideoManager::initVideo()
{
    QQuickWindow* root = qgcApp()->mainRootWindow();
    QQuickItem* widget = root->findChild<QQuickItem*>("videoContent");
    for(int i = 0; i < videoList.size(); i++){
        if(i == 0){
            videoList[i]->initVideo(widget);
            //setVideoTest(widget);
        }
    }
}

void DNVideoManager::initGstreamer(int argc, char* argv[])
{


    _testpipeline = gst_parse_launch("videotestsrc ! glupload ! qmlglsink name=sink",NULL);
    _testsink = gst_bin_get_by_name((GstBin*)_testpipeline,"sink");
}

void DNVideoManager::setVideoTest(QQuickItem* widget)
{
    g_object_set(_testsink, "widget", widget, NULL);
    gst_element_set_state (_testpipeline, GST_STATE_PLAYING);
}

void DNVideoManager::addVideoItem(int index, QString title, int boatID, int videoNo, int formatNo, int PCPort)
{
    VideoItem* newvideoitem = new VideoItem(this, _core, index, title, boatID, videoNo, formatNo, PCPort);
    if(settings->value(QString("%1/w%2/videoinfo").arg(_core->config(),QString::number(newvideoitem->index()))) == 1){
        newvideoitem->setVideoInfo(true);
    }else{
        newvideoitem->setVideoInfo(false);
    }
    videoList.append(newvideoitem);
    connect(newvideoitem, &VideoItem::videoPlayed, this, &DNVideoManager::onPlay);
    connect(newvideoitem, &VideoItem::videoStoped, this, &DNVideoManager::onStop);
    connect(newvideoitem, &VideoItem::requestFormat, this, &DNVideoManager::onRequestFormat);

}

void DNVideoManager::onPlay(VideoItem* videoItem)
{
    QHostAddress ip = QHostAddress(_core->boatManager()->getBoatbyID(videoItem->boatID())->currentIP());
    QString msg = "video"+QString::number(videoItem->videoNo())+" "+videoItem->videoFormat()+" "+videoItem->encoder()+" nan"+" 90"+" "+QString::number(videoItem->port());
    if(msg == QString("")) return;
    emit sendMsg(ip, DNTypes::Command, msg.toLocal8Bit());
}

void DNVideoManager::onStop(VideoItem* videoItem)
{
    QString videoNo = QString("video")+QString::number(videoItem->videoNo());
    if(_core->boatManager()->getBoatbyID(videoItem->boatID()) == 0){
        qDebug()<<"Fatal:: DNVideoManager::onStop, boat ID:"<< videoItem->boatID()<<" not exist";
        return;
    }
    QHostAddress ip = QHostAddress(_core->boatManager()->getBoatbyID(videoItem->boatID())->currentIP());
    emit sendMsg(ip, char(DNTypes::Quit), videoNo.toLocal8Bit());
}

void DNVideoManager::onBoatAdded()
{
    for(int i = 0; i<videoList.size(); i++){
        if(videoList[i]->boatID() == -1){
            videoList[i]->setVideoNo(0);
        }
    }
}

void DNVideoManager::onRequestFormat(VideoItem* videoItem)
{
    QHostAddress addr(_core->boatManager()->getBoatbyID(videoItem->boatID())->currentIP());
    qDebug()<<"DNVideoManager::onRequestFormat: currentIP:"<<_core->boatManager()->getBoatbyID(videoItem->boatID())->currentIP();
    emit sendMsg(addr, DNTypes::Format,"qformat");
}

void DNVideoManager::setVideoFormat(int ID, QStringList videoformat)
{
    for(int i = 0; i < videoList.size(); i++){
        if(videoList[i]->boatID() == ID){
            qDebug()<<"set format, index:"<<_core->boatManager()->getIndexbyID(ID);
            videoList[i]->setVideoFormat(videoformat);

        }
    }
}

void DNVideoManager::onConnectionChanged(int connectionType)
{
    for(int i = 0; i < videoList.size(); i++){
        videoList[i]->setConnectionPriority(connectionType);
    }
}

void DNVideoManager::connectionChanged(int ID)
{
    qDebug()<<"DNVideoManager::connectionChanged: "<<ID;
    for(int i = 0; i < videoList.size(); i++){
        if(videoList[i]->boatID() == ID){
            if(videoList[i]->isPlaying()){
                videoList[i]->stop();
                videoList[i]->play();
            }

        }
    }
}
