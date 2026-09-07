#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Cinema.cpp"
#include "Screen.cpp"
#include "Seat.cpp"
#include "Movie.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "BookingService.cpp"
#include "PaymentType.cpp"
using namespace std;

// Clears the console screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pauses execution until the user presses Enter, so output stays visible
void pauseForUser() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Builds the single screen with 10 Silver, 10 Gold, 10 Platinum seats
Screen buildScreen() {
    vector<Seat> seats;

    for (int i = 1; i <= 10; i++) {
        seats.push_back(Seat("S" + to_string(i), SeatType::SILVER));
    }
    for (int i = 1; i <= 10; i++) {
        seats.push_back(Seat("G" + to_string(i), SeatType::GOLD));
    }
    for (int i = 1; i <= 10; i++) {
        seats.push_back(Seat("P" + to_string(i), SeatType::PLATINUM));
    }

    return Screen(1, seats);
}

// Seeds the cinema with 3 movies and their shows
Cinema buildCinema() {
    Screen screen1 = buildScreen();

    Movie mirzapur("Mirzapur", "Hindi", 140);
    Movie endgame("Avengers: Endgame", "English", 181);
    Movie super30("Super 30", "Hindi", 154);

    vector<Show> shows;
    shows.push_back(Show("SH1", mirzapur, screen1, "10:00 AM"));
    shows.push_back(Show("SH2", mirzapur, screen1, "6:00 PM"));
    shows.push_back(Show("SH3", endgame, screen1, "1:00 PM"));
    shows.push_back(Show("SH4", endgame, screen1, "9:00 PM"));
    shows.push_back(Show("SH5", super30, screen1, "4:00 PM"));

    vector<Screen> screens;
    screens.push_back(screen1);

    return Cinema("PVR Cineplex", screens, shows);
}

void printHeader(string title) {
    cout << "\n----------------------------------------\n";
    cout << title << "\n";
    cout << "----------------------------------------\n";
}

void printMainMenu() {
    printHeader("MOVIE TICKET BOOKING SYSTEM");
    cout << "1. View Movies & Shows\n";
    cout << "2. View Seats for a Show\n";
    cout << "3. Book Seats\n";
    cout << "4. Make Payment for a Booking\n";
    cout << "5. Cancel a Booking\n";
    cout << "6. Exit\n";
    cout << "----------------------------------------\n";
    cout << "Enter choice: ";
}

Show* selectShow(Cinema& cinema) {
    vector<Movie> movies = cinema.listMovies();

    cout << "\nAvailable Movies:\n";
    for (size_t i = 0; i < movies.size(); i++) {
        cout << "  " << (i + 1) << ". " << movies[i].getTitle()
             << " (" << movies[i].getLanguage() << ", "
             << movies[i].getDuration() << " min)\n";
    }

    cout << "Select a movie (number): ";
    int movieChoice;
    cin >> movieChoice;

    if (movieChoice < 1 || movieChoice > (int)movies.size()) {
        cout << "Invalid choice.\n";
        return nullptr;
    }

    Movie selectedMovie = movies[movieChoice - 1];
    vector<Show*> shows = cinema.listShows(selectedMovie);

    cout << "\nShows for " << selectedMovie.getTitle() << ":\n";
    for (size_t i = 0; i < shows.size(); i++) {
        cout << "  " << (i + 1) << ". " << shows[i]->getShowId()
             << " - " << shows[i]->getStartTime() << "\n";
    }

    cout << "Select a show (number): ";
    int showChoice;
    cin >> showChoice;

    if (showChoice < 1 || showChoice > (int)shows.size()) {
        cout << "Invalid choice.\n";
        return nullptr;
    }

    return shows[showChoice - 1];
}

Booking* findBookingById(vector<Booking*>& allBookings, string bookingId) {
    for (Booking* b : allBookings) {
        if (b->getBookingId() == bookingId) {
            return b;
        }
    }
    return nullptr;
}

// Asks a yes/no question and returns true only for 'y'/'Y'
bool askYesNo(string question) {
    cout << question;
    char answer;
    cin >> answer;
    return (answer == 'y' || answer == 'Y');
}

// Handles the payment sub-flow for a booking that was just created
void runPaymentFlow(BookingService& bookingService, Booking* booking) {
    cout << "\nSelect payment method:\n";
    cout << "  1. UPI\n";
    cout << "  2. Card\n";
    cout << "  3. Cash\n";
    cout << "Enter choice: ";
    int payChoice;
    cin >> payChoice;

    PaymentType type;
    if (payChoice == 1) type = PaymentType::UPI;
    else if (payChoice == 2) type = PaymentType::CARD;
    else if (payChoice == 3) type = PaymentType::CASH;
    else {
        cout << "Invalid payment method. You can pay later from the main menu using Booking ID "
             << booking->getBookingId() << ".\n";
        return;
    }

    bookingService.makePayment(booking, type);
}

