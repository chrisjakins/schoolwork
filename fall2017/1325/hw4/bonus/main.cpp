#include <string>
#include <iostream>
#include "library.h"
#include "publication.h"
#include "patron.h"

int menu();
void list_publications();
void execute_cmd(int);

void add_publication();
void list_publications();
void check_out();
void check_in();
void get_help();
void fill_library();

void add_patron();
void list_patrons();

Genre get_genre();
Media get_media();
Age get_age();

int main() {
    int choice;

    std::cout << "=================================\n"
              << "CSE1325 Library Management System\n"
              << "=================================\n\n";

    choice = menu();
    while (choice != 0) {
        execute_cmd(choice);
        choice = menu();
    }

    std::cout << "Thanks for using our Library Management System. Goodbye.\n";
    return 0;
}

int menu() {
    int choice;
     
    std::cout << "\nPublications\n------------\n"
              << "(1) Add publication\n(2) List all publications\n"
              << "(3) Check out publication\n(4) Check in publication\n\n"
              << "Patrons\n-------\n"
              << "(5) Add patron\n(6) List patrons\n\n"
              << "Utility\n-------\n"
              << "(9) Help\n(0) Exit\n"
              << "\nChoice: ";
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}

void execute_cmd(int choice) {
    switch (choice) {
        case 1:
            add_publication();
            break;
        case 2:
            list_publications();
            break;
        case 3:
            check_out();
            break;
        case 4:
            check_in();
            break;
        case 5:
            add_patron();
            break;
        case 6:
            list_patrons();
            break;
        case 9:
            get_help();
            break;
        case 42:
            fill_library();
            break;
        default:
            break;
    }
}

void add_publication() {
    std::string title;
    std::string author;
    std::string copyright;
    std::string isbn;
    Genre genre;
    Media media;
    Age target_age;

    std::cout << "Title: ";
    std::cin >> title;
    std::cout << "Author: ";
    std::cin >> author;
    std::cout << "Copyright: ";
    std::cin >> copyright;
    std::cout << "ISBN: ";
    std::cin >> isbn;
    genre = get_genre();
    media = get_media();
    target_age = get_age();

    Publication pub(title, author, copyright, isbn, genre, media, target_age);
    Library::get_instance().add_publication(pub);
}

void list_publications() {
    Library & library = Library::get_instance();
    for (int i = 0; i < library.number_of_publications(); i++) {
        std::cout << i + 1 << ": " << library.publication_to_string(i);
    }
}

/* fix function */
void check_out() {
    int choice = 0, patron = 0;
    std::string name;
    std::string number;

    while (choice <= 0 || choice > Library::get_instance().number_of_publications()) {
        std::cout << "Which publication would you like to check out: \n";
        list_publications();
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();
    }

    while (patron <= 0 || patron > Library::get_instance().number_of_patrons()) {
        std::cout << "Which patron is checking out the publication: \n";
        list_patrons();
        std::cout << "Choice: ";
        std::cin >> patron;
    }
    
    Library::get_instance().check_out(choice - 1, patron - 1);
}

void check_in() {
    int choice;

    std::cout << "Which publication would you like to check in: \n";
    list_publications();
    std::cout << "Choice: ";
    std::cin >> choice;

    Library::get_instance().check_in(choice - 1);
}

void get_help() {
    std::cout << "This is a helpful message.\n";
}

void fill_library() {
    Library & library = Library::get_instance();

    Publication book1{"Test title", "Test Author", "Test Copyright", "10000000000",
                      fiction, periodicals, children}; 
    Publication art_of_peace{"The Art of Peace", "Morihei Ueshiba", "1992",
                             "0877738513", self_help, books, adult};
    Publication empty{"", "", "", "", nonfiction, audio, restricted};

    library.add_publication(book1);
    library.add_publication(art_of_peace);
    library.add_publication(empty);
}

void add_patron() {
    std::string name;
    std::string number;

    std::cout << "Enter name: ";
    getline(std::cin, name);
    std::cout << "Enter number: ";
    getline(std::cin, number);

    Patron patron{name, number};
    Library::get_instance().add_patron(patron);
}

void list_patrons() {
    Library & library = Library::get_instance();

    std::cout << "\nPatrons\n";
    for (int i = 0; i < library.number_of_patrons(); i++) {
        std::cout << i + 1 << ": " << library.patron_to_string(i) << '\n';
    }
}

Genre get_genre() {
    int choice;
    std::cout << "Genre: \n";
    std::cout << "(1) Fiction\n(2) Nonfiction\n(3) Self-help\n(4) Performance\n"
              << "Enter your numerical choice: ";
    std::cin >> choice;
    switch (choice) {
        case 1: return fiction;
        case 2: return nonfiction;
        case 3: return self_help;
        case 4: return performance;
        default: return fiction;
    }
}

Media get_media() {
    int choice;
    std::cout << "Media: \n";
    std::cout << "(1) Books\n(2) Periodicals\n(3) Newpapers\n(4) Audio\n(5) Video\n"
              << "Enter your numerical choice: ";
    std::cin >> choice;
    switch (choice) {
        case 1: return books;
        case 2: return periodicals;
        case 3: return newspapers;
        case 4: return audio;
        case 5: return video;
        default: return books;
    }
}

Age get_age() {
    int choice;
    std::cout << "Target age: \n";
    std::cout << "(1) Children\n(2) Teen\n(3) Adult\n(4) Restricted\n"
              << "Enter your numerical choice: ";
    std::cin >> choice;
    switch (choice) {
        case 1: return children;
        case 2: return teen;
        case 3: return adult;
        case 4: return restricted;
        default: return children;
    }
}
