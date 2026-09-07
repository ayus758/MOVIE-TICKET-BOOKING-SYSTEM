#ifndef UPI_PAYMENT_CPP
#define UPI_PAYMENT_CPP

#include <string>
#include <iostream>
#include "Payment.cpp"
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string upiId) {
        this->upiId = upiId;
    }

    bool pay(double amount) override {
        this->amount = amount;
        cout << "\nProcessing UPI payment of Rs. " << amount
             << " via UPI ID: " << upiId << "...\n";
        cout << "Payment successful!\n";
        return true;
    }
};

#endif