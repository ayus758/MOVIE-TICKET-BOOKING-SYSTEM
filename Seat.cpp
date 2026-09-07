#ifndef SEAT_CPP
#define SEAT_CPP

#include <string>
#include "SeatType.cpp"
using namespace std;

class Seat {
private:
    string seatNumber;
    SeatType type;

public:
    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    string getSeatNumber() const {
        return seatNumber;
    }

    SeatType getType() const {
        return type;
    }
};

#endif