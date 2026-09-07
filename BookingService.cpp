#ifndef BOOKING_SERVICE_CPP
#define BOOKING_SERVICE_CPP

#include <string>
#include <vector>
#include <iostream>
#include "Show.cpp"
#include "ShowSeat.cpp"
#include "Booking.cpp"
#include "Customer.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "PaymentType.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "BookingStatus.cpp"
using namespace std;

class BookingService {
private:
    PriceCalculator calculator;
    TicketPrinter printer;

public:
        // Returns nullptr if any seat is invalid, already booked, or duplicated (any-seat-fails-all-fail rule)
    Booking* bookSeats(Show* show, vector<string> seatNumbers, Customer customer) {
        vector<ShowSeat*> selectedSeats;
        vector<string> seenSeatNumbers;

        for (string& seatNumber : seatNumbers) {
            // Reject duplicate seat numbers within the same request
            for (string& seen : seenSeatNumbers) {
                if (seen == seatNumber) {
                    cout << "Error: Seat '" << seatNumber
                         << "' was requested more than once. Booking aborted.\n";
                    return nullptr;
                }
            }

            ShowSeat* showSeat = show->getShowSeat(seatNumber);

            if (showSeat == nullptr) {
                cout << "Error: Invalid seat number '" << seatNumber << "'. Booking aborted.\n";
                return nullptr;
            }
            if (!showSeat->isAvailable()) {
                cout << "Error: Seat '" << seatNumber << "' is already booked. Booking aborted.\n";
                return nullptr;
            }

            selectedSeats.push_back(showSeat);
            seenSeatNumbers.push_back(seatNumber);
        }

        double total = calculator.calculateTotal(selectedSeats);
        Booking* booking = new Booking(show, customer, selectedSeats, total);

        for (ShowSeat* showSeat : selectedSeats) {
            showSeat->book();
        }

        cout << "\nSeats reserved. Booking ID: " << booking->getBookingId()
             << " | Total: Rs. " << booking->getTotalAmount() << "\n";
        cout << "Please proceed to payment to confirm your booking.\n";

        return booking; // status is still PENDING
    }
    
    bool makePayment(Booking* booking, PaymentType type) {
        Payment* payment = nullptr;

        switch (type) {
            case PaymentType::UPI: {
                string upiId;
                cout << "Enter UPI ID: ";
                cin >> upiId;
                payment = new UpiPayment(upiId);
                break;
            }
            case PaymentType::CARD: {
                string cardNumber;
                cout << "Enter Card Number: ";
                cin >> cardNumber;
                payment = new CardPayment(cardNumber);
                break;
            }
            case PaymentType::CASH: {
                payment = new CashPayment();
                break;
            }
        }

        bool success = payment->pay(booking->getTotalAmount());
        delete payment;

        if (success) {
            booking->confirm();
            printer.printTicket(booking);
            return true;
        } else {
            for (ShowSeat* showSeat : booking->getSeats()) {
                showSeat->release();
            }
            booking->fail();
            cout << "Booking " << booking->getBookingId()
                 << " could not be confirmed. Seats have been released.\n";
            return false;
        }
    }

    void cancelBooking(Booking* booking) {
        if (booking->getStatus() != BookingStatus::CONFIRMED) {
            cout << "Error: Only confirmed bookings can be cancelled.\n";
            return;
        }

        for (ShowSeat* showSeat : booking->getSeats()) {
            showSeat->release();
        }
        booking->cancel();

        cout << "Booking " << booking->getBookingId() << " has been cancelled. Seats are now available.\n";
    }
};

#endif