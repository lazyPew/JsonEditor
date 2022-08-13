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
               CONSTANT)
public:
    ControlPanel(QObject *parent = nullptr);

public slots:
    ValuesListModel* valuesListModel() const{ return _valuesListModel; }
    QStringList listOfTypes() const         { return getStringTypes(); }
    QStringList listOfDevices() const       { return _listOfDevices; }

    void saveToJsonFile(QString newJsonPath);
    void openJsonFile(QString jsonPath = ":/test2");

    void turnOff();

signals:
    void shutdownNow(int returnCode);

private:
    void shutdown(int returnCode);
    void parseJson(QJsonObject jsonObject);
    void registerQmlTypes();

private:
    ValuesListModel* _valuesListModel;

    QStringList _listOfDevices;
};

#endif // CONTROLPANEL_H
