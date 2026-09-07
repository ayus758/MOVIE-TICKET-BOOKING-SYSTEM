#ifndef UPI_PAYMENT_CPP
#define UPI_PAYMENT_CPP

#include <string>
#include <iostream>
#include <cstdlib>
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

        // Simulate ~15% chance of failure (e.g. UPI timeout/declined)
        int roll = rand() % 100;
        if (roll < 15) {
            cout << "Payment failed: UPI transaction declined. Please try again.\n";
            return false;
        }

        cout << "Payment successful!\n";
        return true;
    }
};

#endif