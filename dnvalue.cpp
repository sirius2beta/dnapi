#include "dnvalue.h"
#include <QQmlEngine>
DNValue::DNValue(QObject *parent)
    : QObject{parent},
    _rawValue(0),
    _type(DNMetaData::valueTypeUint32)
{
QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

DNValue::DNValue(float f)
    : _rawValue(f),
    _type(DNMetaData::valueTypeFloat)
{
QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

DNValue::DNValue(uint32_t i)
    : _rawValue(i),
    _type(DNMetaData::valueTypeUint32)
{
QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

DNValue::DNValue(int i)
    : _rawValue(i),
    _type(DNMetaData::valueTypeUint32)
{
QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

DNValue::DNValue(QVariant _rawValue, DNMetaData::ValueType_t type, QObject *parent)
    : QObject{parent},
    _rawValue(0),
    _type(type)
{
QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

DNValue::DNValue(const DNValue& other, QObject *parent)
{
    *this = other;
}

const DNValue& DNValue::operator =(const DNValue& other)
{
    _rawValue = other._rawValue;
    _type = other._type;
    _name = other._name;
    return *this;
}

QByteArray DNValue::bytesData()
{
    if(_type == DNMetaData::valueTypeUint32){
        char str1[sizeof(uint)];
        uint str2 = _rawValue.toUInt();
        memcpy(str1, &str2, sizeof(uint));
        return QByteArray(str1,sizeof(uint));
    }else if(_type == DNMetaData::valueTypeFloat){
        char str1[sizeof(float)];
        float str2 = _rawValue.toFloat();
        memcpy(str1, &str2, sizeof(float));
        return QByteArray(str1,sizeof(float));
    }else if(_type == DNMetaData::valueTypeBool){
        if(_rawValue.toBool()){
           return QByteArray(1,sizeof(bool));
        }else{
           return QByteArray(0, sizeof(bool));
        }
    }
}

DNValue::~DNValue()
{

}

QVariant DNValue::parseString(QString s, DNMetaData::ValueType_t type)
{
    if(type == DNMetaData::valueTypeUint32){
        return QVariant(s.toInt());
    }else if(type == DNMetaData::valueTypeFloat){
        QVariant(s.toFloat());
    }else if(type == DNMetaData::valueTypeBool){
        if(s.toLower() == "true"){
           return QVariant(true);
        }else{
           return QVariant(false);
        }
    }
    return QVariant();
}
