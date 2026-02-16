#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <string>
#include <iostream>
#include <ctime>
class NotificationManager 
{
public:
    enum NotificationType 
    {
        START_CHARGING,
        STOP_CHARGING,
        LOW_BALANCE,
        BILL_GENERATED,
        LOAD_WARNING,
        ENERGY_SAVED,
        CUSTOM_MESSAGE
    };
    void sendNotification(NotificationType type, const std::string& userId, const std::string& extra = "");
private:
    std::string composeMessage(NotificationType type, const std::string& userId, const std::string& extra);
};
#endif


