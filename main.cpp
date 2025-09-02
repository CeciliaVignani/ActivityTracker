#include <iostream>
#include <cstdlib>
#include <ctime>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "Activity.h"
#include "Register.h"

int main() {
    Fl_Window *window = new Fl_Window(200, 100, "Test FLTK");
    Fl_Box *box = new Fl_Box(20, 20, 160, 60, "Ciao FLTK!");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(16);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show();
    return Fl::run();

    return 0;
}