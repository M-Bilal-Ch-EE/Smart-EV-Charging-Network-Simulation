#include "EnergySource.h"

EnergySource::EnergySource(const std::string& id, float power)
    : sourceId(id), availablePowerKW(power) {
}

float EnergySource::provideEnergy(float requestedKWh) {
    float provided = std::min(requestedKWh, availablePowerKW);
    availablePowerKW -= provided;
    return provided;
}

float EnergySource::getAvailablePower() const {
    return availablePowerKW;
}

void EnergySource::setAvailablePower(float power) {
    availablePowerKW = power;
}

std::string EnergySource::getSourceId() const {
    return sourceId;
}

