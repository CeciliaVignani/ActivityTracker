//
// Created by vigna on 02/09/2025.
//

#include "Utils.h"

bool operator< (const Date &a, const Date &b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

void populateBrowser(const Register& r, Fl_Browser& b) {
    b.clear();
    for (const Activity& act : r.getVector()) {
        b.add(getPreview(act).c_str());
    }
}

string getPreview (const Activity& a, int maxLen) {
    string descr = a.getDescription();
    if (descr.length() > maxLen)
        descr = descr.substr(0, maxLen) + "...";
    return a.getTitle() + " - " + descr;
}

void newAct_cb(Fl_Widget *w, void *data) {
    Fl_Browser* browser = static_cast<Fl_Browser*>(data);
    //TODO implementare callback
}

void removeButton_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context*>(data);

    ct->b->resize(5, 35, 940,660);
    w->label("Cancel");
    ct->deleteg->show();

    ct->win->redraw();
    //TODO implement callback for button cancel
}

