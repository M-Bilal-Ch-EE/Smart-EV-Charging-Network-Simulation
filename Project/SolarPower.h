#ifndef SOLAR_POWER_H
#define SOLAR_POWER_H

#include "EnergySource.h"

class SolarPower : public EnergySource {
public:
    SolarPower(const std::string& id, float power);
    std::string getType() const override;
    float getCostPerKWh() const override;
};

#endif 
