#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <limits>
#include "User.h"
#include "EV.h"
#include "ChargingDock.h"
#include "ChargingStation.h"
#include "Booking.h"
#include "Invoice.h"
#include "EnergySource.h"
#include "SolarPower.h"
#include "GridPower.h"
#include "PricingEngine.h"
#include "LoadBalancer.h"
#include "EnergyTracker.h"
#include "AnalyticsEngine.h"
#include "NotificationManager.h"
using namespace std;
int main() 
{
    using namespace std;
    vector<unique_ptr<User>> users;
    vector<unique_ptr<EV>> evs;
    vector<unique_ptr<ChargingStation>> stations;
    vector<unique_ptr<EnergySource>> energySources;
    LoadBalancer loadBalancer;
    AnalyticsEngine analytics;
    NotificationManager notifier;
    int usageCount = 0;
    auto station1 = make_unique<ChargingStation>("Station_A", "Downtown", 500);
    auto station2 = make_unique<ChargingStation>("Station_B", "Uptown", 600);
    for (int i = 1; i <= 5; ++i) 
    {
        station1->addDock(new ChargingDock("DockA" + to_string(i), 20.0f + i * 2)); 
        station2->addDock(new ChargingDock("DockB" + to_string(i), 25.0f + i * 2)); 
    }
    loadBalancer.addStation(1, 500);
    loadBalancer.addStation(2, 600);
    stations.push_back(move(station1));
    stations.push_back(move(station2));
    while (true)
    {
        cout << "\n======= EV Charging Management System =======\n";
        cout << "1. Add User\n2. Register EV\n3. Create Charging Station\n4. Add Dock to Station\n";
        cout << "5. Book and Simulate Charging\n6. View Analytics\n7. Exit\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) 
        {
            string id, name, membership;
            cout << "Enter User ID: "; getline(cin, id);
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Membership (Premium/Silver/None): "; getline(cin, membership);
            users.push_back(make_unique<User>(id, name, membership));
        }
        else if (choice == 2) 
        {
            if (users.empty()) 
            {
                cout << "No users available.\n"; 
                continue; 
            }
            string evId, make, model, port;
            float cap, soc;
            cout << "Enter EV ID: "; getline(cin, evId);
            cout << "Brand: "; getline(cin, make);
            cout << "Model: "; getline(cin, model);
            cout << "Battery Capacity (kWh): "; cin >> cap;
            cout << "Current SOC (%): "; cin >> soc;
            cin.ignore();
            cout << "Port Type: "; getline(cin, port);
            evs.push_back(make_unique<EV>(evId, make, model, cap, soc, port));
            int uid;
            cout << "Register to which user (index 0 to " << users.size() - 1 << "): "; cin >> uid; cin.ignore();
            if (uid >= 0 && uid < users.size()) users[uid]->registerVehicle(evs.back().get());
        }
        else if (choice == 3)
        {
            string id, loc;
            float maxLoad;
            cout << "Station ID: "; getline(cin, id);
            cout << "Location: "; getline(cin, loc);
            cout << "Max Load (kW): "; cin >> maxLoad;
            cin.ignore();
            stations.push_back(make_unique<ChargingStation>(id, loc, maxLoad));
            loadBalancer.addStation((int)stations.size(), maxLoad);
        }
        else if (choice == 4) 
        {
            int sid;
            float speed;
            string dockId;
            if (stations.empty()) 
            {
                cerr << "No stations available." << endl;
                continue;
            }
            cout << "Station index (0 to " << stations.size() - 1 << "): ";
            while (!(cin >> sid) || sid < 0 || sid >= stations.size()) 
            {
                cout << "Invalid input. Please enter a valid station index (0 to " << stations.size() - 1 << "): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Dock ID: ";
            cin >> dockId;
            cout << "Charging Speed (kWh): ";
            cin >> speed;
            cin.ignore();
            stations[sid]->addDock(new ChargingDock(dockId, speed));
        }
        else if (choice == 5) 
        {
            if (users.empty() || evs.empty() || stations.empty()) 
            {
                cout << "Ensure users, EVs, and stations are set up first.\n";
                continue;
            }
            int u, e, s;
            cout << "User index: "; cin >> u;
            cout << "EV index: "; cin >> e;
            cout << "Station index: "; cin >> s;
            cin.ignore();
            auto start = chrono::system_clock::now();
            auto end = start + chrono::hours(2);
            Booking booking("B001", evs[e].get(), users[u].get(), start, end, 0);
            stations[s]->assignDock(evs[e].get(), &booking);
            auto availableDocks = stations[s]->getAvailableDocks();
            if (availableDocks.empty()) 
            {
                cout << "No available docks at this station.\n";
                continue;
            }
            float speed = availableDocks[0]->getChargingSpeed();
            float duration = 2.0f;
            float energy = speed * duration;
            SolarPower solar("Solar001", 500);
            GridPower grid("Grid001", 1000);
            float solarUsed = solar.provideEnergy(energy);
            float gridUsed = grid.provideEnergy(energy - solarUsed);
            EnergyTracker tracker(users[u]->getName());
            tracker.startSession(energy);
            tracker.addSavedEnergy(solarUsed);
            tracker.endSession();
            booking.markCompleted(energy);
            users[u]->addBooking(&booking);
            PricingEngine::Speed chargingSpeed = (speed > 30) ? PricingEngine::Speed::FAST : PricingEngine::Speed::SLOW;
            PricingEngine::TimeOfDay timeOfDay = PricingEngine::TimeOfDay::PEAK;
            PricingEngine::Membership membership = PricingEngine::Membership::NONE;
            string m = users[u]->getMembershipLevel();
            if (m == "Silver") membership = PricingEngine::Membership::SILVER;
            else if (m == "Premium") membership = PricingEngine::Membership::GOLD;
            PricingEngine::EnergySource source = (solarUsed >= energy / 2) ? PricingEngine::EnergySource::SOLAR : PricingEngine::EnergySource::GRID;
            double rate = PricingEngine::calculatePrice(chargingSpeed, timeOfDay, membership, source, usageCount);
            usageCount++;
            Invoice invoice("INV001", &booking, (float)rate);
            invoice.printInvoice();
            notifier.sendNotification(NotificationManager::BILL_GENERATED, users[u]->getName(), to_string(invoice.getTotalCost()));
            analytics.logSession(1, s + 1, energy, invoice.getTotalCost(), duration * 60);
            stations[s]->displayStationStatus();
        }
        else if (choice == 6) 
        {
            cout << "Total Energy Used: " << analytics.getTotalEnergyUsed() << " kWh\n";
            cout << "Average Session Duration: " << analytics.getAverageSessionDuration() << " minutes\n";
            cout << "Most Used Station ID: " << analytics.getMostUsedStation() << "\n";
        }
        else if (choice == 7) 
        {
            break;
        }
        else 
        {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}