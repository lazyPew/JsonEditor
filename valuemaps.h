#ifndef VALUEMAPS_H
#define VALUEMAPS_H

#include <valueslistmodel.h>
//extern class ValueObject;

const QMap<QString, ValueObject::ValueType> valueTypesMap = {
    { "ipstring", ValueObject::ValueType::IpStringType },
    { "ipdigit" , ValueObject::ValueType::IpDigitType },
    { "domen" , ValueObject::ValueType::DomenType },
    { "_enum", ValueObject::ValueType::EnumType },
    { "gnssstring" , ValueObject::ValueType::GnssStringType, },
    { "gnssdigit" , ValueObject::ValueType::GnssDigitType, },
    { "int" , ValueObject::ValueType::IntType, },
    { "float" , ValueObject::ValueType::FloatType, },
    { "boolean" , ValueObject::ValueType::BooleanType, },
    { "array" , ValueObject::ValueType::ArrayType, },
    { "null" , ValueObject::ValueType::NullType, }
};

#endif // VALUEMAPS_H
