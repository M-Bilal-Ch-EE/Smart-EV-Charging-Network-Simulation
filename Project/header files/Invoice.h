#ifndef INVOICE_H
#define INVOICE_H

#include <string>
#include "Booking.h"
class Invoice 
{
private:
    std::string invoiceId;
    Booking* booking;
    float energyConsumed;   
    float durationHours;
    float pricePerKWh;
    float baseCost;
    float penaltyFee;
    float totalCost;
public:
    Invoice(const std::string& id, Booking* booking, float pricePerKWh);
    void calculateTotal();
    std::string getInvoiceId() const;
    float getTotalCost() const;
    void printInvoice() const;
};
#endif

