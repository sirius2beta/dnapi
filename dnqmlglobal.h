#ifndef DNQMLGLOBAL_H
#define DNQMLGLOBAL_H

#include <QObject>

#include "boatmanager.h"
#include "networkmanager.h"
#include "dnvideomanager.h"

class DNCore;

class DNQmlGlobal : public QObject
{
    Q_OBJECT



public:
    explicit DNQmlGlobal(QObject *parent = nullptr, DNCore* core = nullptr);

    Q_INVOKABLE QString programName() const {return _programName;}

    Q_PROPERTY(QString programName READ programName CONSTANT);
    Q_PROPERTY(NetworkManager* networkManager READ networkManager CONSTANT);
    Q_PROPERTY(BoatManager* boatManager READ boatManager CONSTANT);
    Q_PROPERTY(DNVideoManager* videoManager READ videoManager CONSTANT);
    Q_PROPERTY(int boatListmodel READ boatListmodel CONSTANT)

    NetworkManager* networkManager() { return _networkManager; }
    BoatManager* boatManager() { return _boatManager; }
    DNVideoManager* videoManager() { return _videoManager; }
    int boatListmodel() const {return 0;}
signals:
private:
    DNCore* _core;
    NetworkManager* _networkManager = nullptr;
    BoatManager* _boatManager = nullptr;
    DNVideoManager* _videoManager = nullptr;
    QString _programName ;
};

#endif // DNQMLGLOBAL_H
