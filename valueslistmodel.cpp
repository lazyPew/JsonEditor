#include "valueslistmodel.h"

ValueObject::ValueObject(
        QString device,
        QString name,
        QObject *parent)
    : QObject(parent)
    , _device(device)
    , _name(name)
{}

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
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ValuesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::DeviceRole)] = "deviceRole";
    roles[static_cast<int>(Roles::NameRole)] = "nameRole";
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

