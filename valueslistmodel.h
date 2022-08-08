#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>

class ValueObject : public QObject
{
    Q_OBJECT

public:
    ValueObject(QString device,
                QString name,
                QObject *parent = nullptr);

    QString device() const  { return _device; }
    QString name() const    { return _name; }
//    QString type() const    { return _type; }

private:
    QString _device;
    QString _name;
//    QString _type;
};

class ValuesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ValuesListModel(QObject *parent = nullptr);

    enum Roles{
        DeviceRole = Qt::UserRole + 1,
        NameRole
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
