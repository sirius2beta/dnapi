﻿#include "gpbcore.h"

GPBCore::GPBCore(QObject *parent, QString config)
    : QObject{parent},
      _config(config)
{
    settings = new QSettings("Ezosirius", "GPlayer_v1",this);
    _configManager = new ConfigManager();
    _networkManager = new NetworkManager(this, this);
    _boatManager = new BoatManager(this, this);
    _videoManager = new DNVideoManager(this, this);
    _sensorManager = new SensorManager(this, this);


    connect(_videoManager, &DNVideoManager::sendMsg, _networkManager, &NetworkManager::sendMsg);
    connect(_networkManager, &NetworkManager::setFormat, _videoManager, &DNVideoManager::setVideoFormat);
    connect(_boatManager, &BoatManager::connectionChanged, _videoManager, &DNVideoManager::connectionChanged);
    connect(_boatManager, &BoatManager::connectionTypeChanged, _videoManager, &DNVideoManager::onConnectionChanged);
    connect(_boatManager, &BoatManager::BoatAdded, _videoManager, &DNVideoManager::onBoatAdded);
    connect(_networkManager, &NetworkManager::sensorMsg, _sensorManager, &SensorManager::onSensorMsg);

    init();
}

GPBCore::~GPBCore(){
    delete _boatManager;
}

void GPBCore::init()
{
    _videoManager->init();
    _sensorManager->init();
    _networkManager->init();

}


