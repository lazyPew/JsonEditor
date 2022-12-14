#include "valueobject.h"
#include "valuemaps.h"

#include <QJsonDocument>
#include <QDebug>

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

QJsonValue ValueObject::maxValue() const { return _additionalFields.value("max"); }
QJsonValue ValueObject::minValue() const { return _additionalFields.value("min"); }
QVariantList ValueObject::except() const { return (_additionalFields.value("except").toArray().toVariantList()); }
QString ValueObject::units() const { return _additionalFields.value("units").toString(); }
QString ValueObject::regex() const { return _additionalFields.value("regex").toString(); }


QJsonObject ValueObject::getJson()
{
    QJsonObject valueJson;
    valueJson.insert("type", type());
    valueJson.insert("value", value());
    valueJson.insert("isEditable", isEditable());
    valueJson.insert("isNull", isNull());
    valueJson.insert("default", defaultValue());
    valueJson.insert("desc", desc());

    if (!_additionalFields.isEmpty()){
        for(QString field: _additionalFields.keys()){
            valueJson.insert(field,_additionalFields.value(field));
        }
    }
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
        clearAdditionalFields();
        if(_typeCode != ValueType::EnumType)
            setType(getType(_typeCode));
        resetFields();
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

void ValueObject::setDefaultValue(QJsonValue newValue)
{
    if(newValue != _defaultValue){
        _defaultValue = newValue;
        emit defaultValueChanged(_defaultValue);
    }
}

void ValueObject::setDesc(QString newValue)
{
    if(newValue != _desc){
        _desc = newValue;
        emit descChanged(_desc);
    }
}

void ValueObject::setMaxValue(QJsonValue newValue)
{
    if(newValue == QJsonValue::Null)
        _additionalFields.remove("max");
    else if(newValue != _additionalFields.value("max")){
        _additionalFields.insert("max",newValue);
    }
}


void ValueObject::setMinValue(QJsonValue newValue)
{
    if(newValue == QJsonValue::Null)
        _additionalFields.remove("min");
    else if(newValue != _additionalFields.value("min")){
        _additionalFields.insert("min",newValue);
    }
}


void ValueObject::setExcept(QVariant newValue)
{
    QJsonArray newArray = QJsonArray(QJsonDocument::fromJson(
                                   newValue.toByteArray()).array());
    if(newArray != _additionalFields.value("except").toArray()){
       if(newArray.size()>0)
           _additionalFields.insert("except",newArray);
       else
           _additionalFields.remove("except");
    }
}


void ValueObject::setUnits(QString newValue)
{
    if(newValue != _additionalFields.value("units").toString()){
        _additionalFields.insert("units",newValue);
    }
}


void ValueObject::setRegex(QString newValue)
{
    if(newValue != _additionalFields.value("regex").toString()){
        if(!newValue.isEmpty())
            _additionalFields.insert("regex",newValue);
        else
            _additionalFields.remove("regex");
    }
}

void ValueObject::clearAdditionalFields(){
    for(QString field: _additionalFields.keys())
        _additionalFields.remove(field);
}

void ValueObject::resetFields()
{
    _isNull = true;
    _value = QJsonValue::Undefined;
    _defaultValue = QJsonValue::Undefined;
}
