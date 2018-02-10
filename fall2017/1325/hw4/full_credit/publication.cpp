#include <string>
#include "publication.h"

Publication::Publication(std::string title, std::string author,
                         std::string copyright, std::string isbn,
                         Genre genre, Media media, Age target_age)
:   _title{title}, _author{author}, _copyright{copyright},
    _isbn{isbn}, _genre{genre}, _media{media}, _target_age{target_age},
    _checked_out{false}
{ }

/* "Title" by Author, Copyright (age genre media) ISBN: isbn#
    Checked out info */
std::string Publication::to_string() {
    std::string string_rep = "\"" + _title + "\" by " + _author + ", " + 
                             _copyright + ", (" + age_to_string() + " " +
                             genre_to_string() + " " + media_to_string() +
                             ") ISBN: " + _isbn + "\n";

    if (_checked_out) {
        string_rep += "Checked out by " + _patron_name + " (" + 
                      _patron_phone + ")\n";
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

void Publication::check_out(std::string name, std::string number) {
    if (!_checked_out) {
        _checked_out = true;
        _patron_name = name;
        _patron_phone = number;
    }
}

void Publication::check_in() {
    if (_checked_out) {
        _checked_out = false;
        _patron_name = "";
        _patron_phone = "";
    }
}
