#ifndef GRID_POWER_H
#define GRID_POWER_H

#include "EnergySource.h"

class GridPower : public EnergySource {
public:
    GridPower(const std::string& id, float power);
    std::string getType() const override;
    float getCostPerKWh() const override;
};

#endif 


