#ifndef CONTROLITEM_H
#define CONTROLITEM_H

#include <QObject>
#include <QHostAddress>

#include "dnvalue.h"

class ControlItem : public QObject
{
    Q_OBJECT
public:
    explicit ControlItem(QObject *parent, QString name, int controlType, QVector<DNValue> fields);
    ControlItem(const ControlItem& other, QObject *parent = nullptr);
    const ControlItem& operator = (const ControlItem& other);
    void setField(int index, QString value);
    void sendCMD();
signals:
    void sendMsg(QByteArray command);
private:
    QString _name;
    int _controlType;
    QVector<DNValue> _fields;
    int _boatID;

};

#endif // CONTROLITEM_H
