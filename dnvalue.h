#ifndef DNVALUE_H
#define DNVALUE_H

#include <QObject>
#include <QVariant>
#include "dnmetadata.h"

class DNValue : public QObject
{
    Q_OBJECT
public:
    DNValue(QObject *parent = nullptr);
    DNValue(QVariant _rawValue, DNMetaData::ValueType_t type, QObject *parent = nullptr);
    DNValue(const DNValue& other, QObject *parent = nullptr);
    const DNValue& operator = (const DNValue& other);
    QVariant data() { return _rawValue; }
    QByteArray bytesData();
    DNMetaData::ValueType_t dataType() { return _type; }
    ~DNValue();
    static QVariant parseString(QString s, DNMetaData::ValueType_t type);
    void setValue(QVariant value) { _rawValue = value; }
    void setValue(QString s) { _rawValue = parseString(s, _type);}

private:

    QVariant _rawValue;
    DNMetaData::ValueType_t _type;
};

#endif // DNVALUE_H
