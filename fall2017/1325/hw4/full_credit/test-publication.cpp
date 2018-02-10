#include <string>
#include <iostream>
#include "publication.h"

int main() {
    /*************************************
        test constructor and to_string
    *************************************/
    Publication book1{"Test title", "Test Author", "Test Copyright", "10000000000",
                      fiction, periodicals, children}; 
    std::string testbook1 = "\"Test title\" by Test Author, Test Copyright, " 
                            "(children fiction periodicals) ISBN: 10000000000\n";

    if (book1.to_string() != testbook1) {
        std::cerr << "Constructor or to_string not working... \n" 
                  << "Expected: \n" << testbook1
                  << "Actual: \n" << book1.to_string();
        return 1;
    }

    Publication art_of_peace{"The Art of Peace", "Morihei Ueshiba", "1992",
                             "0877738513", self_help, books, adult};
    std::string art_test = "\"The Art of Peace\" by Morihei Ueshiba, 1992, "
                           "(adult self-help books) ISBN: 0877738513\n";

    if (art_of_peace.to_string() != art_test) {
        std::cerr << "Constructor or to_string not working... \n" 
                  << "Expected: \n" << art_test
                  << "Actual: \n" << art_of_peace.to_string();
        return 1;
    }

    Publication empty{"", "", "", "", nonfiction, audio, restricted};
    std::string empty_str = "\"\" by , , (restricted nonfiction audio) ISBN: \n";
    if (empty.to_string() != empty_str) {
        std::cerr << "Constructor or to_string not working... \n" 
                  << "Expected: \n" << empty_str
                  << "Actual: \n" << empty.to_string();
        return 1;
    }
    /*************************************
           test checking in and out
    *************************************/
    book1.check_out("Name", "Number");
    if (!book1.is_checked_out()) {
        std::cerr << "Check_out not working... Expected: True"
                  << "\nActual: False\n";
        return 1;
    }
    book1.check_in();
    if (book1.is_checked_out()) {
        std::cerr << "Check_in not working... Expected: False"
                  << "\nActual: True\n";
        return 1;
    }

    std::string art_test_checked = art_test + "Checked out by Chris Jakins (8175555555)\n";
    art_of_peace.check_out("Chris Jakins", "8175555555");
    if (art_of_peace.to_string() != art_test_checked) {
        std::cerr << "to_string or check_out not working...\n"
                  << "Expected: \n" << art_test_checked
                  << "Actual: \n" << art_of_peace.to_string();
        return 1;
    }

    art_of_peace.check_in();
    if (art_of_peace.to_string() != art_test) {
        std::cerr << "to_string or check_in not working...\n"
                  << "Expected: \n" << art_test
                  << "Actual: \n" << art_of_peace.to_string();
        return 1;
    } 

    return 0;
}
