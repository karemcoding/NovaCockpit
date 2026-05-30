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

public:
    explicit VehicleData(QObject *parent = nullptr);

    int speed() const;
    void setSpeed(int newSpeed);
    int rpm() const;
    void setRpm(int newRpm);

signals:
    void speedChanged();
    void rpmChanged();

private:
    int m_speed;
    int m_rpm;

    QCanBusDevice *m_canDevice; // Pointer to handle CAN connection

    // Setup connection to the virtual CAN bus
    void initCanBus();

    // Slot to handle incoming CAN frames
    void processReceivedFrames();
};

#endif // VEHICLEDATA_H
