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

signals:
protected:
    void readSensorTypes();
    void readMessageTypes();
    void readVideoFormatTypes();
private:
    QXmlStreamReader reader;
    QStandardItemModel* s;

    QVector<SensorGroup> _sensorGropList;


    QMap<QString, uint8_t> _messageTypeMap;
    QVector<QString> _videoFormatTypeList;
};

#endif // CONFIGMANAGER_H
