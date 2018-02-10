#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string>

enum Genre { fiction, nonfiction, self_help, performance };
enum Media { books, periodicals, newspapers, audio, video };
enum Age   { children, teen, adult, restricted };

class Publication {
    public:
        Publication(std::string, std::string, std::string, std::string,
                    Genre, Media, Age);
        
        std::string to_string(); 
        std::string genre_to_string();
        std::string media_to_string();
        std::string age_to_string();

        bool is_checked_out();
        void check_out(std::string, std::string);
        void check_in();

    private:
        std::string _title;
        std::string _author;
        std::string _copyright;
        std::string _isbn;
        std::string _patron_name;
        std::string _patron_phone;
        Genre _genre;
        Media _media;
        Age _target_age;
        bool _checked_out;
};
#endif
