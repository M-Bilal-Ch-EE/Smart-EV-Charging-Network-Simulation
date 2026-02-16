#include "EV.h"
#include <iomanip>

EV::EV(const std::string& id, const std::string& make, const std::string& model,
    float capacity, float soc, const std::string& port)
    : evId(id), make(make), model(model), batteryCapacityKWh(capacity),
    currentSOC(soc), portType(port) {
}

std::string EV::getEVId() const {
    return evId;
}

float EV::getBatteryCapacity() const {
    return batteryCapacityKWh;
}

float EV::getCurrentSOC() const {
    return currentSOC;
}

std::string EV::getPortType() const {
    return portType;
}

void EV::updateSOC(float energyAddedKWh) {
    float addedPercent = (energyAddedKWh / batteryCapacityKWh) * 100.0f;
    currentSOC += addedPercent;
    if (currentSOC > 100.0f)
        currentSOC = 100.0f;
}

float EV::estimateChargingTime(float chargingSpeedKWh) const {
    float remainingKWh = batteryCapacityKWh * ((100.0f - currentSOC) / 100.0f);
    return remainingKWh / chargingSpeedKWh; 
}

void EV::displayInfo() const {
    std::cout << "EV ID: " << evId << "\n"
        << "Make: " << make << ", Model: " << model << "\n"
        << "Battery: " << batteryCapacityKWh << " kWh, SOC: " << std::fixed << std::setprecision(1)
        << currentSOC << "%\n"
        << "Port Type: " << portType << "\n\n";
}
