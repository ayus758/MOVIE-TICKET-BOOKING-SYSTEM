#ifndef CASH_PAYMENT_CPP
#define CASH_PAYMENT_CPP

#include <iostream>
#include "Payment.cpp"
using namespace std;

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        this->amount = amount;
        cout << "\nProcessing Cash payment of Rs. " << amount << " at counter...\n";
        // Cash is treated as always successful (money in hand)
        cout << "Payment successful!\n";
        return true;
    }
};

#endif