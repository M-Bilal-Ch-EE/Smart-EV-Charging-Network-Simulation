#include "User.h"
#include "EV.h"
#include "Booking.h"
void User::registerVehicle(EV* vehicle) 
{
    registeredVehicles.push_back(vehicle);
    std::cout << "Vehicle registered successfully.\n";
}
void User::listVehicles() const 
{
    std::cout << "Registered Vehicles for " << name << ":\n";
    for (const auto& ev : registeredVehicles) 
    {
        ev->displayInfo();
    }
}
void User::viewBookings() const
{
    std::cout << "Booking History for " << name << ":\n";
    for (const auto& booking : bookingHistory) 
    {
        booking->displaySummary();
    }
}
void User::addBooking(Booking* booking) 
{
    bookingHistory.push_back(booking);
}

