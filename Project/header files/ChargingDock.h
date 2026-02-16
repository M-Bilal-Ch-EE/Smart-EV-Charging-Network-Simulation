#ifndef CHARGING_DOCK_H
#define CHARGING_DOCK_H

#include <string>
#include "EV.h"
#include "Booking.h"
class ChargingDock 
{
private:
    std::string dockId;
    float chargingSpeedKWh;
    bool isOccupied;
    EV* currentEV;
    Booking* currentBooking;
public:
    ChargingDock(const std::string& id, float speed);
    std::string getDockId() const;
    float getChargingSpeed() const;
    bool isAvailable() const;
    bool startCharging(EV* ev, Booking* booking);
    void stopCharging();
    void displayStatus() const;
};
#endif 
