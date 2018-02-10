#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include <string>

#include "library.h"
#include "publication.h"
#include "patron.h"

class Main_window : public Gtk::Window {
    public:
        Main_window();
        virtual ~Main_window();
    protected:
        void add_pub();
        void list_pub();
        void add_patron();
        void list_patron();
        void check_out();
        void check_in();
        void help();
        
        void on_quit();
    private:
        Media get_media();
        Age get_age();
        Genre get_genre();
        int convertChoiceToInt(std::string);
};
#endif
