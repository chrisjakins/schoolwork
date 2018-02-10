#include <gtkmm.h>

#include "main_window.h"

int main(int argc, char * argv[]) {
    auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1324.lms.jakins");
    Main_window win{};

    return app->run(win);
}
