#include "controlpanel.h"
#include "ValueModels/valueslistmodel.h"

#include <QCoreApplication>
#include "QQmlEngine"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

ControlPanel::ControlPanel(QStringList args, QObject *parent)
    : QObject(parent)
    , _valuesListModel{ new ValuesListModel(this) }
{
    Q_UNUSED(parent);
    QString jsonPath = checkArguments(args);

    openJsonFile(jsonPath);
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
    for(int i = 0; i < _valuesListModel->valueObjectsList().size(); ++i){
        if(valuesListModel()->valueObjectAt(i)->device() == _listOfDevices.at(index))
            removeValueObject(i);
    }
    _listOfDevices.removeAt(index);
    emit listOfDevicesChanged(_listOfDevices);
}


void ControlPanel::addEmptyValueObject(){
    ValueObject* newValue = new ValueObject(
                *listOfDevices().begin(),
                "",
                ValueObject::ValueType::NullType,
                this,
                QJsonValue::Null
                );
    _valuesListModel->addValueObject(newValue);
}

void ControlPanel::removeValueObject(int index){
    _valuesListModel->valueObjectRemoving(index);
}

bool ControlPanel::addCustomEnum(QString enumName){
    if(_customEnumsMap.keys().contains(enumName))
        return false;
    _customEnumsMap[enumName] = QVariantList();
    emit listOfEnumsChanged(_customEnumsMap.keys());
    return true;
}

void ControlPanel::updateCustomEnum(QString enumName, QVariantList list){
    _customEnumsMap[enumName] = list;
}

void ControlPanel::removeCustomEnum(QString enumName){
    for(int i = 0; i < _valuesListModel->valueObjectsList().size(); ++i){
        if(valuesListModel()->valueObjectAt(i)->type() == enumName)
            removeValueObject(i);
    }
    _customEnumsMap.remove(enumName);
    emit listOfEnumsChanged(_customEnumsMap.keys());
}

void ControlPanel::saveToJsonFile(QString newJsonPath){
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

void ControlPanel::enumsToJson(QJsonObject& objForJsonDoc){
    for(QString key : _customEnumsMap.keys()){
        QJsonObject enumJson;
        enumJson.insert("type", "enum");
        enumJson.insert("value",QJsonArray::fromVariantList(_customEnumsMap.value(key)));
        objForJsonDoc.insert(key,enumJson);
    }
}

void ControlPanel::openJsonFile(QString jsonPath){
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

void ControlPanel::parseJson(QJsonObject jsonObject){
    for(QString devName : jsonObject.keys()){
        QJsonObject devObject = jsonObject.value(devName).toObject();
        if(devName.contains("_enum")){
            _customEnumsMap.insert(devName,devObject.value("value").toArray().toVariantList());
            emit listOfEnumsChanged(_customEnumsMap.keys());

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

                parseJsonFields(newValue, valJsonObject);
            }
        }
    }
}

void ControlPanel::parseJsonFields(ValueObject *newValue, QJsonObject &valJsonObject)
{

    if(valJsonObject.value("isEditable") != QJsonValue::Undefined)
        newValue->setIsEditable(valJsonObject.value("isEditable").toBool());

    if(valJsonObject.value("isNull") != QJsonValue::Undefined)
        newValue->setIsNull(valJsonObject.value("isNull").toBool());

    if(valJsonObject.value("default") != QJsonValue::Undefined)
        newValue->setDefaultValue(valJsonObject.value("default"));

    if(valJsonObject.value("desc") != QJsonValue::Undefined)
        newValue->setDesc(valJsonObject.value("desc").toString());

    _valuesListModel->addValueObject(newValue);

    if(extendableTypes.contains(newValue->typeCode())){

        if(valJsonObject.value("max") != QJsonValue::Undefined)
            newValue->setMaxValue(valJsonObject.value("max"));

        if(valJsonObject.value("min") != QJsonValue::Undefined)
            newValue->setMinValue(valJsonObject.value("min"));

        if(valJsonObject.value("except") != QJsonValue::Undefined){
            QJsonDocument doc;
            doc.setArray(valJsonObject.value("except").toArray());
            newValue->setExcept(doc.toJson());
        };

        if(valJsonObject.value("units") != QJsonValue::Undefined)
            newValue->setUnits(valJsonObject.value("units").toString());

        if(valJsonObject.value("regex") != QJsonValue::Undefined)
            newValue->setRegex(valJsonObject.value("regex").toString());
    }
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

QString ControlPanel::checkArguments(QStringList args)
{
    QString jsonPath;
    if(args.size() <= 1){
        qDebug() << "No additional arguments have been given. Using test JSON file.";
        jsonPath = ":/test2";
    }
    else{
        qDebug() << "Argument for JSON file have been given, checking file " + args.at(1) + "...";
        if(QFile(args.at(1)).exists())
            jsonPath = args.at(1);
        else{
            qDebug() << "No such file. Using test JSON file.";
            jsonPath = ":/test2";
        }
    }
    return jsonPath;
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
