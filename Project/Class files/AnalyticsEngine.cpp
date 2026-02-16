#include "AnalyticsEngine.h"
#include <unordered_map>
AnalyticsEngine::AnalyticsEngine() {}
void AnalyticsEngine::logSession(int sessionId, int stationId, double energyUsed, double pricePaid, double duration) 
{
    sessions.push_back({ sessionId, stationId, energyUsed, pricePaid, duration });
}
double AnalyticsEngine::getTotalEnergyUsed() const 
{
    double total = 0;
    for (const auto& session : sessions) 
    {
        total += session.energyUsed;
    }
    return total;
}
double AnalyticsEngine::getAverageSessionDuration() const 
{
    if (sessions.empty())
    {
        return 0;
    }
    double totalDuration = 0;
    for (const auto& session : sessions) 
    {
        totalDuration += session.duration;
    }
    return totalDuration / sessions.size();
}
int AnalyticsEngine::getMostUsedStation() const 
{
    std::unordered_map<int, int> stationCount;
    for (const auto& session : sessions) 
    {
        stationCount[session.stationId]++;
    }
    int mostUsed = -1;
    int maxCount = 0;
    for (const auto& pair : stationCount) 
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            mostUsed = pair.first;
        }
    }
    return mostUsed;
}