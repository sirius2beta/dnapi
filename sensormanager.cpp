#include "sensormanager.h"
#include "dncore.h"
#include <QByteArray>
#include <QVariant>
#ifdef USE_QML
#include <QQmlEngine>
#endif

SensorManager::SensorManager(QObject *parent, DNCore* core)
    : QObject{parent},
    _core(core)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    settings = new QSettings("Ezosirius", "GPlayer_v1", this);
    _sensorTypeModel = new QStandardItemModel;
}

void SensorManager::init()
{
    qDebug()<<"sensorManager:: Initiating...";

    _sensorGroupList = _core->configManager()->sensorGropList();
    for(int i = 0; i< _sensorGroupList.count(); i++){
        DNQmlObjectListModel* model = new DNQmlObjectListModel(this);
        for(int j = 0; j < _sensorGroupList[i].count(); j++){
            model->append(_sensorGroupList[i][j]);

        }
        _sensorGroupListModel.append(model);
    }

    qDebug()<<"sensorManager:: Initiate complete";
}

DNQmlObjectListModel* SensorManager::getSensorModel(int index)
{
    if(index<_sensorGroupList.size()){
        return _sensorGroupListModel[index];
    }else{
        qDebug()<<"**Fatal: sensorManager:: getSensorModel: index out of range";
        return nullptr;
    }
}

void SensorManager::addSensor(SensorItem* sensorItem)
{
    _sensorList.append(sensorItem);
}

void SensorManager::deleteSensor(int index)
{
    _sensorList.remove(index);
}

void SensorManager::onSensorMsg(int ID, QByteArray data)
{

    //DNMetaData::ValueType_t datatype;
    int sensortype;
    char* cdata = data.data();
    if(_sensorList.size() == 0) return;
    int readorder = 0;
    for(int i = 0; i < data.size()/4; i++){
        if(readorder == 0){
            memcpy(&sensortype, cdata, sizeof(int));
            qDebug()<<"SensorManager:: on msg: boat ID:"<<ID;
            qDebug()<<"SensorManager:: on msg: size:"<<data.size()/4<<"bytes";
            qDebug()<<"SensorManager:: on msg: sensor type:"<<sensortype;
            cdata+=4;
        }else if(readorder == 1){
            /*
            //QByteArray sensordata(data.data()+i,1);
            readorder = -1;
            if(sensortype >= _core->configManager()->sensorTypeList().size()){
                qDebug()<<"**Fatal SensorManager::Sensor type out of range, type index:"<<sensortype;
                return;
            }
            DNValue value = _core->configManager()->sensorTypeList()[sensortype];
            if(value.dataType() == DNMetaData::valueTypeUint32){
                int i;
                memcpy(&i, cdata, sizeof(int));
                value.setValue(QVariant(i));
                qDebug()<<"get int data: "<<i;
                cdata+=4;
            }else if(value.dataType() == DNMetaData::valueTypeFloat){
                float f;
                memcpy(&f, cdata, sizeof(float));
                value.setValue(QVariant(f));
                qDebug()<<"get float data: "<<f;
                cdata+=4;
            }else if(value.dataType() == DNMetaData::valueTypeBool){
                int i;
                memcpy(&i, cdata, sizeof(int));
                value.setValue(QVariant(i));
                qDebug()<<"get bool : "<<i;
                cdata+=4;
            }else{
                qDebug()<<"**Fatal SensorManager::Data type out of range, type index:"<<value.dataType();
                return;
            }
            for(int i = 0; i< _sensorList.size(); i++){
                qDebug()<<"sensor list sensor-"<<i<<" : sensorType:"<<_sensorList[i]->value().SensorType()<<" , ID: "<<_sensorList[i]->boatID();
                if(_sensorList[i]->boatID() == ID && _sensorList[i]->value().SensorType() == sensortype){
                    _sensorList[i]->setValue(value);
                }
            }
            */
        }

        readorder ++;
    }
}
