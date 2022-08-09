#ifndef VALUEMAPS_H
#define VALUEMAPS_H

#include <valueslistmodel.h>
//extern class ValueObject;

const QMap<ValueObject::ValueType, QString> valueTypesMap = {
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

#endif // VALUEMAPS_H
