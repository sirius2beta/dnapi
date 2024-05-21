#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H
#include <QObject>
#include <QHostAddress>

#include "dnqmlobjectlistmodel.h"

class DNCore;
class ControlManager : public QObject
{
    Q_OBJECT
public:
    explicit ControlManager(QObject *parent = nullptr, DNCore *core = nullptr);

    void init();
    void sendControlMsg(QByteArray msg); //call by control
    void setBoatID(int boatID);
signals:
    void sendMsg(int boatID, char topic, QByteArray command);
protected slots:
    void onMsg(QByteArray command);
private:
    DNCore* _core;
    int _boatID;
    DNQmlObjectListModel _controls;

};

#endif // CONTROLMANAGER_H
