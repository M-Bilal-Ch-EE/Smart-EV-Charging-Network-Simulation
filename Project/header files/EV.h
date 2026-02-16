#ifndef EV_H
#define EV_H

#include <iostream>
#include <string>
class EV 
{
private:
    std::string evId;
    std::string make;
    std::string model;
    float batteryCapacityKWh; 
    float currentSOC;     
    std::string portType;   
public:
    EV(const std::string& id, const std::string& make, const std::string& model,
        float capacity, float soc, const std::string& port);
    std::string getEVId() const;
    float getBatteryCapacity() const;
    float getCurrentSOC() const;
    std::string getPortType() const;
    void updateSOC(float energyAddedKWh);  
    float estimateChargingTime(float chargingSpeedKWh) const;
    void displayInfo() const;
};
#endif 
