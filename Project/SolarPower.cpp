#include "SolarPower.h"

SolarPower::SolarPower(const std::string& id, float power)
    : EnergySource(id, power) 
{ }
std::string SolarPower::getType() const 
{
    return "Solar";
}
float SolarPower::getCostPerKWh() const 
{
    return 0.10f; 
}