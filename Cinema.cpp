#ifndef CINEMA_CPP
#define CINEMA_CPP

#include <string>
#include <vector>
#include <algorithm>
#include "Screen.cpp"
#include "Show.cpp"
#include "Movie.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;
    vector<Show> shows;

public:
    Cinema(string name, vector<Screen> screens, vector<Show> shows) {
        this->name = name;
        this->screens = screens;
        this->shows = shows;
    }

    string getName() const {
        return name;
    }

    vector<Screen> getScreens() const {
        return screens;
    }

    vector<Show>& getShows() {
        return shows;
    }

    // Derives distinct movies from the list of shows
    vector<Movie> listMovies() const {
        vector<Movie> movies;
        for (const Show& s : shows) {
            bool alreadyAdded = false;
            for (const Movie& m : movies) {
                if (m.getTitle() == s.getMovie().getTitle()) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) {
                movies.push_back(s.getMovie());
            }
        }
        return movies;
    }

    // Filters shows by movie title
    vector<Show*> listShows(const Movie& movie) {
        vector<Show*> result;
        for (Show& s : shows) {
            if (s.getMovie().getTitle() == movie.getTitle()) {
                result.push_back(&s);
            }
        }
        return result;
    }
};

#endif