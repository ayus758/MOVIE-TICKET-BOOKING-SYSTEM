#ifndef SHOW_SEAT_CPP
#define SHOW_SEAT_CPP

#include "Seat.cpp"
#include "SeatStatus.cpp"

class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat(Seat seat) : seat(seat) {
        status = SeatStatus::AVAILABLE;
    }

    Seat getSeat() const {
        return seat;
    }

    SeatStatus getStatus() const {
        return status;
    }

    bool isAvailable() const {
        return status == SeatStatus::AVAILABLE;
    }

    void book() {
        status = SeatStatus::BOOKED;
    }

    void release() {
        status = SeatStatus::AVAILABLE;
    }
};

#endif