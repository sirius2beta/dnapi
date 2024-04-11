#ifndef CONTROLMANAGER_H
#define CONTROLMANAGER_H
#include <QObject>

#include "dnqmlobjectlistmodel.h"

class DNCore;
class ControlManager : public QObject
{
    Q_OBJECT
public:
    explicit ControlManager(QObject *parent = nullptr, DNCore *core = nullptr);

    void init();

signals:

private:
    DNCore* _core;
    int BoatID;
    DNQmlObjectListModel _controls;

};

#endif // CONTROLMANAGER_H
