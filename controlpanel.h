#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>

class ValuesListModel;

class ControlPanel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ValuesListModel* valuesListModel
               READ valuesListModel
               CONSTANT)
public:
    ControlPanel(QObject *parent = nullptr);

public slots:
    ValuesListModel* valuesListModel() const { return _valuesListModel; }

    void saveToJsonFile();
    void openJsonFile(QString jsonPath);

    void turnOff();

signals:
    void shutdownNow(int returnCode);

private:
    void shutdown(int returnCode);

private:
    ValuesListModel* _valuesListModel;
};

#endif // CONTROLPANEL_H
