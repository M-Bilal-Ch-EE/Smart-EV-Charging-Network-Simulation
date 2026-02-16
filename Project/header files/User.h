#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
class EV;
class Booking;  
class User 
{
private:
    std::string userId;
    std::string name;
    std::string membershipLevel;
    std::vector<EV*> registeredVehicles;
    std::vector<Booking*> bookingHistory;
public:
    User(const std::string& id, const std::string& name, const std::string& level)
        : userId(id), name(name), membershipLevel(level) 
    { }
    void registerVehicle(EV* vehicle);
    void listVehicles() const;
    void viewBookings() const;
    std::string getUserId() const 
    {
        return userId; 
    }
    std::string getName() const 
    {
        return name; 
    }
    std::string getMembershipLevel() const 
    {
        return membershipLevel; 
    }
    void addBooking(Booking* booking);
};
#endif 

