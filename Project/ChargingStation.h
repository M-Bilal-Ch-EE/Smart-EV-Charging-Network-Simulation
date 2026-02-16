#ifndef CHARGING_STATION_H
#define CHARGING_STATION_H

#include <string>
#include <vector>
#include <queue>
#include "ChargingDock.h"
#include "EV.h"
#include "Booking.h"
class ChargingStation 
{
private:
    std::string stationId;
    std::string location;
    float maxLoadCapacity;
    std::vector<ChargingDock*> docks;
    std::queue<Booking*> bookingQueue;
public:
    ChargingStation(const std::string& id, const std::string& loc, float maxLoad);
    void addDock(ChargingDock* dock);
    std::vector<ChargingDock*> getAvailableDocks() const;
    bool assignDock(EV* ev, Booking* booking);
    void addBookingToQueue(Booking* booking);
    void processQueue();
    float getTotalLoad() const;
    void displayStationStatus() const;
    std::string getStationId() const;
};
#endif