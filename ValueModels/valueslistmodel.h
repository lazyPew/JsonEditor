#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QJsonValue>
#include <QJsonObject>

class ValueObject;

class ValuesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ValuesListModel(QObject *parent = nullptr);

    enum Roles{
        DeviceRole = Qt::UserRole + 1,
        NameRole,
        TypeRole,
        TypeCodeRole,
        ValueRole,
        IsEditableRole,
        IsNullRole,
        DefaultValueRole,
        DescRole,

        AdditionalFieldsRole,
        MaxRole,
        MinRole,
        ExceptRole,
        RegexRole,
        UnitsRole
    };
    void addValueObject(ValueObject*);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index,
                         const QVariant &value,
                         int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    QList<ValueObject*> valueObjectsList() const;
    ValueObject* valueObjectAt(int index) const;
    void valueObjectRemoving(int index);

    void clearList();
    QJsonObject createJson(QStringList);

private:
    QVariant convertFromJsonValue(uint, QJsonValue) const;
    QJsonValue convertToJsonValue(uint, QVariant) const;

    QJsonObject createJsonForDevice(QString);

private:
    QList<ValueObject*> _valueObjectsList;

};

#endif // DEVICELISTMODEL_H
