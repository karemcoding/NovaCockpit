#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "vehicledata.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    VehicleData vehicle;
    vehicle.setSpeed(80);

    QQmlApplicationEngine engine;
    qRegisterMetaType<VehicleData::GearShift>("VehicleData::GearShift");
    engine.rootContext()->setContextProperty("vehicleProvider", &vehicle);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("NovaCockpit", "Main");

    return app.exec();
}
