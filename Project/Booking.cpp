#include "Booking.h"
#include <iostream>
#include <iomanip>

Booking::Booking(const std::string& id, EV* ev, User* user,
    const std::chrono::system_clock::time_point& start,
    const std::chrono::system_clock::time_point& end,
    int priority)
    : bookingId(id), ev(ev), user(user), startTime(start), endTime(end),
    status(BookingStatus::Scheduled), priorityLevel(priority),
    estimatedEnergyKWh(0.0f), actualEnergyDelivered(0.0f),
    penaltyApplied(false), penaltyAmount(0.0f)
{
    float hours = std::chrono::duration<float>(end - start).count();
    estimatedEnergyKWh = hours * 7.0f;  
}

std::string Booking::getBookingId() const { return bookingId; }
EV* Booking::getEV() const { return ev; }
User* Booking::getUser() const { return user; }
BookingStatus Booking::getStatus() const { return status; }
float Booking::getEstimatedEnergy() const { return estimatedEnergyKWh; }

void Booking::markActive() {
    status = BookingStatus::Active;
}

void Booking::markCompleted(float actualEnergy) {
    status = BookingStatus::Completed;
    actualEnergyDelivered = actualEnergy;
}

void Booking::markCancelled(bool late) {
    status = BookingStatus::Cancelled;
    if (late) applyPenalty(5.0f);  
}

void Booking::markNoShow() {
    status = BookingStatus::NoShow;
    applyPenalty(10.0f); 
}

void Booking::checkOverstay(const std::chrono::system_clock::time_point& actualEnd) {
    if (actualEnd > endTime) {
        status = BookingStatus::Overstayed;
        applyPenalty(3.0f);
    }
}

void Booking::applyPenalty(float amount) {
    penaltyApplied = true;
    penaltyAmount += amount;
}

float Booking::getPenaltyAmount() const {
    return penaltyAmount;
}

void Booking::displaySummary() const {
    std::cout << "Booking ID: " << bookingId
        << ", User: " << user->getName()
        << ", EV: " << ev->getEVId()
        << ", Status: ";

    switch (status) {
    case BookingStatus::Scheduled: std::cout << "Scheduled"; break;
    case BookingStatus::Active: std::cout << "Active"; break;
    case BookingStatus::Completed: std::cout << "Completed"; break;
    case BookingStatus::Cancelled: std::cout << "Cancelled"; break;
    case BookingStatus::NoShow: std::cout << "No Show"; break;
    case BookingStatus::Overstayed: std::cout << "Overstayed"; break;
    }

    std::cout << ", Energy: " << std::fixed << std::setprecision(1)
        << actualEnergyDelivered << " kWh"
        << (penaltyApplied ? ", Penalty: $" + std::to_string(penaltyAmount) : "")
        << "\n";
}

