﻿#ifndef BOATMANAGER_H
#define BOATMANAGER_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <QStandardItemModel>
#include "boatitem.h"
#include <QMetaType>
#include <QObject>
#include <QQmlListProperty>
#include "dnqmlobjectlistmodel.h"

class DNCore;
class BoatManager: public QObject
{
    Q_OBJECT
public:
    BoatManager(QObject* parent = nullptr, DNCore* core = nullptr);
    ~BoatManager();
    Q_PROPERTY(DNQmlObjectListModel* boatListModel READ boatListModel CONSTANT)
    QAbstractItemModel* model() const {return boatItemModel;}
    void init();
    BoatItem* addBoat(int ID, QString boatname, QString PIP, QString SIP);
    void deleteBoat(int index);

    BoatItem* getBoatbyIndex(int index);
    BoatItem* getBoatbyID(int ID);
    Q_INVOKABLE int getIDbyInex(int index);
    Q_INVOKABLE int getIndexbyID(int ID);
    DNQmlObjectListModel* boatListModel(void) { return &_boatListModel;}
    QString CurrentIP(QString boatname);
    //void setConnectionType(int connectiontype);
    int size();
signals:
    void BoatAdded();
    void connectionTypeChanged(int connectiontype);
    void connectionChanged(int ID);
public slots:
    void onBoatNameChange(int ID, QString newname);
    void onIPChanged(int ID, bool primary);
    void onConnectStatusChanged(int ID, bool isprimary, bool isConnected);
    //void onDisonnected(int ID, bool isprimary);
    void onConnectionTypeChanged(int connectiontype);

private:
    QSettings *settings;
    QStandardItemModel* boatItemModel;
    QList<BoatItem*> _boatList;
    int _connectionType;
    DNCore* _core;
    DNQmlObjectListModel _boatListModel;
};

#endif // BOATMANAGER_H
