#include "EnergyTracker.h"
EnergyTracker::EnergyTracker(const std::string& userId)
    : userId(userId), energyUsed(0), energySaved(0), energyCost(0), energyRate(0.15) 
{
}
void EnergyTracker::startSession(double energyRequired)
{
    energyUsed = energyRequired;
    energyCost = energyUsed * energyRate;
    std::cout << "Charging started for user " << userId << ". Energy required: " << energyRequired << " kWh.\n";
}
void EnergyTracker::endSession()
{
    std::cout << "Charging session ended for user " << userId << ". Total energy used: "
        << energyUsed << " kWh. Cost: $" << energyCost << ".\n";
    energyUsed = 0;
    energyCost = 0;
}
void EnergyTracker::addSavedEnergy(double savedEnergy) 
{
    energySaved += savedEnergy;
    std::cout << "Energy saved for user " << userId << ": " << savedEnergy << " kWh.\n";
}
double EnergyTracker::getEnergyUsed() const 
{
    return energyUsed;
}
double EnergyTracker::getEnergySaved() const 
{
    return energySaved;
}
double EnergyTracker::getTotalCost() const 
{
    return energyCost;
}
