#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controlpanel.h"
#include "valuemaps.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ControlPanel* panel = new ControlPanel(QCoreApplication::arguments());

    engine.rootContext()->setContextProperty("panel", panel);
    engine.rootContext()->setContextProperty("valueTypes", QVariant::fromValue(getStringTypes()));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
