#include <gtkmm.h>

#include "main_window.h"
#include "dialogs.h"
#include "library.h"
#include "publication.h"
#include "patron.h"

/* TODO temporary */
Genre get_genre();
Media get_media();
Age get_age();
int convertChoiceToInt(std::string);

Main_window::Main_window() {
    set_default_size(600, 400);

    Gtk::Box * vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    /* Menu bar */
    Gtk::MenuBar * menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    /*****************
           FILE
    *****************/
    Gtk::MenuItem * menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu * filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    /* quit */
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_quit)); 
    filemenu->append(*menuitem_quit);

    /*****************
       PUBLICATIONS
    *****************/
    Gtk::MenuItem * menuitem_pub = Gtk::manage(new Gtk::MenuItem("_Publications", true));
    menubar->append(*menuitem_pub);
    Gtk::Menu * pubmenu = Gtk::manage(new Gtk::Menu());
    menuitem_pub->set_submenu(*pubmenu);

    /* add publication */
    Gtk::MenuItem * menuitem_add = Gtk::manage(new Gtk::MenuItem("_Add Publication", true));
    menuitem_add->signal_activate().connect(sigc::mem_fun(*this, &Main_window::add_pub)); 
    pubmenu->append(*menuitem_add);

    /* list publications */
    Gtk::MenuItem * menuitem_listpub = Gtk::manage(new Gtk::MenuItem("_List Publications", true));
    menuitem_listpub->signal_activate().connect(sigc::mem_fun(*this, &Main_window::list_pub));
    pubmenu->append(*menuitem_listpub);

    /* check out */
    Gtk::MenuItem * menuitem_cout = Gtk::manage(new Gtk::MenuItem("Check _Out", true));
    menuitem_cout->signal_activate().connect(sigc::mem_fun(*this, &Main_window::check_out));
    pubmenu->append(*menuitem_cout);

    /* check in */
    Gtk::MenuItem * menuitem_cin = Gtk::manage(new Gtk::MenuItem("Check _In", true));
    menuitem_cin->signal_activate().connect(sigc::mem_fun(*this, &Main_window::check_in));
    pubmenu->append(*menuitem_cin);


    /*****************
          PATRONS
    *****************/
    Gtk::MenuItem * menuitem_patron = Gtk::manage(new Gtk::MenuItem("Patrons", true));
    menubar->append(*menuitem_patron);
    Gtk::Menu * patronmenu = Gtk::manage(new Gtk::Menu());
    menuitem_patron->set_submenu(*patronmenu);

    /* add patron */
    Gtk::MenuItem * menuitem_addpat = Gtk::manage(new Gtk::MenuItem("Add Patron", true));
    menuitem_addpat->signal_activate().connect(sigc::mem_fun(*this, &Main_window::add_patron));
    patronmenu->append(*menuitem_addpat);    

    /* list patrons */
    Gtk::MenuItem * menuitem_listpat = Gtk::manage(new Gtk::MenuItem("List patrons", true));
    menuitem_listpat->signal_activate().connect(sigc::mem_fun(*this, &Main_window::list_patron));
    patronmenu->append(*menuitem_listpat);

    /*****************
           HELP
    *****************/
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    /*about */
    Gtk::MenuItem *menuitem_abt = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_abt->signal_activate().connect(sigc::mem_fun(*this, &Main_window::help));
    helpmenu->append(*menuitem_abt);

    /* set up toolbar here later for bonus */
    
    /* consider having list publications as default on screen for extreme bonus*/

    vbox->show_all();
}

Main_window::~Main_window() { }

void Main_window::add_pub() {
    int genre;
    int media;
    int age;
    std::vector<std::string> labels = {"Title", "Author", "Copyright", "ISBN"};
    std::vector<std::string> user_entries;

    user_entries = Dialogs::addPub("Add publiication", labels, &genre, &media, &age);
    
    Publication pub(user_entries[0], user_entries[1], user_entries[2], 
                    user_entries[3], genre, media, age);
    Library::get_instance().add_publication(pub);
}

void Main_window::list_pub() {
    Dialogs::message(Library::get_instance().library_to_string(), "Publications");
}

void Main_window::add_patron() {
    std::vector<std::string> labels = {"Name", "Number"};
    std::vector<std::string> patron_info = Dialogs::multiInput("Add patron", labels);

    Patron patron{patron_info[0], patron_info[1]};
    Library::get_instance().add_patron(patron);
}

void Main_window::list_patron() {
    Dialogs::message(Library::get_instance().patrons_to_string(), "Patrons");
}

void Main_window::check_out() {
    int choice = -1, patron = -1;

    while (choice < 0 || choice > Library::get_instance().number_of_publications()) {
        std::string publications = Library::get_instance().library_to_string();
        choice = convertChoiceToInt(Dialogs::input(publications, "Choose publication", "#"));
    }
    
    if (choice == 0)
        return;

    while (patron < 0 || patron > Library::get_instance().number_of_patrons()) {
        std::string patrons = Library::get_instance().patrons_to_string();
        patron = convertChoiceToInt(Dialogs::input(patrons, "Choose Patron", "#"));
    }

    if (patron == 0) 
        return;
    
    Library::get_instance().check_out(choice - 1, patron - 1);
}

void Main_window::check_in() {
    int choice;

    while (choice < 0 || choice > Library::get_instance().number_of_publications()) {
        std::string publications = Library::get_instance().library_to_string();
        choice = convertChoiceToInt(Dialogs::input(publications, "Choose publication", "#"));
    }

    if (choice == 0)
        return;

    Library::get_instance().check_in(choice - 1);
}

void Main_window::help() {
    Dialogs::message("This is a helpful message", "Help");
}

void Main_window::on_quit() {
    close();
}

Genre Main_window::get_genre() {
    int choice;
    std::string message = "What genre is your publication: ";
    std::vector<std::string> buttons = {"Fiction", "Nonfiction", "Self-help", "Performance"};
    
    choice = Dialogs::question(message, "Genre Selection", buttons) + 1;

    switch (choice) {
        case 1: return fiction;
        case 2: return nonfiction;
        case 3: return self_help;
        case 4: return performance;
        default: return fiction;
    }
}

Media Main_window::get_media() {
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

Age Main_window::get_age() {
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

int Main_window::convertChoiceToInt(std::string response) {
    if (response[0] <= '9' && response[0] >= '0') {
        return std::stoi(response);
    } else {
        return 0;
    }
}
