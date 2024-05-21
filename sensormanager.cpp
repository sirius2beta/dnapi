#include "sensormanager.h"
#include "dncore.h"
#include <QByteArray>
#include <QVariant>
#include <QQmlEngine>

SensorManager::SensorManager(QObject *parent, DNCore* core)
    : QObject{parent},
    _core(core)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    settings = new QSettings("Ezosirius", "GPlayer_v1", this);
}

void SensorManager::init()
{
    qDebug()<<"sensorManager:: Initiating...";

    QVector<SensorGroup> _sensorGroupList = _core->configManager()->sensorGropList(); //從configmanager取得sensorgrouplist
    //將_sensorGroupList轉存為_sensorGroupListModel

    for(int i = 0; i< _sensorGroupList.count(); i++){
        DNQmlObjectListModel* model = new DNQmlObjectListModel(this); // model為sensorgrouplist其中一個sensorGroup

        for(int j = 0; j < _sensorGroupList[i].count(); j++){
            model->append(_sensorGroupList[i][j]);

        }
        _sensorGroupListModel.append(model);
    }
    qDebug()<<"sensorManager:: Initiate complete";
}

DNQmlObjectListModel* SensorManager::getSensorModel(int index)
{

    if(index<_sensorGroupListModel.size()){
        return _sensorGroupListModel[index];
    }else{
        qDebug()<<"**Fatal: sensorManager:: getSensorModel: index out of range";
        return nullptr;
    }
}


void SensorManager::onSensorMsg(int ID, QByteArray data)
{

    //DNMetaData::ValueType_t datatype;
   //qDebug()<<data;
    uint8_t sensortype;
    char* cdata = data.data();
    if(_sensorGroupListModel.size() == 0) return;
    memcpy(&sensortype, cdata, sizeof(uint8_t));
    qDebug()<<"SensorManager:: on msg: boat ID:"<<ID;

    qDebug()<<"SensorManager:: on msg: size:"<<data.size()/4<<"bytes";
    qDebug()<<"SensorManager:: on msg: sensor type:"<<sensortype;
}
