#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>
#include "ValueModels/valuemaps.h"

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

    Q_PROPERTY(QString fileName
               READ fileName
               NOTIFY fileNameChanged)

public:
    ControlPanel(QStringList args, QObject *parent = nullptr);

public slots:
    ValuesListModel* valuesListModel() const                { return _valuesListModel; }
    QStringList listOfTypes() const                         { return getStringTypes(); }
    QStringList listOfDevices() const                       { return _listOfDevices; }
    QStringList listOfEnums() const                         { return _customEnumsMap.keys(); }
    QVariantList valuesListOfEnum(QString enumString) const { return _customEnumsMap.value(enumString); }

    QString fileName() const                                { return _fileName; }

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

    void openingFailed(QString errorExplanation);
    void fileNameChanged(QString fileName);

    void shutdownNow(int returnCode);

private:
    void shutdown(int returnCode);
    void registerQmlTypes();

    QString checkArguments(QStringList args);

    void parseJson(QJsonObject jsonObject);
    void parseJsonFields(ValueObject* newValue, QJsonObject& valJsonObject);
    void enumsToJson(QJsonObject&);

private:
    ValuesListModel* _valuesListModel;

    QString _fileName;

    QStringList _listOfDevices;
    QMap<QString, QVariantList> _customEnumsMap;

};

#endif // CONTROLPANEL_H
