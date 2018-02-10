#ifndef PATRON_H
#define PATRON_H
#include <string>

class Patron {
    public:
        Patron(std::string, std::string);
        Patron();
        std::string to_string();
    private:
        std::string _name;
        std::string _number;
};
#endif
