#ifndef SHOW_CPP
#define SHOW_CPP

#include <string>
#include <vector>
#include <iostream>
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"
using namespace std;

class Show {
private:
    string showId;
    Movie movie;
    Screen screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(string showId, Movie movie, Screen screen, string startTime)
        : movie(movie), screen(screen) {
        this->showId = showId;
        this->startTime = startTime;

        // One ShowSeat per physical Seat on this Screen
        for (const Seat& s : screen.getSeats()) {
            showSeats.push_back(ShowSeat(s));
        }
    }

    string getShowId() const {
        return showId;
    }

    Movie getMovie() const {
        return movie;
    }

    Screen getScreen() const {
        return screen;
    }

    string getStartTime() const {
        return startTime;
    }

    vector<ShowSeat>& getShowSeats() {
        return showSeats;
    }

    void displaySeats() {
        cout << "\nSeats for " << movie.getTitle() << " at " << startTime << ":\n";
        for (ShowSeat& ss : showSeats) {
            string typeStr;
            switch (ss.getSeat().getType()) {
                case SeatType::SILVER: typeStr = "Silver"; break;
                case SeatType::GOLD: typeStr = "Gold"; break;
                case SeatType::PLATINUM: typeStr = "Platinum"; break;
            }
            string statusStr = ss.isAvailable() ? "Available" : "Booked";
            cout << "  " << ss.getSeat().getSeatNumber()
                 << " [" << typeStr << "] - " << statusStr << "\n";
        }
    }

    ShowSeat* getShowSeat(string seatNumber) {
        for (ShowSeat& ss : showSeats) {
            if (ss.getSeat().getSeatNumber() == seatNumber) {
                return &ss;
            }
        }
        return nullptr;
    }
};

#endif