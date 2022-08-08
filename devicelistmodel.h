#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>

class DeviceListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DeviceListModel(QObject *parent = nullptr);
};

#endif // DEVICELISTMODEL_H
