#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string>
#include "patron.h"

enum Genre { fiction, nonfiction, self_help, performance };
enum Media { books, periodicals, newspapers, audio, video };
enum Age   { children, teen, adult, restricted };

class Publication {
    public:
        Publication(std::string, std::string, std::string, std::string,
                    Genre, Media, Age);

        Publication(std::string, std::string, std::string, std::string,
                    int, int, int);
        
        std::string to_string(); 
        std::string genre_to_string();
        std::string media_to_string();
        std::string age_to_string();

        bool is_checked_out();
        void check_out(Patron &);
        void check_in();
    private:
        std::string _title;
        std::string _author;
        std::string _copyright;
        std::string _isbn;
        Genre _genre;
        Media _media;
        Age _target_age;
        bool _checked_out;
        Patron _patron;

        Genre convertGenre(int);
        Media convertMedia(int);
        Age convertAge(int);
};
#endif
