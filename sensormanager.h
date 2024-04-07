#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QObject>
#include <QSettings>
#include <QStandardItemModel>
#include "sensoritem.h"
#include "sensorgroup.h"
#include "dnvalue.h"
#include "dnqmlobjectlistmodel.h"


class DNCore;

class SensorManager : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(DNQmlObjectListModel* aquaModel READ aquaModel CONSTANT)
    explicit SensorManager(QObject *parent = nullptr, DNCore *core = nullptr);
    void init();
    int count() { return _sensorList.size(); }
    SensorItem* getSensor(int index){ return _sensorList[index];}
    DNQmlObjectListModel* aquaModel(void){return _sensorGroupListModel[1]; }
    Q_INVOKABLE DNQmlObjectListModel* getSensorModel(int index);
    void addSensor(SensorItem *sensorItem);
    void deleteSensor(int index);
    QAbstractItemModel* sensorTypeModel() { return _sensorTypeModel;}
    enum dataType{ int_type = 0, float_type = 1};


signals:
    void sensorDataChanged(int ID, DNValue& value);

public slots:
    void onSensorMsg(int ID, QByteArray data);

private:
    QSettings* settings;
    QVector<SensorItem*> _sensorList;
    QVector<SensorGroup> _sensorGroupList;
    DNCore* _core;
    QStandardItemModel* _sensorTypeModel;
    QList<DNQmlObjectListModel*> _sensorGroupListModel;
};

#endif // SENSORMANAGER_H
