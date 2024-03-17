#include "networkmanager.h"
#include "gpbcore.h"
#include <QQmlEngine>

#include "dntypes.h"

NetworkManager::NetworkManager(QObject *parent, GPBCore *core)
    : QObject{parent}
{
    _core = core;
    serverSocket = new QUdpSocket(this);
    clientSocket = new QUdpSocket(this);
    clientSocket->bind(50008,QUdpSocket::ShareAddress);

}

void NetworkManager::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    connect(clientSocket,&QUdpSocket::readyRead,this, &NetworkManager::onUDPMsg);
}

void NetworkManager::sendMsg(QHostAddress addr, char topic, QByteArray command)
{
    QByteArray cmd;
    cmd.resize(1);
    cmd[0] = topic;
    cmd.append(command);
    serverSocket->writeDatagram(cmd,cmd.size(), addr, 50006);
}

void NetworkManager::onUDPMsg()
{
    while(clientSocket->hasPendingDatagrams()){
        QByteArray data;
        QHostAddress addr;
        QString ip;
        data.resize(clientSocket->pendingDatagramSize());
        clientSocket->readDatagram(data.data(),data.size(),&addr);

        char topic = data[0];
        data.remove(0,1);

        ip = QHostAddress(addr.toIPv4Address()).toString();


        QStringList dataList = QString(data).split(' ');
        QString message;
        if(data.split(' ').size() >1){
            message = data.split(' ')[1];
        }
        if(topic == DNTypes::Heartbeat){
            int ID = int(data[0]);
            BoatItem* boat = _core->boatManager()->getBoatbyID(ID);

            if( boat != 0){

                emit AliveResponse(ip, ID);
            }


        }else if(topic == DNTypes::Format){
            int ID = int(data[0]);
            QString format = data.remove(0,1);
            //qDebug()<<"MainWindow call from FORMAT, boat ID:"<<ID;
            qDebug()<<"Net format ID:"<<ID;
            if(format != ""){
                emit setFormat(ID, format.split('\n'));
            }

        }else if(topic == DNTypes::Sensor){
            int ID = int(data[0]);
            data.remove(0,1);
            emit sensorMsg(ID, data);
        }
        const QString content = QLatin1String(" Received Topic: ")
                    + topic
                                + QLatin1String(" Message: ");
        //qDebug() << content;
    }
}
