#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QXmlStreamReader>

#include <QStandardItemModel>

#include "dnvalue.h"
#include "sensorgroup.h"

#include "QDebug"

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfigManager(QObject *parent = nullptr);
    int message(QString msg);
    QString messageChar(uint8_t index);
    QString videoFormatString(uint8_t index){ return _videoFormatTypeList[index]; }
    QVector<SensorGroup> sensorGropList() { return _sensorGropList;};
    QVector<QString> controlList() { return _controlTypeList; }

signals:
protected:
    void readSensorTypes();
    void readMessageTypes();
    void readVideoFormatTypes();
    void readControlTypes();
private:
    QXmlStreamReader reader;
    QStandardItemModel* s;

    QVector<SensorGroup> _sensorGropList;


    QMap<QString, uint8_t> _messageTypeMap;
    QVector<QString> _videoFormatTypeList;
    QVector<QString> _controlTypeList;
};

#endif // CONFIGMANAGER_H
