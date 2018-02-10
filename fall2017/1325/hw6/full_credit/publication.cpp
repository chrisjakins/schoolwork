#include <string>
#include "publication.h"
#include "patron.h"

Publication::Publication(std::string title, std::string author,
                         std::string copyright, std::string isbn,
                         Genre genre, Media media, Age target_age)
:   _title{title}, _author{author}, _copyright{copyright},
    _isbn{isbn}, _genre{genre}, _media{media}, _target_age{target_age},
    _checked_out{false}
{ }

Publication::Publication(std::string title, std::string author,
                         std::string copyright, std::string isbn,
                         int genre, int media, int target_age)
:   _title{title}, _author{author}, _copyright{copyright},
    _isbn{isbn}, _genre{convertGenre(genre)}, _media{convertMedia(media)},
     _target_age{convertAge(target_age)}, _checked_out{false}
{ }

/* "Title" by Author, Copyright (age genre media) ISBN: isbn#
    Checked out info */
std::string Publication::to_string() {
    std::string string_rep = "\"" + _title + "\" by " + _author + ", " + 
                             _copyright + ", (" + age_to_string() + " " +
                             genre_to_string() + " " + media_to_string() +
                             ") ISBN: " + _isbn + "\n";

    if (_checked_out) {
        string_rep += "Checked out by " + _patron.to_string() + '\n';
    }
    return string_rep;
}

std::string Publication::genre_to_string() {
    switch (_genre) {
        case fiction: return "fiction";
        case nonfiction: return "nonfiction";
        case self_help: return "self-help";
        case performance: return "performance";
        default: return "";
    }
}

std::string Publication::media_to_string() {
    switch (_media) {
        case books: return "books";
        case periodicals: return "periodicals";
        case newspapers: return "newspapers";
        case audio: return "audio";
        case video: return "video";
        default: return "";
    }
}

std::string Publication::age_to_string() {
    switch (_target_age) {
        case children: return "children";
        case teen: return "teen";
        case adult: return "adult";
        case restricted: return "restricted";
        default: return "";
    }
}

bool Publication::is_checked_out() {
    return _checked_out;
}

void Publication::check_out(Patron & patron) {
    if (!_checked_out) {
        _checked_out = true;
        _patron = patron;
    }
}

void Publication::check_in() {
    if (_checked_out) {
        _checked_out = false;
    }
}

Genre Publication::convertGenre(int gen) {
    switch (gen) {
        case 1: return fiction;
        case 2: return nonfiction;
        case 3: return self_help;
        case 4: return performance;
        default: return fiction;
    }
}

Media Publication::convertMedia(int med) {
    switch (med) {
        case 1: return books;
        case 2: return periodicals;
        case 3: return newspapers;
        case 4: return audio;
        case 5: return video;
        default: return books;
    }
}
Age Publication::convertAge(int age) {
    switch (age) {
        case 1: return children;
        case 2: return teen;
        case 3: return adult;
        case 4: return restricted;
        default: return children;
    }
}
