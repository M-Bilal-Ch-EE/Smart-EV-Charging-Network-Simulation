#include "ChargingDock.h"
#include <iostream>

ChargingDock::ChargingDock(const std::string& id, float speed)
    : dockId(id), chargingSpeedKWh(speed), isOccupied(false),
    currentEV(nullptr), currentBooking(nullptr) {
}

std::string ChargingDock::getDockId() const {
    return dockId;
}

float ChargingDock::getChargingSpeed() const {
    return chargingSpeedKWh;
}

bool ChargingDock::isAvailable() const {
    return !isOccupied;
}

bool ChargingDock::startCharging(EV* ev, Booking* booking) {
    if (isOccupied) {
        std::cout << "Dock " << dockId << " is already occupied.\n";
        return false;
    }

    currentEV = ev;
    currentBooking = booking;
    isOccupied = true;

    std::cout << "Charging started for EV " << ev->getEVId()
        << " on dock " << dockId << " at "
        << chargingSpeedKWh << " kWh.\n";

    return true;
}

void ChargingDock::stopCharging() {
    if (!isOccupied) {
        std::cout << "Dock " << dockId << " is not in use.\n";
        return;
    }

    std::cout << "Charging completed for EV " << currentEV->getEVId()
        << " on dock " << dockId << ".\n";

    currentEV = nullptr;
    currentBooking = nullptr;
    isOccupied = false;
}

void ChargingDock::displayStatus() const {
    std::cout << "Dock ID: " << dockId
        << ", Speed: " << chargingSpeedKWh << " kWh"
        << ", Status: " << (isOccupied ? "Occupied" : "Available") << "\n";
}
