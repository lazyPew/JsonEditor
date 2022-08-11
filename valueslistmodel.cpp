#include "valueslistmodel.h"
#include "valuemaps.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ValueObject::ValueObject(
        QString device,
        QString name,
        ValueType type,
        QJsonValue value,
        QObject *parent)
    : QObject(parent)
    , _device(device)
    , _name(name)
    , _type(type)
    , _value(value)
{}

void ValueObject::setDevice(QString newValue)
{
    if(newValue != _device){
        _device = newValue;
        emit deviceChanged(_device);
    }
}

void ValueObject::setName(QString newValue)
{
    qDebug() << newValue;
    if(newValue != _name){
        _name = newValue;
        emit nameChanged(_name);
    }
}

void ValueObject::setType(QString newValue)
{
    ValueObject::ValueType newType = valueTypesMap.value(newValue);
    if(newType != _type){
        _type = newType;
        emit typeChanged(newValue);
    }
}

void ValueObject::setValue(QJsonValue newValue)
{
    valueConversion(newValue);
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
void ValueObject::setDescription(QString newValue)
{
    if(newValue != _description){
        _description = newValue;
        emit descriptionChanged(_description);
    }
}
void ValueObject::setDefault(QJsonValue newValue)
{
    valueConversion(newValue);
}

void ValueObject::valueConversion(QJsonValue value)
{

}


ValuesListModel::ValuesListModel(QObject *parent)
    : QAbstractListModel(parent)
    , _valueObjectsList{}
{
    qRegisterMetaType<ValuesListModel*>("ValuesListModel*");
}

void ValuesListModel::addValueObject(ValueObject *valueObject)
{
    int index = _valueObjectsList.size();
    beginInsertRows(QModelIndex(), index, index);
    _valueObjectsList.append(valueObject);
    endInsertRows();
}

int ValuesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _valueObjectsList.size();
}

QVariant ValuesListModel::data(const QModelIndex &index, int role) const
{
    auto const row = index.row();

    switch (role) {
    case static_cast<int>(Roles::DeviceRole):
        return _valueObjectsList.at(row)->device();
    case static_cast<int>(Roles::NameRole):
        return _valueObjectsList.at(row)->name();
    case static_cast<int>(Roles::TypeRole):
        return valueTypesMap.key(_valueObjectsList.at(row)->type());
    case static_cast<int>(Roles::ValueRole):
        return convertJsonValue(_valueObjectsList.at(row)->type(),
                                _valueObjectsList.at(row)->value());
//        return _valueObjectsList.at(row)->value().toString();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ValuesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::DeviceRole)] = "deviceRole";
    roles[static_cast<int>(Roles::NameRole)] = "nameRole";
    roles[static_cast<int>(Roles::TypeRole)] = "typeRole";
    roles[static_cast<int>(Roles::ValueRole)] = "valueRole";
    return roles;
}

QList<ValueObject *> ValuesListModel::valueObjectsList() const
{
    return _valueObjectsList;
}

ValueObject *ValuesListModel::valueObjectAt(int index) const
{
    return _valueObjectsList.at(index);
}

QVariant ValuesListModel::convertJsonValue(ValueObject::ValueType type, QJsonValue jsonValue) const
{
    switch (type) {
    case ValueObject::ValueType::IpStringType:
    case ValueObject::ValueType::DomenType:
    case ValueObject::ValueType::GnssStringType:
        return jsonValue.toString();
    case ValueObject::ValueType::IpDigitType:
    case ValueObject::ValueType::IntType:
        return jsonValue.toInt();
    case ValueObject::ValueType::FloatType:
        return jsonValue.toDouble();
    case ValueObject::ValueType::BooleanType:
        return jsonValue.toBool();
//        return jsonValue.toString();
    case ValueObject::ValueType::ArrayType:
        return jsonValue.toArray();
    case ValueObject::ValueType::GnssDigitType:
    case ValueObject::ValueType::EnumType:
    case ValueObject::ValueType::NullType:
        return jsonValue.toVariant();

    default:
        return QVariant();
    }
}

