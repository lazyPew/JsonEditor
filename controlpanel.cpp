#include "controlpanel.h"
#include "valueslistmodel.h"

#include <QCoreApplication>
#include "QQmlEngine"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

ControlPanel::ControlPanel(QObject *parent)
    : QObject(parent)
    , _valuesListModel{ new ValuesListModel(this) }
{
    openJsonFile();
    registerQmlTypes();
    connect(this, &ControlPanel::shutdownNow,
            this, &ControlPanel::shutdown, Qt::QueuedConnection);
}

void ControlPanel::addDevice(QString newDevice)
{
    _listOfDevices.append(newDevice);
    emit listOfDevicesChanged(_listOfDevices);
}
void ControlPanel::removeDevice(int index)
{
    _listOfDevices.removeAt(index);
    emit listOfDevicesChanged(_listOfDevices);
}

void ControlPanel::addEmptyValueObject()
{
    ValueObject* newValue = new ValueObject(
                *listOfDevices().begin(),
                "",
                ValueObject::ValueType::NullType,
                this,
                QJsonValue::Null
                );
    _valuesListModel->addValueObject(newValue);
}

void ControlPanel::removeValueObject(int index)
{
    _valuesListModel->valueObjectRemoving(index);
}

void ControlPanel::addCustomEnum()
{

}

void ControlPanel::updateCustomEnum(QString enumName, QVariantList list)
{
    _customEnumsMap[enumName] = list;
}

void ControlPanel::saveToJsonFile(QString newJsonPath)
{
    if (newJsonPath.isEmpty())
         newJsonPath = (QCoreApplication::applicationDirPath()).append("/" + QDateTime::currentDateTime().toString("MMdd_HHmmss") + ".json");
    qDebug() << "save to" << newJsonPath;
    QJsonObject objForJsonDoc = _valuesListModel->createJson(_listOfDevices);
    enumsToJson(objForJsonDoc);

    QJsonDocument docJson(objForJsonDoc);
    QFile file(newJsonPath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << docJson.toJson() << "\n";
    file.close();
}


void ControlPanel::enumsToJson(QJsonObject& objForJsonDoc)
{
    for(QString key : _customEnumsMap.keys()){
        QJsonObject enumJson;
        enumJson.insert("type", "enum");
        enumJson.insert("value",QJsonArray::fromVariantList(_customEnumsMap.value(key)));
        objForJsonDoc.insert(key,enumJson);
    }
}

void ControlPanel::openJsonFile(QString jsonPath)
{
    _valuesListModel->clearList();

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
        QJsonObject devObject = jsonObject.value(devName).toObject();
        if(devName.contains("_enum")){
            _customEnumsMap.insert(devName,devObject.value("value").toArray().toVariantList());
        }
        else{
            _listOfDevices.append(devName);
            for(QString valName : devObject.keys()){
                QJsonObject valJsonObject = devObject.value(valName).toObject();
                ValueObject* newValue = new ValueObject(
                            devName,
                            valName,
                            (checkType(valJsonObject.value("type").toString())
                             ? valueTypesMap.key(valJsonObject.value("type").toString())
                             : ValueObject::ValueType::EnumType),
                            this,
                            valJsonObject.value("value")
                            );
                newValue->setType(valJsonObject.value("type").toString());

                qDebug() << newValue->type();

                if(valJsonObject.value("isEditable") != QJsonValue::Undefined)
                    newValue->setIsEditable(valJsonObject.value("isEditable").toBool());

                if(valJsonObject.value("isNull") != QJsonValue::Undefined)
                    newValue->setIsNull(valJsonObject.value("isNull").toBool());

                if(valJsonObject.value("default") != QJsonValue::Undefined)
                    newValue->setDefaultValue(valJsonObject.value("default"));

                if(valJsonObject.value("desc") != QJsonValue::Undefined)
                    newValue->setDesc(valJsonObject.value("desc").toString());

                _valuesListModel->addValueObject(newValue);
            }
        }
    }
    qDebug() << _valuesListModel->rowCount(QModelIndex());
//    qDebug() << valuesListOfEnum(*listOfEnums().begin());
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
