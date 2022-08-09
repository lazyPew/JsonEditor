#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QJsonValue>

class ValueObject : public QObject
{
    Q_OBJECT


public:
    enum ValueType
    {
        IpStringType,
        IpDigitType,
        DomenType,
        EnumType,
        GnssStringType,
        GnssDigitType,
        IntType,
        FloatType,
        BooleanType,
        ArrayType,
        NullType
    };

    ValueObject(QString device,
                QString name,
                ValueType type,
                QJsonValue value,
                QObject *parent = nullptr);

    QString device() const      { return _device; }
    QString name() const        { return _name; }
//    bool isEditable() const     { return _isEditable; }
    ValueType type() const      { return _type; }
    QJsonValue value() const   { return _value; }

private:
    QString _device;
    QString _name;
//    bool _isEditable;
    ValueType _type;
    QJsonValue _value;
};

class ValuesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ValuesListModel(QObject *parent = nullptr);

    enum Roles{
        DeviceRole = Qt::UserRole + 1,
        NameRole,
        TypeRole,
        ValueRole
    };
    void addValueObject(ValueObject*);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    QList<ValueObject*> valueObjectsList() const;
    ValueObject* valueObjectAt(int index) const;

private:
    QList<ValueObject*> _valueObjectsList;
};

#endif // DEVICELISTMODEL_H
