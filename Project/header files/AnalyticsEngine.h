#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

#include <vector>

class AnalyticsEngine {
public:
    struct Session {
        int sessionId;
        int stationId;
        double energyUsed;
        double pricePaid;  
        double duration;   
    };

    AnalyticsEngine();
    void logSession(int sessionId, int stationId, double energyUsed, double pricePaid, double duration);
    double getTotalEnergyUsed() const;
    double getAverageSessionDuration() const;
    int getMostUsedStation() const;

private:
    std::vector<Session> sessions;
};

#endif

