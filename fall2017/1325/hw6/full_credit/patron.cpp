#include "patron.h"
#include <string>

Patron::Patron(std::string name, std::string number) 
: _name{name}, _number{number}
{ }

Patron::Patron()
: Patron("", "")
{ }

std::string Patron::to_string() {
    std::string result = _name + " (" + _number + ")";
    return result;
}
