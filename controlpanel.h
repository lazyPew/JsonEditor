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

    Q_PROPERTY(QStringList listOfEnums
               READ listOfEnums
               NOTIFY listOfEnumsChanged)

public:
    ControlPanel(QStringList args, QObject *parent = nullptr);

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

    bool addCustomEnum(QString enumName);
    void updateCustomEnum(QString enumName, QVariantList list);
    void removeCustomEnum(QString enumName);

    void saveToJsonFile(QString newJsonPath);
    void openJsonFile(QString jsonPath);

    void turnOff();

signals:
    void listOfDevicesChanged(QStringList);
    void listOfEnumsChanged(QStringList);
    void shutdownNow(int returnCode);

private:
    void shutdown(int returnCode);
    void registerQmlTypes();

    QString checkArguments(QStringList args);

    void parseJson(QJsonObject jsonObject);
    void enumsToJson(QJsonObject&);

private:
    ValuesListModel* _valuesListModel;

    QStringList _listOfDevices;
    QMap<QString, QVariantList> _customEnumsMap;

};

#endif // CONTROLPANEL_H
