#include <vector>
#include <string>
#include "publication.h"
#include "library.h"

Library::Library() {}

void Library::add_publication(Publication pub) {
    _publications.push_back(pub);
}

void Library::check_out(int publication_index, std::string name, std::string number) {
    _publications[publication_index].check_out(name, number);
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
