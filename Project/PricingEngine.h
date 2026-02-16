#ifndef PRICING_ENGINE_H
#define PRICING_ENGINE_H

#include <string>
class PricingEngine 
{
public:
    enum class Speed { SLOW, FAST };
    enum class TimeOfDay { OFF_PEAK, PEAK };
    enum class Membership { NONE, SILVER, GOLD };
    enum class EnergySource { SOLAR, WIND, GRID };
    static double calculatePrice(Speed speed, TimeOfDay time, Membership membership, EnergySource source, int usageCount);
};
#endif


