#include "dnvalue.h"

DNValue::DNValue(QObject *parent)
    : QObject{parent},
    _rawValue(0),
    _type(DNMetaData::valueTypeUint32)
{

}

DNValue::DNValue(QVariant _rawValue, DNMetaData::ValueType_t type, QObject *parent)
    : QObject{parent},
    _rawValue(0),
    _type(type)
{

}

DNValue::DNValue(const DNValue& other, QObject *parent)
{
    *this = other;
}

const DNValue& DNValue::operator =(const DNValue& other)
{
    _rawValue = other._rawValue;
    _type = other._type;
    return *this;
}

DNValue::~DNValue()
{

}
