#include "dialogs.h"

// A message is like cout, simply displaying information to the user
void Dialogs::message(string msg, string title) {
    Gtk::MessageDialog *dialog = new Gtk::MessageDialog(title);
    dialog->set_secondary_text(msg, true);
    dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete dialog;
}

// A question is a message that allows the user to respond with a button
int Dialogs::question(string msg, string title,
             vector<string> buttons) {
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);

    Gtk::Label *label = new Gtk::Label(msg);
    dialog->get_content_area()->pack_start(*label);
    label->show();

    for(unsigned int i=0; i < buttons.size(); ++i) dialog->add_button(buttons[i], i);

    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete label;
    delete dialog;

    return result;
}

// allow multiple Gtk::Entry fields in one dialog
vector<string> Dialogs::multiInput(string title, vector<string> input_strings) {
    Gtk::Dialog * dialog = new Gtk::Dialog();
    dialog->set_title(title);

    vector<Gtk::Label *> labels;
    vector<Gtk::Entry *> entries;
    for (unsigned int i = 0; i < input_strings.size(); i++) {
        Gtk::Label * label = new Gtk::Label(input_strings[i]);
        dialog->get_content_area()->pack_start(*label);
        label->show();
        labels.push_back(label); 
        
        Gtk::Entry * entry = new Gtk::Entry{};
        entry->set_max_length(75);
        entry->show();
        dialog->get_vbox()->pack_start(*entry);
        entries.push_back(entry);
    }
    dialog->add_button("Done", 0);
    dialog->set_default_response(1);

    dialog->run();
    
    vector<string> output; 
    for (unsigned int i = 0; i < entries.size(); i++) {
        output.push_back(entries[i]->get_text());
    }

    dialog->close();
    while (Gtk::Main::events_pending()) Gtk::Main::iteration();

    for (unsigned int i = 0; i < entries.size(); i++) {
        delete labels[i];
        delete entries[i];
    }
    delete dialog;

    return output;
}

// A request for a line of text input
string Dialogs::input(string msg, string title, string default_text, 
             string cancel_text) {
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);

    Gtk::Label *label = new Gtk::Label(msg);
    dialog->get_content_area()->pack_start(*label);
    label->show();

    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->set_default_response(1);

    Gtk::Entry *entry = new Gtk::Entry{};
    entry->set_text(default_text);
    entry->set_max_length(50);
    entry->show();
    dialog->get_vbox()->pack_start(*entry);

    int result = dialog->run();
    string text = entry->get_text();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete entry;
    delete label;
    delete dialog;

    if (result == 1)
        return text;
    else
        return cancel_text;
}

// Display an image from a disk file
void Dialogs::image(string filename, string title, string msg) {
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);

    Gtk::Label *label = new Gtk::Label(msg);
    dialog->get_content_area()->pack_start(*label);
    label->show();

    dialog->add_button("Close", 0);
    dialog->set_default_response(0);

    Gtk::Image *image = new Gtk::Image{filename};
    image->show();
    dialog->get_vbox()->pack_start(*image);

    dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete image;
    delete label;
    delete dialog;

    return;
}
