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

QString ValueObject::typeString() const
{
    return valueTypesMap.value(_typeCode);
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
        return convertJsonValue(_valueObjectsList.at(row)->typeCode(),
                                _valueObjectsList.at(row)->value());
//        return _valueObjectsList.at(row)->value().toString();
    case static_cast<int>(Roles::IsEditableRole):
        return _valueObjectsList.at(row)->isEditable();
    case static_cast<int>(Roles::IsNullRole):
        return _valueObjectsList.at(row)->isNull();
    default:
        return QVariant();
    }
}

bool ValuesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ValueObject* valueObject = _valueObjectsList[index.row()];

    switch(role){
//    DeviceRole
//    NameRole,
//    TypeRole,
//    ValueRole,
//    IsEditableRole,
//    IsNullRole
    case NameRole:
//        qDebug() << "Set Position in DataModelList";
        valueObject->setName(value.toString());
        break;

    case TypeCodeRole:
//        qDebug() << "Set Position in DataModelList";
        valueObject->setTypeCode(uint(value.toInt()));
        break;

    case IsEditableRole:
        valueObject->setIsEditable(value.toBool());
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

QVariant ValuesListModel::convertJsonValue(uint type, QJsonValue jsonValue) const
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

