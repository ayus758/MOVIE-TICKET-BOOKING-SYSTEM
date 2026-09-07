#ifndef TICKET_PRINTER_CPP
#define TICKET_PRINTER_CPP

#include <iostream>
#include <iomanip>
#include "Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking* booking) {
        cout << "\n";
        cout << "========================================\n";
        cout << "              BOOKING CONFIRMED          \n";
        cout << "========================================\n";
        cout << "Booking ID   : " << booking->getBookingId() << "\n";
        cout << "Movie        : " << booking->getShow()->getMovie().getTitle() << "\n";
        cout << "Language     : " << booking->getShow()->getMovie().getLanguage() << "\n";
        cout << "Screen       : " << booking->getShow()->getScreen().getScreenNumber() << "\n";
        cout << "Show Time    : " << booking->getShow()->getStartTime() << "\n";
        cout << "Customer     : " << booking->getCustomer().getName()
             << " (" << booking->getCustomer().getPhone() << ")\n";

        cout << "Seats        : ";
        vector<ShowSeat*> seats = booking->getSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeat().getSeatNumber();
            if (i != seats.size() - 1) cout << ", ";
        }
        cout << "\n";

        cout << fixed << setprecision(2);
        cout << "Total Amount : Rs. " << booking->getTotalAmount() << "\n";
        cout << "========================================\n";
        cout << "         Enjoy your movie! \n";
        cout << "========================================\n\n";
    }
};

#endif