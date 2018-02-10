#include <iostream>
#include <string>
#include "library.h"
#include "publication.h"
#include "patron.h"

int main() {
    /*******************************
             Add publication
    *******************************/
    Publication book1{"Test title", "Test Author", "Test Copyright", "10000000000",
                      fiction, periodicals, children}; 
    Publication art_of_peace{"The Art of Peace", "Morihei Ueshiba", "1992",
                             "0877738513", self_help, books, adult};
    Publication empty{"", "", "", "", nonfiction, audio, restricted};
    Library & library = Library::get_instance();

    library.add_publication(book1);
    library.add_publication(art_of_peace);
    library.add_publication(empty);

    /*******************************
           List publications
    *******************************/
    if (library.number_of_publications() != 3) {
        std::cerr << "Problem with add_publication... Expected 3, Actual"
                  << library.number_of_publications();
        return 1;
    }

    std::string testbook1 = "\"Test title\" by Test Author, Test Copyright, " 
                            "(children fiction periodicals) ISBN: 10000000000\n";

    if (library.publication_to_string(0) != testbook1) {
        std::cerr << "Constructor or to_string not working... \n" 
                  << "Expected: \n" << testbook1
                  << "Actual: \n" << library.publication_to_string(0);
        return 1;
    }

    std::string art_test = "\"The Art of Peace\" by Morihei Ueshiba, 1992, "
                           "(adult self-help books) ISBN: 0877738513\n";

    if (library.publication_to_string(1) != art_test) {
        std::cerr << "To_string not working... \n" 
                  << "Expected: \n" << art_test
                  << "Actual: \n" << library.publication_to_string(1);
        return 1;
    }

    std::string empty_str = "\"\" by , , (restricted nonfiction audio) ISBN: \n";
    if (library.publication_to_string(2) != empty_str) {
        std::cerr << "Constructor or to_string not working... \n" 
                  << "Expected: \n" << empty_str
                  << "Actual: \n" << library.publication_to_string(2);
        return 1;
    }

    /*******************************
           Check-out/-in
    *******************************/
    Patron patron1{"Chris Jakins", "8175555555"};
    std::string art_test_checked = art_test + "Checked out by Chris Jakins (8175555555)\n";
    library.check_out(1, patron1);
    if (library.publication_to_string(1) != art_test_checked) {
        std::cerr << "to_string or check_out not working...\n"
                  << "Expected: \n" << art_test_checked
                  << "Actual: \n" << library.publication_to_string(1);
        return 1;
    }

    library.check_in(1);
    if (library.publication_to_string(1) != art_test) {
        std::cerr << "to_string or check_in not working...\n"
                  << "Expected: \n" << art_test
                  << "Actual: \n" << library.publication_to_string(1);
        return 1;
    } 

    /*******************************
          Patron functionality
    *******************************/
    std::string expected_patron{"John Snow (18003232323)"};
    Patron patron2;
    Patron patron3{"John Snow", "18003232323"};
    library.add_patron(patron1);
    library.add_patron(patron2);
    library.add_patron(patron3);
    
    if (library.patron_to_string(2) != expected_patron) {
        std::cerr << "add_patron or list_patrons not working...\n"
                  << "Expected: \n" << expected_patron
                  << "Actual: \n" << library.patron_to_string(2);
        return 1;
    }
    return 0;
}
