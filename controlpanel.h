#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>
#include "valuemaps.h"

class ValuesListModel;

class ControlPanel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ValuesListModel* valuesListModel
               READ valuesListModel
               CONSTANT)
    Q_PROPERTY(QStringList listOfDevices
               READ listOfDevices
               NOTIFY listOfDevicesChanged)

public:
    ControlPanel(QObject *parent = nullptr);

public slots:
    ValuesListModel* valuesListModel() const                { return _valuesListModel; }
    QStringList listOfTypes() const                         { return getStringTypes(); }
    QStringList listOfDevices() const                       { return _listOfDevices; }
    QStringList listOfEnums() const                         { return _customEnumsMap.keys(); }
    QVariantList valuesListOfEnum(QString enumString) const { return _customEnumsMap.value(enumString); }

    void addDevice(QString newDevice);
    void removeDevice(int index);

    void addEmptyValueObject();
    void removeValueObject(int index);

    void addCustomEnum();
    void updateCustomEnum(QString enumName, QVariantList list);

    void saveToJsonFile(QString newJsonPath);
    void openJsonFile(QString jsonPath = ":/test2");

    void turnOff();

signals:
    void listOfDevicesChanged(QStringList);
    void shutdownNow(int returnCode);

private:
    void shutdown(int returnCode);
    void parseJson(QJsonObject jsonObject);
    void registerQmlTypes();
    void enumsToJson(QJsonObject&);

private:
    ValuesListModel* _valuesListModel;

    QStringList _listOfDevices;
    QMap<QString, QVariantList> _customEnumsMap;

};

#endif // CONTROLPANEL_H
