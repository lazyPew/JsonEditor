#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QJsonValue>

class ValueObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name
               READ name
               WRITE setName
               NOTIFY nameChanged)
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
    Q_ENUM(ValueType)

    ValueObject(QString device,
                QString name,
                ValueType type,
                QJsonValue value,
                QObject *parent = nullptr);

    QString device() const      { return _device; }
    QString name() const        { return _name; }
    ValueType type() const      { return _type; }
    QJsonValue value() const    { return _value; }
    bool isEditable() const     { return _isEditable; }
    bool isNull() const         { return _isNull; }

    void setDevice(QString newValue);
    void setName(QString newValue);
    void setType(QString newValue);
    void setValue(QJsonValue newValue);

    void setIsEditable(bool newValue);
    void setIsNull(bool newValue);
    void setDescription(QString newValue);
    void setDefault(QJsonValue newValue);

signals:
    void deviceChanged(QString);
    void nameChanged(QString);
    void typeChanged(QString);
    void valueChanged(QJsonValue);
    void isEditableChanged(bool);
    void isNullChanged(bool);
    void descriptionChanged(QString);
    void defaultChanged(QJsonValue);

private:
    void valueConversion(QJsonValue);

private:
    QString _device;
    QString _name;
    ValueType _type;
    QJsonValue _value;
    bool _isEditable = true;
    bool _isNull = true;
    QString _description = "";
    QJsonValue _dafault = QJsonValue::Null;
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
    QVariant convertJsonValue(ValueObject::ValueType, QJsonValue) const;
private:
    QList<ValueObject*> _valueObjectsList;
};

#endif // DEVICELISTMODEL_H
