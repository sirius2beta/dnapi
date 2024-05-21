#include "controlitem.h"

ControlItem::ControlItem(QObject *parent, QString name, int controlType, QVector<DNValue> fields)
: QObject{parent},
_name(name),
_controlType(controlType),
_fields(fields),
_boatID(-1)
{

}

ControlItem::ControlItem(const ControlItem& other, QObject *parent)
{
    *this = other;
}


const ControlItem& ControlItem::operator =(const ControlItem& other)
{
    _name = other._name;
    _controlType = other._controlType;
    _fields = other._fields;
    _boatID = other._boatID;
    return *this;
}

void ControlItem::setField(int index, QString value)
{
    if(index >= _fields.size()){
        qDebug()<<"\u001b[38;5;203m"<<"**Fatal error: ControlItem::setField index outof range"<<"\033[0m";
    }else{
        _fields[index].setValue(value);
    }

}

void ControlItem::sendCMD()
{
    QByteArray data;
    for(int i = 0; i < _fields.size(); i++){
        data += _fields[i].bytesData();
    }
    emit sendMsg(data);
}
