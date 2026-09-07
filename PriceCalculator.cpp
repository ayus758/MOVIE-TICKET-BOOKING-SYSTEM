#ifndef PRICE_CALCULATOR_CPP
#define PRICE_CALCULATOR_CPP

#include <vector>
#include "ShowSeat.cpp"
#include "SeatType.cpp"
using namespace std;

class PriceCalculator {
public:
    static const int SILVER_PRICE = 150;
    static const int GOLD_PRICE = 250;
    static const int PLATINUM_PRICE = 400;

    double calculateTotal(vector<ShowSeat*> seats) {
        double total = 0;
        for (ShowSeat* ss : seats) {
            switch (ss->getSeat().getType()) {
                case SeatType::SILVER:
                    total += SILVER_PRICE;
                    break;
                case SeatType::GOLD:
                    total += GOLD_PRICE;
                    break;
                case SeatType::PLATINUM:
                    total += PLATINUM_PRICE;
                    break;
            }
        }
        return total;
    }
};

#endif