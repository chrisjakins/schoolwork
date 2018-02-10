#include <string>
#include <iostream>
#include <gtkmm.h>

#include "library.h"
#include "publication.h"
#include "patron.h"
#include "dialogs.h"

int menu();
int convertChoiceToInt(std::string);
void execute_cmd(int);

void list_publications();
void add_publication();
void check_out();
void check_in();

void add_patron();
void list_patrons();

void get_help();
void fill_library();

Genre get_genre();
Media get_media();
Age get_age();

int main(int argc, char * argv[]) {
    int choice;
    Gtk::Main kit(argc, argv);

    std::cout << "=================================\n"
              << "CSE1325 Library Management System\n"
              << "=================================\n\n";

    choice = menu();
    while (choice != 0) {
        if (choice == -1) {
            Dialogs::message("Invalid choice. Please enter an integer.", "Invalid");
        } else {
            execute_cmd(choice);
        }
        choice = menu();
    }
    
    /* take this out later */
    std::cout << "Thanks for using our Library Management System. Goodbye.\n";
    return 0;
}

int menu() {
    std::string menu_string = 
    R"(
    =================================
    CSE1325 Library Management System
    =================================

    Publications
    ------------
    (1) Add publication
    (2) List all publications
    (3) Check out publication
    (4) Check in publication
    
    Patrons
    -------
    (5) Add patron
    (6) List patrons
    
    Utility
    -------
    (9) Help
    (0) Exit)";
    
    return convertChoiceToInt(Dialogs::input(menu_string, "Menu", "Choice", "0"));
}

int convertChoiceToInt(std::string response) {
    if (response[0] <= '9' && response[0] >= '0') {
        return std::stoi(response);
    } else {
        return -1;
    }
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
            Dialogs::message("Invalid choice.", "Invalid");
            break;
    }
}

void add_publication() {
    Genre genre;
    Media media;
    Age target_age;

    std::vector<std::string> labels = {"Title", "Author", "Copyright", "ISBN"};
    std::vector<std::string> entries;
    entries = Dialogs::multiInput("Add publication", labels);
    genre = get_genre();
    media = get_media();
    target_age = get_age();

    Publication pub(entries[0], entries[1], entries[2], entries[3], genre, media, target_age);
    Library::get_instance().add_publication(pub);
}

void list_publications() {
    std::string msg = Library::get_instance().library_to_string();
    Dialogs::message(msg, "Publications");
}

void check_out() {
    int choice = 0, patron = 0;

    while (choice <= 0 || choice > Library::get_instance().number_of_publications()) {
        std::string publications = Library::get_instance().library_to_string();
        choice = convertChoiceToInt(Dialogs::input(publications, "Choose publication", "#"));
    }

    while (patron <= 0 || patron > Library::get_instance().number_of_patrons()) {
        std::string patrons = Library::get_instance().patrons_to_string();
        patron = convertChoiceToInt(Dialogs::input(patrons, "Choose Patron", "#"));
    }
    
    Library::get_instance().check_out(choice - 1, patron - 1);
}

void check_in() {
    int choice;

    while (choice <= 0 || choice > Library::get_instance().number_of_publications()) {
        std::string publications = Library::get_instance().library_to_string();
        choice = convertChoiceToInt(Dialogs::input(publications, "Choose publication", "#"));
    }

    Library::get_instance().check_in(choice - 1);
}

void get_help() {
    Dialogs::message("This is a helpful message.", "Help");
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
    std::vector<std::string> labels = {"Name", "Number"};
    std::vector<std::string> patron_info = Dialogs::multiInput("Add patron", labels);

    Patron patron{patron_info[0], patron_info[1]};
    Library::get_instance().add_patron(patron);
}

void list_patrons() {
    std::string msg = Library::get_instance().patrons_to_string();
    Dialogs::message(msg, "Patrons");
}

Genre get_genre() {
    int choice;
    std::string message = "What genre is your publication: ";
    std::vector<std::string> buttons = {"Fiction", "Nonfiction", "Self-help", "Performance"};
    
    choice = Dialogs::question(message, "Genre Selection", buttons) + 1;

    std::cout << choice << "\n";
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
    std::string message = "What media is your publication: ";
    std::vector<std::string> buttons = {"Books", "Periodicals", "Newspapers",
                                        "Audio", "Video"};
    
    choice = Dialogs::question(message, "Media Selection", buttons) + 1;
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
    std::string message = "What Age group is your publication for: ";
    std::vector<std::string> buttons = {"Children", "Teen", "Adult", "Restricted"};
    
    choice = Dialogs::question(message, "Age Group Selection", buttons) + 1;
    switch (choice) {
        case 1: return children;
        case 2: return teen;
        case 3: return adult;
        case 4: return restricted;
        default: return children;
    }
}
