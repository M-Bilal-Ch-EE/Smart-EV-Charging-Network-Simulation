#include "NotificationManager.h"

void NotificationManager::sendNotification(NotificationType type, const std::string& userId, const std::string& extra) 
{
    std::string message = composeMessage(type, userId, extra);
    std::time_t now = std::time(nullptr);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &now); 
    std::cout << "[Notification][" << buffer << "] " << message;
}
std::string NotificationManager::composeMessage(NotificationType type, const std::string& userId, const std::string& extra) 
{
    switch (type) 
    {
    case START_CHARGING:
        return "User " + userId + ": Charging session has started.";
    case STOP_CHARGING:
        return "User " + userId + ": Charging session has ended.";
    case LOW_BALANCE:
        return "User " + userId + ": Low account balance. Please recharge.";
    case BILL_GENERATED:
        return "User " + userId + ": Your invoice is ready. Amount: " + extra;
    case LOAD_WARNING:
        return "User " + userId + ": Load warning issued. Charging speed may be adjusted.";
    case ENERGY_SAVED:
        return "User " + userId + ": Energy-saving mode activated. Green credits earned.";
    case CUSTOM_MESSAGE:
        return "User " + userId + ": " + extra;
    default:
        return "User " + userId + ": Unknown notification.";
    }
}
