#include "controlpanel.h"
#include "valueslistmodel.h"
#include "valuemaps.h"

#include <QCoreApplication>
#include "QQmlEngine"
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

ControlPanel::ControlPanel(QObject *parent)
    : QObject(parent)
    , _valuesListModel{ new ValuesListModel(this) }
{
    openJsonFile();

    connect(this, &ControlPanel::shutdownNow,
            this, &ControlPanel::shutdown, Qt::QueuedConnection);
}

void ControlPanel::saveToJsonFile(QString newJsonPath)
{
    qDebug() << "save to" << newJsonPath;
}

void ControlPanel::openJsonFile(QString jsonPath)
{
    qDebug() << "open" << jsonPath;
    QFile file(jsonPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        qDebug() << jsonError.errorString();
    }
    file.close();
    parseJson(jsonDoc.object());

}
void ControlPanel::parseJson(QJsonObject jsonObject)
{
    for(QString devName : jsonObject.keys()){
        if(!devName.contains("_enum")){
            QJsonObject devObject = jsonObject.value(devName).toObject();
            for(QString valName : devObject.keys()){
                QJsonObject valJsonObject = devObject.value(valName).toObject();
//                if(!valJsonObject.value("type").toString().contains("_enum"))
                {
                    ValueObject* newValue =
                            new ValueObject(
                                devName,
                                valName,
                                valueTypesMap.value(valJsonObject.value("type").toString()),
                                valJsonObject.value("value"),
                                this);
                    _valuesListModel->addValueObject(newValue);
                }
            }
        }
    }
    qDebug() << _valuesListModel->rowCount(QModelIndex());
}


void ControlPanel::registerQmlTypes() {
    static bool registered = false;
    if (!registered) {
        qmlRegisterUncreatableType<ValueObject>(
                    "ValueObjectsModule",
                    1, 0,
                    "ValueObject", "NOPE"
                    );
        qRegisterMetaType<ValueObject::ValueType>("ValueType");
        registered = true;
    }
}

//===============================================================================

void ControlPanel::turnOff() {
    int exitCode = 201; //Shutdown computer
    //TODO ControlPanel: Add more exit codes
    emit shutdownNow(exitCode);
}
void ControlPanel::shutdown(int returnCode) {

    qDebug() << "shutdown";

    QString command("kill ");
    command.append(QString::number(QCoreApplication::applicationPid()));
    system(qPrintable(command));
    QCoreApplication::exit(returnCode);
}
