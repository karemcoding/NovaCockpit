#include "vehicledata.h"
#include <QDebug>

VehicleData::VehicleData(QObject *parent)
    : QObject{parent}, m_speed(0), m_rpm(0)
{
    initCanBus();
}

int VehicleData::speed() const
{
    return m_speed;
}

void VehicleData::setSpeed(int newSpeed)
{
    if (m_speed == newSpeed)
        return;
    m_speed = newSpeed;

    // DEBUG: Check the exact value before notifying QML
    //qDebug() << "[C++] Speed updated to:" << m_speed;

    emit speedChanged();
}

int VehicleData::rpm() const
{
    return m_rpm;
}

void VehicleData::setRpm(int newRpm)
{
    if (m_rpm == newRpm)
        return;
    m_rpm = newRpm;

    emit rpmChanged();
}

void VehicleData::initCanBus()
{
    // Create a CAN device using the 'socketcan' plugin on 'vcan0' interface
    QString errorString;
    m_canDevice = QCanBus::instance()->createDevice("socketcan", "vcan0", &errorString);

    if (!m_canDevice) {
        qDebug() << "[CAN] Error creating device:" << errorString;
        return;
    }

    // Connect the framesReceived signal to our processing slot
    connect(m_canDevice, &QCanBusDevice::framesReceived, this, &VehicleData::processReceivedFrames);

    // Connect to the bus
    if (!m_canDevice->connectDevice()) {
        qDebug() << "[CAN] Connection failed:" << m_canDevice->errorString();
    } else {
        qDebug() << "[CAN] Successfully connected to vcan0";
    }
}

void VehicleData::processReceivedFrames()
{
    if (!m_canDevice) return;

    // Read all available frames in the buffer
    while (m_canDevice->framesAvailable()) {
        QCanBusFrame frame = m_canDevice->readFrame();

        // Assuming Frame ID 0x123 contains our speed data in the first byte
        if (frame.frameId() == 0x123) {
            QByteArray payload = frame.payload();
            if (!payload.isEmpty()) {
                // Read the first byte and cast it to integer speed
                int realSpeed = static_cast<int>(payload.at(0));
                setSpeed(realSpeed);
            }
        }
        else if (frame.frameId() == 0x124) {
            QByteArray payload = frame.payload();
            // RPM requires at least 2 bytes (e.g., max 8000 RPM)
            if (payload.size() >= 2) {
                // Combine byte 0 (High) and byte 1 (Low) using bitwise shift
                int realRpm = (static_cast<unsigned char>(payload.at(0)) << 8) |
                              static_cast<unsigned char>(payload.at(1));
                setRpm(realRpm);
            }
        }
    }
}
