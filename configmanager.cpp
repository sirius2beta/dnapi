﻿#include "configmanager.h"
#include <QFile>
#include <QDebug>
#include <QQmlEngine>


ConfigManager::ConfigManager(QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    QFile file("SensorType.xml");
    reader.setDevice(&file);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"file opened";

        if (reader.readNextStartElement()) {
            if (reader.name().toString() == "marinelink"){
                while(reader.readNextStartElement()){
                    if(reader.name().toString() == "enum"){
                        if(reader.attributes().value("name").toString() == "SENSOR_TYPE"){

                            readSensorTypes();
                        }else if(reader.attributes().value("name").toString() == "MESSAGE_TYPE"){
                            reader.skipCurrentElement();

                        }

                    }
                    else
                        reader.skipCurrentElement();
                }
            }
            else
                reader.raiseError(QObject::tr("ConfigManager:: Incorrect xml config file"));
        }
    }
    file.close();
    qDebug()<<"ConfigManager:: xml file closed";
}

void ConfigManager::readSensorTypes()
{
    _sensorTypeList.clear();
    while(reader.readNextStartElement()){

        if(reader.name().toString() == "entry"){
            qDebug()<<reader.attributes().value("name");
            int sensorType = reader.attributes().value("value").toInt();
            QString name = reader.attributes().value("name").toString();
            QString type = reader.attributes().value("type").toString();
            DNMetaData::ValueType_t dataType = DNMetaData::stringToType(type);
            qDebug()<<type;
            _sensorTypeList.append(DNValue(sensorType, name, dataType));
            // readElementText at last to prevent breaking loop
            QString s = reader.readElementText();
        }
    }
}
