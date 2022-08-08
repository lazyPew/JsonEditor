#include "controlpanel.h"
#include "valueslistmodel.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

ControlPanel::ControlPanel(QObject *parent)
    : QObject(parent)
    , _valuesListModel{ new ValuesListModel(this) }
{
    openJsonFile(":/testJson");
    connect(this, &ControlPanel::shutdownNow,
            this, &ControlPanel::shutdown, Qt::QueuedConnection);
}

void ControlPanel::saveToJsonFile()
{
    qDebug() << "save";
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

    QJsonObject objFromDoc = jsonDoc.object();

    //TODO move to jsonParser
    for(QString devName : objFromDoc.keys()){
        if(!devName.contains("_enum")){
            for(QString valName : objFromDoc.value(devName).toObject().keys()){
                ValueObject* newValue = new ValueObject(devName,valName,this);
                _valuesListModel->addValueObject(newValue);
            }
//            objFromDoc.value()
        }
    }
    qDebug() << _valuesListModel->rowCount(QModelIndex());
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
