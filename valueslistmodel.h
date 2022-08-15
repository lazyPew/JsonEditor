#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QJsonValue>
#include <QJsonObject>

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
                QObject *parent = nullptr,
                QJsonValue value = QJsonValue::Null,
                bool isEditable = true,
                bool isNull = true,
                QJsonValue defaultValue = QJsonValue::Null,
                QString desc = ""
            );
public slots:
    QString device() const              { return _device; }
    QString name() const                { return _name; }
    uint typeCode() const               { return _typeCode; }
    QString type() const                { return _type; }
    QJsonValue value() const            { return _value; }
    bool isEditable() const             { return _isEditable; }
    bool isNull() const                 { return _isNull; }
    QJsonValue defaultValue() const     { return _defaultValue; }
    QString desc() const                { return _desc; }

    void setDevice(QString newValue);
    void setName(QString newValue);
    void setTypeCode(uint newValue);
    void setType(QString newValue);
    void setValue(QJsonValue newValue);
    void setIsEditable(bool newValue);
    void setIsNull(bool newValue);
    void setDefaultValue(QJsonValue newValue);
    void setDesc(QString newValue);

    QJsonObject getJson();

signals:
    void deviceChanged(QString);
    void nameChanged(QString);
    void typeCodeChanged(uint);
    void typeChanged(QString);
    void valueChanged(QJsonValue);
    void isEditableChanged(bool);
    void isNullChanged(bool);
    void defaultValueChanged(QJsonValue);
    void descChanged(QString);

private:
    QString _device;
    QString _name;
    uint _typeCode;
    QString _type;
    QJsonValue _value;
    bool _isEditable = true;
    bool _isNull = true;
    QJsonValue _defaultValue = QJsonValue::Null;
    QString _desc = "";
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
        IsNullRole,
        DefaultValueRole,
        DescRole
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
