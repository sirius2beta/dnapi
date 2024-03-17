#include "gpbcore.h"
#include <QQmlEngine>

GPBCore::GPBCore(QObject *parent, QString config)
    : QObject{parent},
      _config(config)
{
    settings = new QSettings("Ezosirius", "GPlayer_v1",this);
    _configManager = new ConfigManager();
    _networkManager = new NetworkManager(this, this);
    _boatManager = new BoatManager(this, this);
    _videoManager = new DNVideomanager(this, this);
    _sensorManager = new SensorManager(this, this);


    connect(_videoManager, &DNVideomanager::sendMsg, _networkManager, &NetworkManager::sendMsg);
    connect(_networkManager, &NetworkManager::setFormat, _videoManager, &DNVideomanager::setVideoFormat);
    connect(_boatManager, &BoatManager::connectionChanged, _videoManager, &DNVideomanager::connectionChanged);
    connect(_boatManager, &BoatManager::connectionTypeChanged, _videoManager, &DNVideomanager::onConnectionChanged);
    connect(_boatManager, &BoatManager::BoatAdded, _videoManager, &DNVideomanager::onBoatAdded);
    connect(_networkManager, &NetworkManager::sensorMsg, _sensorManager, &SensorManager::onSensorMsg);

    init();
}

GPBCore::~GPBCore(){
    delete _boatManager;
}

void GPBCore::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    _videoManager->init();
    _sensorManager->init();
    _networkManager->init();

    // Register our Qml objects
    // Register Qml Singletons

}


