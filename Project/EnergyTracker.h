#ifndef ENERGY_TRACKER_H
#define ENERGY_TRACKER_H

#include <string>
#include <iostream>
class EnergyTracker 
{
public:
    EnergyTracker(const std::string& userId);
    void startSession(double energyRequired);
    void endSession();
    void addSavedEnergy(double savedEnergy);
    double getEnergyUsed() const;
    double getEnergySaved() const;
    double getTotalCost() const;
private:
    std::string userId;
    double energyUsed;
    double energySaved;
    double energyCost; 
    double energyRate;
};
#endif
