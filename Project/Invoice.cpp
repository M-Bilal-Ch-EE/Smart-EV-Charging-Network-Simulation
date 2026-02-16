#include "Invoice.h"
#include <iostream>
#include <iomanip>
#include <chrono>

Invoice::Invoice(const std::string& id, Booking* b, float priceRate)
    : invoiceId(id), booking(b), pricePerKWh(priceRate), penaltyFee(0.0f) 
{
    energyConsumed = booking->getEstimatedEnergy(); 
    penaltyFee = booking->getPenaltyAmount();
    calculateTotal();
}

void Invoice::calculateTotal() {
    baseCost = energyConsumed * pricePerKWh;
    totalCost = baseCost + penaltyFee;
}

std::string Invoice::getInvoiceId() const {
    return invoiceId;
}

float Invoice::getTotalCost() const {
    return totalCost;
}

void Invoice::printInvoice() const {
    std::cout << "\n====== Invoice ======\n"
        << "Invoice ID: " << invoiceId << "\n"
        << "User: " << booking->getUser()->getName() << "\n"
        << "EV: " << booking->getEV()->getEVId() << "\n"
        << "Energy Consumed: " << energyConsumed << " kWh\n"
        << "Rate: $" << pricePerKWh << " / kWh\n"
        << "Base Cost: $" << baseCost << "\n";

    if (penaltyFee > 0.0f) {
        std::cout << "Penalty Fee: $" << penaltyFee << "\n";
    }

    std::cout << "Total Cost: $" << totalCost << "\n"
        << "=====================\n";
}
