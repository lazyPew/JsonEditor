#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>

class DeviceListModel;

class ControlPanel : public QObject
{
    Q_OBJECT

public:
    ControlPanel(QObject *parent = nullptr);

public slots:
    void saveToJsonFile();
    void openJsonFile(QString jsonPath);

    void turnOff();

signals:
    void shutdownNow(int returnCode);

private:
    void shutdown(int returnCode);

private:
    DeviceListModel* _deviceListModel;
};

#endif // CONTROLPANEL_H
