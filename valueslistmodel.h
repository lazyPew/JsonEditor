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
        IpStringType = 0,
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
                uint typeCode,
                QJsonValue value,
                QObject *parent = nullptr
            );
public slots:
    QString device() const      { return _device; }
    QString name() const        { return _name; }
    uint typeCode() const       { return _typeCode; }
    QJsonValue value() const    { return _value; }
    bool isEditable() const     { return _isEditable; }
    bool isNull() const         { return _isNull; }

    void setDevice(QString newValue);
    void setName(QString newValue);
    void setTypeCode(uint newValue);
    void setValue(QJsonValue newValue);

    void setIsEditable(bool newValue);
    void setIsNull(bool newValue);
    void setDescription(QString newValue);
    void setDefault(QJsonValue newValue);

    QString typeString() const;

signals:
    void deviceChanged(QString);
    void nameChanged(QString);
    void typeChanged(uint);
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
    uint _typeCode;
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
        TypeCodeRole,
        ValueRole,
        IsEditableRole,
        IsNullRole
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

private:
    QVariant convertJsonValue(uint, QJsonValue) const;
private:
    QList<ValueObject*> _valueObjectsList;
};

#endif // DEVICELISTMODEL_H
