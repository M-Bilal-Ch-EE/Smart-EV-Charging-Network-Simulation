#include "PricingEngine.h"
double PricingEngine::calculatePrice(Speed speed, TimeOfDay time, Membership membership, EnergySource source, int usageCount) 
{
    double baseRate = 0.20;
    switch (speed) 
    {
    case Speed::SLOW:
        baseRate *= 1.0;
        break;
    case Speed::FAST:
        baseRate *= 1.5;
        break;
    }
    switch (time) 
    {
    case TimeOfDay::OFF_PEAK:
        baseRate *= 0.8;
        break;
    case TimeOfDay::PEAK:
        baseRate *= 1.2;
        break;
    }
    switch (membership) 
    {
    case Membership::NONE:
        baseRate *= 1.0;
        break;
    case Membership::SILVER:
        baseRate *= 0.9;
        break;
    case Membership::GOLD:
        baseRate *= 0.8;
        break;
    }
    switch (source) 
    {
    case EnergySource::SOLAR:
        baseRate *= 0.85;
        break;
    case EnergySource::WIND:
        baseRate *= 0.90;
        break;
    case EnergySource::GRID:
        baseRate *= 1.0;
        break;
    }
    if (usageCount > 50) 
    {
        baseRate *= 0.95;
    }
    return baseRate;
}