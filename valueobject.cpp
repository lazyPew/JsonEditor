#include "valueobject.h"
#include "valuemaps.h"

ValueObject::ValueObject(
        QString device,
        QString name,
        uint typeCode,
        QObject *parent,
        QJsonValue value,
        bool isEditable,
        bool isNull,
        QJsonValue defaultValue,
        QString desc)
    : QObject(parent)
    , _device(device)
    , _name(name)
    , _typeCode(typeCode)
    , _value(value)
    , _isEditable(isEditable)
    , _isNull(isNull)
    , _defaultValue(defaultValue)
    , _desc(desc)
{}

QJsonObject ValueObject::getJson()
{
    QJsonObject valueJson;
    valueJson.insert("type", type());
    valueJson.insert("value", value());
    valueJson.insert("isEditable", isEditable());
    valueJson.insert("isNull", isNull());
    valueJson.insert("default", defaultValue());
    valueJson.insert("desc", desc());
    return valueJson;
}

void ValueObject::setDevice(QString newValue)
{
    if(newValue != _device){
        _device = newValue;
        emit deviceChanged(_device);
    }
}

void ValueObject::setName(QString newValue)
{
    if(newValue != _name){
        _name = newValue;
        emit nameChanged(_name);
    }
}


void ValueObject::setTypeCode(uint newValue)
{
    if(newValue != _typeCode){
        _typeCode = newValue;
        if(_typeCode != ValueType::EnumType)
            setType(getType(_typeCode));
        emit typeCodeChanged(_typeCode);
    }
}

void ValueObject::setType(QString newValue)
{
    if(newValue != _type){
        _type = newValue;
        emit typeCodeChanged(_typeCode);
    }
}

void ValueObject::setValue(QJsonValue newValue)
{
    if(newValue != _value){
        _value = newValue;
        emit valueChanged(_value);
    }
}

void ValueObject::setIsEditable(bool newValue)
{
    if(newValue != _isEditable){
        _isEditable = newValue;
        emit isEditableChanged(_isEditable);
    }
}
void ValueObject::setIsNull(bool newValue)
{
    if(newValue != _isNull){
        _isNull = newValue;
        emit isNullChanged(_isNull);
    }
}
void ValueObject::setDesc(QString newValue)
{
    if(newValue != _desc){
        _desc = newValue;
        emit descChanged(_desc);
    }
}

void ValueObject::setDefaultValue(QJsonValue newValue)
{
    if(newValue != _defaultValue){
        _defaultValue = newValue;
        emit defaultValueChanged(_defaultValue);
    }
}
