#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration; // in minutes

public:
    Movie(string title, string language, int duration) {
        this->title = title;
        this->language = language;
        this->duration = duration;
    }

    string getTitle() const {
        return title;
    }

    string getLanguage() const {
        return language;
    }

    int getDuration() const {
        return duration;
    }
};

#endif