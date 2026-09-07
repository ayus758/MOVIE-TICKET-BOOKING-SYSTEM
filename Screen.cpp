#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <vector>
#include "Seat.cpp"
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber, vector<Seat> seats) {
        this->screenNumber = screenNumber;
        this->seats = seats;
    }

    vector<Seat> getSeats() const {
        return seats;
    }

    int getScreenNumber() const {
        return screenNumber;
    }
};

#endif