// One booking journey: pick seats -> book -> optionally pay.
// Pass an already-selected show to skip the movie/show picker.
void runBookingFlow(Cinema& cinema, BookingService& bookingService,
                     vector<Booking*>& allBookings, Show* preSelectedShow) {
    Show* show = preSelectedShow;
    if (show == nullptr) {
        show = selectShow(cinema);
        if (show == nullptr) return;
    }

    show->displaySeats();

    cout << "\nHow many seats do you want to book? ";
    int count;
    cin >> count;

    if (count <= 0) {
        cout << "Invalid number of seats.\n";
        return;
    }

    vector<string> seatNumbers;
    for (int i = 0; i < count; i++) {
        string seatNum;
        cout << "Enter seat number " << (i + 1) << ": ";
        cin >> seatNum;
        seatNumbers.push_back(seatNum);
    }

    cout << "Enter your name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "Enter your phone number: ";
    string phone;
    getline(cin, phone);

    Customer customer(name, phone);
    Booking* booking = bookingService.bookSeats(show, seatNumbers, customer);

    if (booking == nullptr) {
        cout << "Booking could not be completed.\n";
        return;
    }

    allBookings.push_back(booking);
    cout << "\nBooking created with ID " << booking->getBookingId()
         << " (status: PENDING).\n";

    if (askYesNo("Pay now? (y/n): ")) {
        runPaymentFlow(bookingService, booking);
    } else {
        cout << "No problem — pay later from the main menu (option 4) using Booking ID "
             << booking->getBookingId() << ".\n";
    }
}

// Repeats runBookingFlow() as many times as the user wants, asking
// "book more seats?" after each one. Only returns to the main menu
// when the user says no.
void bookingSession(Cinema& cinema, BookingService& bookingService,
                     vector<Booking*>& allBookings, Show* initialShow) {
    Show* showForThisRound = initialShow;
    bool continueBooking = true;

    while (continueBooking) {
        runBookingFlow(cinema, bookingService, allBookings, showForThisRound);

        // Only reuse the pre-selected show for the very first round;
        // later rounds let the user pick again (seats/availability may differ).
        showForThisRound = nullptr;

        continueBooking = askYesNo("\nDo you want to book more seats? (y/n): ");
    }
}

int main() {
    srand(time(0)); // seed random once, used by UPI/Card payment simulation

    Cinema cinema = buildCinema();
    BookingService bookingService;
    vector<Booking*> allBookings;

    int choice;
    bool running = true;

    while (running) {
        clearScreen();
        printMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            pauseForUser();
            continue;
        }

        switch (choice) {
            case 1: {
                printHeader("MOVIES & SHOWS");
                vector<Movie> movies = cinema.listMovies();
                for (Movie& m : movies) {
                    cout << "\n" << m.getTitle() << " (" << m.getLanguage()
                         << ", " << m.getDuration() << " min)\n";
                    vector<Show*> shows = cinema.listShows(m);
                    for (Show* s : shows) {
                        cout << "  " << s->getShowId() << " - " << s->getStartTime() << "\n";
                    }
                }

                if (askYesNo("\nDo you want to book seats now? (y/n): ")) {
                    bookingSession(cinema, bookingService, allBookings, nullptr);
                }
                pauseForUser();
                break;
            }

            case 2: {
                printHeader("VIEW SEATS");
                Show* show = selectShow(cinema);
                if (show != nullptr) {
                    show->displaySeats();

                    if (askYesNo("\nBook these seats now? (y/n): ")) {
                        bookingSession(cinema, bookingService, allBookings, show);
                    }
                }
                pauseForUser();
                break;
            }

            case 3: {
                printHeader("BOOK SEATS");
                bookingSession(cinema, bookingService, allBookings, nullptr);
                pauseForUser();
                break;
            }

            case 4: {
                printHeader("MAKE PAYMENT");
                cout << "Enter Booking ID: ";
                string bookingId;
                cin >> bookingId;

                Booking* booking = findBookingById(allBookings, bookingId);
                if (booking == nullptr) {
                    cout << "Error: No booking found with ID '" << bookingId << "'.\n";
                    pauseForUser();
                    break;
                }

                if (booking->getStatus() != BookingStatus::PENDING) {
                    cout << "Error: This booking is not pending payment.\n";
                    pauseForUser();
                    break;
                }

                runPaymentFlow(bookingService, booking);
                pauseForUser();
                break;
            }

            case 5: {
                printHeader("CANCEL BOOKING");
                cout << "Enter Booking ID: ";
                string bookingId;
                cin >> bookingId;

                Booking* booking = findBookingById(allBookings, bookingId);
                if (booking == nullptr) {
                    cout << "Error: No booking found with ID '" << bookingId << "'.\n";
                    pauseForUser();
                    break;
                }

                bookingService.cancelBooking(booking);
                pauseForUser();
                break;
            }

            case 6: {
                cout << "\nThank you for using the Movie Ticket Booking System. Goodbye!\n";
                running = false;
                break;
            }

            default: {
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                pauseForUser();
                break;
            }
        }
    }

    // Clean up dynamically allocated bookings
    for (Booking* b : allBookings) {
        delete b;
    }

    return 0;
}