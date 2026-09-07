#ifndef CARD_PAYMENT_CPP
#define CARD_PAYMENT_CPP

#include <string>
#include <iostream>
#include "Payment.cpp"
using namespace std;

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string cardNumber) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) override {
        this->amount = amount;
        cout << "\nProcessing Card payment of Rs. " << amount
             << " using card ending in "
             << cardNumber.substr(cardNumber.length() - 4) << "...\n";
        cout << "Payment successful!\n";
        return true;
    }
};

#endif