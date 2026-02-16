#ifndef ENERGY_SOURCE_H
#define ENERGY_SOURCE_H

#include <string>
class EnergySource 
{
protected:
    std::string sourceId;
    float availablePowerKW;  
public:
    EnergySource(const std::string& id, float power);
    virtual ~EnergySource() = default;
    virtual std::string getType() const = 0;
    virtual float getCostPerKWh() const = 0;
    virtual float provideEnergy(float requestedKWh);
    float getAvailablePower() const;
    void setAvailablePower(float power);
    std::string getSourceId() const;
};
#endif
