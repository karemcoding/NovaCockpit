#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

class VehicleData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(VehicleData::GearShift currentGear READ currentGear WRITE setCurrentGear NOTIFY currentGearChanged)

public:
    explicit VehicleData(QObject *parent = nullptr);
    enum GearShift {
        Park = 0,
        Reverse = 1,
        Neutral = 2,
        Drive = 3
    };
    Q_ENUM(GearShift)

    int speed() const;
    void setSpeed(int newSpeed);
    int rpm() const;
    void setRpm(int newRpm);
    GearShift currentGear() const;
    void setCurrentGear(GearShift gear);

signals:
    void speedChanged();
    void rpmChanged();
    void currentGearChanged();

private:
    int m_speed;
    int m_rpm;
    GearShift m_currentGear;

    QCanBusDevice *m_canDevice; // Pointer to handle CAN connection

    // Setup connection to the virtual CAN bus
    void initCanBus();

    // Slot to handle incoming CAN frames
    void processReceivedFrames();
};

#endif // VEHICLEDATA_H
