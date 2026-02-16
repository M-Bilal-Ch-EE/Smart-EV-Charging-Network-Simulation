#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <chrono>
#include "EV.h"
#include "User.h"
enum class BookingStatus 
{
    Scheduled,
    Active,
    Completed,
    Cancelled,
    NoShow,
    Overstayed
};
class Booking 
{
private:
    std::string bookingId;
    EV* ev;
    User* user;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    BookingStatus status;
    int priorityLevel; 
    float estimatedEnergyKWh;
    float actualEnergyDelivered;
    bool penaltyApplied;
    float penaltyAmount;

public:
    Booking(const std::string& id, EV* ev, User* user,
        const std::chrono::system_clock::time_point& start,
        const std::chrono::system_clock::time_point& end,
        int priority = 0);
    std::string getBookingId() const;
    EV* getEV() const;
    User* getUser() const;
    BookingStatus getStatus() const;
    float getEstimatedEnergy() const;
    void markActive();
    void markCompleted(float actualEnergy);
    void markCancelled(bool late);
    void markNoShow();
    void checkOverstay(const std::chrono::system_clock::time_point& actualEnd);
    void applyPenalty(float amount);
    float getPenaltyAmount() const;
    void displaySummary() const;
};
#endif

