#include <QQmlEngine>
#include "controlmanager.h"
#include "dncore.h"
#include "dncontrol.h"
#include "qdebug.h"
#include "dncore.h"
ControlManager::ControlManager(QObject *parent, DNCore *core)
    : QObject{parent},
      _boatID(-1)
{
    _core = core;
}

void ControlManager::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qDebug()<<"initializing ControlManager...";
    QVector<ControlItem> controls = _core->configManager()->controlList();
    for(int i = 0; i < controls.size(); i++){
        ControlItem* newControl = new ControlItem(controls[i],this);
        connect(newControl, &ControlItem::sendMsg, this, &ControlManager::onMsg);

        _controls.append(newControl);
    }

    qDebug()<<"    ... done";
}

void ControlManager::sendControlMsg(QByteArray msg)
{
}

void ControlManager::setBoatID(int boatID)
{
    _boatID = boatID;
}

void ControlManager::onMsg(QByteArray command)
{
    emit sendMsg(_boatID, _core->configManager()->message(ConfigManager::msg_control()), command);
}
