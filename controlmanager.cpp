#include <QQmlEngine>
#include "controlmanager.h"
#include "dncore.h"
#include "dncontrol.h"
#include "qdebug.h"

ControlManager::ControlManager(QObject *parent, DNCore *core)
    : QObject{parent}
{
    _core = core;
}

void ControlManager::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qDebug()<<"initializing ControlManager...";
    QVector<QString> controls = _core->configManager()->controlList();
    for(int i = 0; i < controls.size(); i++){
        DNControl* newControl = new DNControl(this);
        _controls.append(newControl);
    }
    qDebug()<<"    ... done";
}
