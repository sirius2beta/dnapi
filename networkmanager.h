﻿#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include "boatmanager.h"

class DNCore;

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr, DNCore* core = nullptr);
    void init();

signals:
    void AliveResponse(QString ip, int ID);
    void setFormat(int ID, QStringList format);
    void sensorMsg(int ID, QByteArray data);
public slots:
    void sendMsg(QHostAddress addr, char topic, QByteArray command);

protected slots:
    void onUDPMsg();
private:
    QUdpSocket *serverSocket;
    QUdpSocket *clientSocket;
    DNCore* _core;
};

#endif // NETWORKMANAGER_H
