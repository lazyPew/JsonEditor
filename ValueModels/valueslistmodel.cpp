#include "valueslistmodel.h"
#include "valueobject.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

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
        return _valueObjectsList.at(row)->type();
    case static_cast<int>(Roles::TypeCodeRole):
        return _valueObjectsList.at(row)->typeCode();
    case static_cast<int>(Roles::ValueRole):
        return convertFromJsonValue(_valueObjectsList.at(row)->typeCode(),
                                _valueObjectsList.at(row)->value());
    case static_cast<int>(Roles::IsEditableRole):
        return _valueObjectsList.at(row)->isEditable();
    case static_cast<int>(Roles::IsNullRole):
        return _valueObjectsList.at(row)->isNull();
    case static_cast<int>(Roles::DefaultValueRole):
        return convertFromJsonValue(_valueObjectsList.at(row)->typeCode(),
                                _valueObjectsList.at(row)->defaultValue());
    case static_cast<int>(Roles::DescRole):
        return _valueObjectsList.at(row)->desc();

    case static_cast<int>(Roles::MaxRole):
        return _valueObjectsList.at(row)->maxValue();
    case static_cast<int>(Roles::MinRole):
        return _valueObjectsList.at(row)->minValue();
    case static_cast<int>(Roles::ExceptRole):
        return _valueObjectsList.at(row)->except();
    case static_cast<int>(Roles::RegexRole):
        return _valueObjectsList.at(row)->regex();
    case static_cast<int>(Roles::UnitsRole):
        return _valueObjectsList.at(row)->units()
                ;
    default:
        return QVariant();
    }
}

bool ValuesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    ValueObject* valueObject = _valueObjectsList[index.row()];

    switch(role){

    case DeviceRole:
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

    case TypeRole:
        valueObject->setType(value.toString());
        break;

    case IsEditableRole:
        valueObject->setIsEditable(value.toBool());
        break;

    case IsNullRole:
        valueObject->setIsNull(value.toBool());
        break;

    case DefaultValueRole:
        valueObject->setDefaultValue(convertToJsonValue(valueObject->typeCode(),value));
        break;

    case DescRole:
        valueObject->setDesc(value.toString());
        break;

        //-----------------//

    case MaxRole:
        if(value.toString() == "")
            valueObject->setMaxValue(QJsonValue::Null);
        else valueObject->setMaxValue(convertToJsonValue(valueObject->typeCode(),value));
        break;

    case MinRole:
        if(value.toString() == "")
            valueObject->setMinValue(QJsonValue::Null);
        else valueObject->setMinValue(convertToJsonValue(valueObject->typeCode(),value));
        break;

    case ExceptRole:
        valueObject->setExcept(value);
        break;

    case RegexRole:
        valueObject->setRegex(value.toString().replace(QRegExp("\""), ""));
        break;

    case UnitsRole:
        valueObject->setUnits(value.toString().replace(QRegExp("\""), ""));
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
    roles[static_cast<int>(Roles::DefaultValueRole)] = "defaultValueRole";
    roles[static_cast<int>(Roles::MaxRole)] = "maxRole";
    roles[static_cast<int>(Roles::MinRole)] = "minRole";
    roles[static_cast<int>(Roles::ExceptRole)] = "exceptRole";
    roles[static_cast<int>(Roles::RegexRole)] = "regexRole";
    roles[static_cast<int>(Roles::UnitsRole)] = "unitsRole";
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

void ValuesListModel::valueObjectRemoving(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    _valueObjectsList.removeAt(index);
    endRemoveRows();
}

void ValuesListModel::clearList()
{
    int endIndex = _valueObjectsList.size() - 1;
    beginRemoveRows(QModelIndex(),0, endIndex);
    _valueObjectsList.clear();
    endRemoveRows();
}

QJsonObject ValuesListModel::createJson(QStringList listOfDevices)
{
    QJsonObject allValuesJsonObject;
    for(QString deviceStr: listOfDevices){
        QJsonObject deviceJsonObject = createJsonForDevice(deviceStr);
        if(!deviceJsonObject.isEmpty())
            allValuesJsonObject.insert(deviceStr, deviceJsonObject);
    }
    return allValuesJsonObject;
}


QJsonObject ValuesListModel::createJsonForDevice(QString deviceStr)
{
    QJsonObject deviceJsonObject;
    for(ValueObject* valueObject : _valueObjectsList){
        if(valueObject->device() == deviceStr){
            deviceJsonObject.insert(valueObject->name(), valueObject->getJson());
        }
    }
    return deviceJsonObject;
}


QVariant ValuesListModel::convertFromJsonValue(uint type, QJsonValue jsonValue) const
{
    switch (type) {
    case ValueObject::ValueType::IpStringType:
    case ValueObject::ValueType::DomenType:
    case ValueObject::ValueType::GnssStringType:
        return jsonValue.toString();
    case ValueObject::ValueType::IntType:
        return jsonValue.toInt();
    case ValueObject::ValueType::IpDigitType:
        return jsonValue.toVariant().toUInt();
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
        return QJsonValue(qvar.toString().replace(QRegExp("\""), ""));
    case ValueObject::ValueType::IntType:
        return QJsonValue(qvar.toInt());
    case ValueObject::ValueType::IpDigitType:
    case ValueObject::ValueType::FloatType:
        return QJsonValue(qvar.toDouble());
    case ValueObject::ValueType::BooleanType:
        return QJsonValue(qvar.toBool());
    case ValueObject::ValueType::ArrayType:
        return QJsonArray(QJsonDocument::fromJson(
                              qvar.toByteArray()).array());
    case ValueObject::ValueType::GnssDigitType:
    case ValueObject::ValueType::EnumType:
        return QJsonValue::fromVariant(qvar);
    case ValueObject::ValueType::NullType:
        return QJsonValue::Null;
    default:
        return QJsonValue();
    }
}

