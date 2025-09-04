#include <iostream>
#include <ctime>
#include <map>
#include <FL/Fl_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include "Activity.h"
#include "Register.h"
#include "Utils.h"

int main() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    int day = local->tm_mday;
    int month = local->tm_mon +1;
    int year = local->tm_year + 1900;
    Date today;
    today.day = day;
    today.month = month;
    today.year = year;

    Register reg(day, month, year);
    Fl_Window window (1000, 750, "ACTIVITY TRACKER");
    string dateLabel = dateToString(today);
    Fl_Box* dateBox = new Fl_Box(5, 5, 990, 30, dateLabel.c_str());
    dateBox->labelfont(FL_BOLD);
    Fl_Browser* browser = new Fl_Browser(5, 35, 990, 660);
    browser->add("Registro vuoto. Inserisci la tua prima attività!");

    Fl_Button* prevDay = new Fl_Button(5,5, 60, 30, "<<");
    Fl_Button* nextDay = new Fl_Button(935, 5, 60, 30, ">>");
    prevDay->align(FL_ALIGN_CENTER);
    prevDay->labelfont(FL_BOLD);
    nextDay->align(FL_ALIGN_CENTER);
    nextDay->labelfont(FL_BOLD);
    Fl_Button* newAct = new Fl_Button(5, 695, 247, 50, "New");
    Fl_Button* removeAct = new Fl_Button(252, 695, 248, 50, "Remove");
    Fl_Button* labelFilter = new Fl_Button (500, 695, 248, 50, "Filter by Label");
    Fl_Button* orderBy = new Fl_Button (748, 695, 247, 50, "Order by:");
    newAct->align(FL_ALIGN_CENTER);
    removeAct->align(FL_ALIGN_CENTER);
    labelFilter->align(FL_ALIGN_CENTER);
    orderBy->align(FL_ALIGN_CENTER);
    newAct->callback(newAct_cb, browser);
    //TODO implementare callback tasti

    window.end();
    window.show();
    return Fl::run();
}