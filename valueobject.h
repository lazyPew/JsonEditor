#ifndef VALUEOBJECT_H
#define VALUEOBJECT_H

#include <QObject>
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

#endif // VALUEOBJECT_H
