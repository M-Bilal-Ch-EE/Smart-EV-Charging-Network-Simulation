#include "LoadBalancer.h"
LoadBalancer::LoadBalancer()
{ }
void LoadBalancer::addStation(int id, double capacity) 
{
    stations.push_back({ id, capacity, 0.0 });
}
int LoadBalancer::assignStation(double requestedLoad) 
{
    int bestStation = -1;
    double minExtraLoad = 1e9;
    for (size_t i = 0; i < stations.size(); ++i)
    {
        double available = stations[i].capacity - stations[i].currentLoad;
        if (available >= requestedLoad && available < minExtraLoad)
        {
            minExtraLoad = available;
            bestStation = stations[i].id;
        }
    }
    return bestStation; 
}
void LoadBalancer::updateLoad(int stationId, double loadChange) 
{
    for (auto& station : stations)
    {
        if (station.id == stationId)
        {
            station.currentLoad += loadChange;
            if (station.currentLoad < 0) station.currentLoad = 0;
            if (station.currentLoad > station.capacity) station.currentLoad = station.capacity;
            break;
        }
    }
}

