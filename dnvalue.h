#ifndef DNVALUE_H
#define DNVALUE_H

#include <QObject>
#include <QVariant>
#include "dnmetadata.h"

class DNValue : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name CONSTANT)
    DNValue(QObject *parent = nullptr);
    DNValue(float f);
    DNValue(QVariant _rawValue, DNMetaData::ValueType_t type, QObject *parent = nullptr);
    DNValue(const DNValue& other, QObject *parent = nullptr);
    const DNValue& operator = (const DNValue& other);
    QVariant data() { return _rawValue; }
    QByteArray bytesData();
    DNMetaData::ValueType_t dataType() { return _type; }
    QString name(){ return QString("e"); }
    ~DNValue();
    static QVariant parseString(QString s, DNMetaData::ValueType_t type);
    void setValue(QVariant value) { _rawValue = value; }
    void setValue(QString s) { _rawValue = parseString(s, _type);}
    void setName(QString s) { _name=s; }

private:

    QVariant _rawValue;
    DNMetaData::ValueType_t _type;
    QString _name;
};

#endif // DNVALUE_H
