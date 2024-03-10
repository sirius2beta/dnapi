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
    _videoManager = new VideoManager(this, this);
    _sensorManager = new SensorManager(this, this);


    connect(_videoManager, &VideoManager::sendMsg, _networkManager, &NetworkManager::sendMsg);
    connect(_networkManager, &NetworkManager::setFormat, _videoManager, &VideoManager::setVideoFormat);
    connect(_boatManager, &BoatManager::connectionChanged, _videoManager, &VideoManager::connectionChanged);
    connect(_boatManager, &BoatManager::connectionTypeChanged, _videoManager, &VideoManager::onConnectionChanged);
    connect(_boatManager, &BoatManager::BoatAdded, _videoManager, &VideoManager::onBoatAdded);
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


