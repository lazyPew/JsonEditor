#include "valueslistmodel.h"
#include "valuemaps.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ValueObject::ValueObject(
        QString device,
        QString name,
        uint type,
        QJsonValue value,
        QObject *parent)
    : QObject(parent)
    , _device(device)
    , _name(name)
    , _typeCode(type)
    , _value(value)
{}

void ValueObject::setDevice(QString newValue)
{
    if(newValue != _device){
        qDebug() << "new Value" << newValue;
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
        emit typeChanged(_typeCode);
    }
}

void ValueObject::setValue(QJsonValue newValue)
{
    qDebug() << _value << newValue;
    if(newValue != _value){
        qDebug() << "new Value" << newValue;
        _value = newValue;
        emit valueChanged(_value);
    }}

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
void ValueObject::setDefault(QJsonValue newValue)
{
    valueConversion(newValue);
}

QString ValueObject::typeString() const
{
    return getType(_typeCode);
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
        return _valueObjectsList.at(row)->typeString();
    case static_cast<int>(Roles::TypeCodeRole):
        return _valueObjectsList.at(row)->typeCode();
    case static_cast<int>(Roles::ValueRole):
        return convertFromJsonValue(_valueObjectsList.at(row)->typeCode(),
                                _valueObjectsList.at(row)->value());
//        return _valueObjectsList.at(row)->value().toString();
    case static_cast<int>(Roles::IsEditableRole):
        return _valueObjectsList.at(row)->isEditable();
    case static_cast<int>(Roles::IsNullRole):
        return _valueObjectsList.at(row)->isNull();
    case static_cast<int>(Roles::DescRole):
        return _valueObjectsList.at(row)->desc();
    default:
        return QVariant();
    }
}

bool ValuesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ValueObject* valueObject = _valueObjectsList[index.row()];

    switch(role){
//    DeviceRole
//    ValueRole,

    case DeviceRole:
        qDebug() << "new Value" ;
        valueObject->setDevice(value.toString());
        break;

    case NameRole:
        valueObject->setName(value.toString());
        break;

    case ValueRole:
        valueObject->setValue(convertToJsonValue(valueObject->typeCode(),value));
        break;

    case TypeCodeRole:
        valueObject->setTypeCode(uint(value.toInt()));
        break;

    case IsEditableRole:
        valueObject->setIsEditable(value.toBool());
        break;

    case IsNullRole:
        valueObject->setIsNull(value.toBool());
        break;

    case DescRole:
        valueObject->setDesc(value.toString());
        break;

    default:
        return false;
    }
    return true;
}

Qt::ItemFlags ValuesListModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> ValuesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::DeviceRole)] = "deviceRole";
    roles[static_cast<int>(Roles::NameRole)] = "nameRole";
    roles[static_cast<int>(Roles::TypeRole)] = "typeRole";
    roles[static_cast<int>(Roles::TypeCodeRole)] = "typeCodeRole";
    roles[static_cast<int>(Roles::ValueRole)] = "valueRole";
    roles[static_cast<int>(Roles::IsEditableRole)] = "isEditableRole";
    roles[static_cast<int>(Roles::IsNullRole)] = "isNullRole";
    roles[static_cast<int>(Roles::DescRole)] = "descRole";
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

QVariant ValuesListModel::convertFromJsonValue(uint type, QJsonValue jsonValue) const
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

QJsonValue ValuesListModel::convertToJsonValue(uint type, QVariant qvar) const
{
    switch (type) {
    case ValueObject::ValueType::IpStringType:
    case ValueObject::ValueType::DomenType:
    case ValueObject::ValueType::GnssStringType:
        return QJsonValue(qvar.toString());
    case ValueObject::ValueType::IpDigitType:
    case ValueObject::ValueType::IntType:
        return QJsonValue(qvar.toInt());
    case ValueObject::ValueType::FloatType:
        return QJsonValue(qvar.toDouble());
    case ValueObject::ValueType::BooleanType:
        return QJsonValue(qvar.toBool());
    case ValueObject::ValueType::ArrayType:
        return QJsonArray(QJsonDocument::fromJson(
                              qvar.toByteArray()).array());
    case ValueObject::ValueType::GnssDigitType:
    case ValueObject::ValueType::EnumType:
    case ValueObject::ValueType::NullType:
        return QJsonObject(QJsonDocument::fromJson(
                               qvar.toByteArray()).object());
    }
}

