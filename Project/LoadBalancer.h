#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
class LoadBalancer 
{
public:
    struct Station 
    {
        int id;
        double capacity;
        double currentLoad;
    };
    LoadBalancer();
    void addStation(int id, double capacity);
    int assignStation(double requestedLoad);
    void updateLoad(int stationId, double loadChange);
private:
    std::vector<Station> stations;
};
#endif

