#include "ChargingStation.h"
#include <iostream>

ChargingStation::ChargingStation(const std::string& id, const std::string& loc, float maxLoad)
    : stationId(id), location(loc), maxLoadCapacity(maxLoad) {
}

void ChargingStation::addDock(ChargingDock* dock) {
    docks.push_back(dock);
}

std::vector<ChargingDock*> ChargingStation::getAvailableDocks() const {
    std::vector<ChargingDock*> available;
    for (auto& dock : docks) {
        if (dock->isAvailable()) {
            available.push_back(dock);
        }
    }
    return available;
}

bool ChargingStation::assignDock(EV* ev, Booking* booking) {
    for (auto& dock : docks) {
        if (dock->isAvailable()) {
            return dock->startCharging(ev, booking);
        }
    }
    std::cout << "No docks available. Adding booking to queue.\n";
    addBookingToQueue(booking);
    return false;
}

void ChargingStation::addBookingToQueue(Booking* booking) {
    bookingQueue.push(booking);
}

void ChargingStation::processQueue() {
    std::queue<Booking*> remainingQueue;

    while (!bookingQueue.empty()) {
        Booking* b = bookingQueue.front();
        bookingQueue.pop();

        if (!assignDock(b->getEV(), b)) {
            remainingQueue.push(b); 
        }
    }

    bookingQueue = std::move(remainingQueue);
}

float ChargingStation::getTotalLoad() const {
    float total = 0.0f;
    for (const auto& dock : docks) {
        if (!dock->isAvailable())
            total += dock->getChargingSpeed();
    }
    return total;
}

void ChargingStation::displayStationStatus() const {
    std::cout << "\nStation " << stationId << " at " << location << "\n";
    std::cout << "Total load: " << getTotalLoad() << " kW\n";
    for (const auto& dock : docks) {
        dock->displayStatus();
    }
    std::cout << "Queued bookings: " << bookingQueue.size() << "\n";
}

std::string ChargingStation::getStationId() const {
    return stationId;
}

