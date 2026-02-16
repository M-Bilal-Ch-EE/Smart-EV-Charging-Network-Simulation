#include "GridPower.h"

GridPower::GridPower(const std::string& id, float power)
    : EnergySource(id, power) {
}

std::string GridPower::getType() const {
    return "Grid";
}

float GridPower::getCostPerKWh() const {
    return 0.25f;  
}
