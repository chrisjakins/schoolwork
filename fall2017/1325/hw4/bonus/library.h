#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <string>
#include "publication.h"
#include "patron.h"

class Library {
    public:

        /* Singleton pattern components */
        static Library & get_instance() {
            static Library instance;
            return instance;
        }

        Library(Library const &) = delete;
        void operator=(Library const &) = delete;

        /* Library functionality */
        void add_publication(Publication);
        void check_out(int, int); 
        void check_in(int);
        std::string publication_to_string(int);
        int number_of_publications();

        void add_patron(Patron &);
        std::string patron_to_string(int);
        int number_of_patrons();
    private:
        Library();
        std::vector<Publication> _publications;
        std::vector<Patron> _patrons;
};
#endif
