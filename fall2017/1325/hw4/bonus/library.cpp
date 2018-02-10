#include <iostream>
#include <vector>
#include <string>
#include "publication.h"
#include "library.h"
#include "patron.h"

Library::Library() {}

void Library::add_publication(Publication pub) {
    _publications.push_back(pub);
}

void Library::check_out(int publication_index, int patron_index) {
    _publications[publication_index].check_out(_patrons[patron_index]);
}

void Library::check_in(int publication_index) {
    _publications[publication_index].check_in();
}

std::string Library::publication_to_string(int publication_index) {
    return _publications[publication_index].to_string();
}

int Library::number_of_publications() {
    return _publications.size();
}

void Library::add_patron(Patron & patron) {
    _patrons.push_back(patron);
}

std::string Library::patron_to_string(int index) {
    return _patrons[index].to_string();
}

int Library::number_of_patrons() {
    return _patrons.size();
}
