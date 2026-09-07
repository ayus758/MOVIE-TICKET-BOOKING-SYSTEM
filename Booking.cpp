#ifndef BOOKING_CPP
#define BOOKING_CPP

#include <string>
#include <vector>
#include "Show.cpp"
#include "Customer.cpp"
#include "ShowSeat.cpp"
#include "BookingStatus.cpp"
using namespace std;

class Booking {
private:
    string bookingId;
    Show* show;
    Customer customer;
    vector<ShowSeat*> seats;
    double totalAmount;
    BookingStatus status;

    static int bookingCounter;

public:
    Booking(Show* show, Customer customer, vector<ShowSeat*> seats, double totalAmount)
        : show(show), customer(customer) {
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->status = BookingStatus::PENDING;

        bookingCounter++;
        this->bookingId = "BK" + to_string(1000 + bookingCounter);
    }

    string getBookingId() const {
        return bookingId;
    }

    Show* getShow() const {
        return show;
    }

    Customer getCustomer() const {
        return customer;
    }

    vector<ShowSeat*> getSeats() const {
        return seats;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    BookingStatus getStatus() const {
        return status;
    }

    void confirm() {
        status = BookingStatus::CONFIRMED;
    }

    void fail() {
        status = BookingStatus::FAILED;
    }

    void cancel() {
        status = BookingStatus::CANCELLED;
    }
};

int Booking::bookingCounter = 0;

#endif