#ifndef VALUEMAPS_H
#define VALUEMAPS_H

#include <ValueModels/valueobject.h>
#include <QMap>

static const QMap<uint, QString> valueTypesMap = {
    {ValueObject::ValueType::IpStringType, "ipstring" },
    {ValueObject::ValueType::IpDigitType, "ipdigit" },
    {ValueObject::ValueType::DomenType, "domen" },
    {ValueObject::ValueType::EnumType, "_enum" },
    {ValueObject::ValueType::GnssStringType, "gnssstring" },
    {ValueObject::ValueType::GnssDigitType, "gnssdigit" },
    {ValueObject::ValueType::IntType, "int" },
    {ValueObject::ValueType::FloatType, "float" },
    {ValueObject::ValueType::BooleanType, "boolean" },
    {ValueObject::ValueType::ArrayType, "array" },
    {ValueObject::ValueType::NullType, "null" }
};



static QStringList getStringTypes() { return valueTypesMap.values(); }
static QString getType(uint typeCode) { return valueTypesMap.value(typeCode); }
static bool checkType(QString typeStr) { return valueTypesMap.values().contains(typeStr); }


#endif // VALUEMAPS_H
