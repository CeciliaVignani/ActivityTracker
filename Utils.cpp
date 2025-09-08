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
    if (r.getVector().empty())
        b.add("Registro vuoto. Inserisci la tua prima attività!");
    else
        for (const Activity& act : r.getVector())
            b.add(getPreview(act).c_str());
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

void removeButton_cb(Fl_Widget *w, void *data){
    context* ct = static_cast<context*>(data);

    if (strcmp(w->label(),"Remove") == 0) {
        ct->b->resize(5, 35, 940,660);
        w->label("Cancel");
        ct->deleteg->show();
        for (auto wid : ct->allButtons)
            if (strcmp(wid->label(), "Cancel") != 0)
                wid->deactivate();

    }else if (strcmp(w->label(),"Cancel") == 0) {
        ct->b->resize(5, 35, 990,660);
        w->label("Remove");
        ct->deleteg->hide();
        for (auto wid : ct->allButtons)
            wid->activate();
    }
}

void deleteButton_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);
    Fl_Button* btn = static_cast<Fl_Button*>(w);

    int n = ct->r->getVector().size();
    int index = ct->deleteButtons[btn];
    auto act = ct->r->getVector()[index];
    string question = "Do you really want to remove the activity with title '" + act.getTitle() + "' ?";

    int choice = fl_choice(question.c_str(), "Confirm", "Cancel", 0);
    if (choice == 0) {
        ct->r->removeActivity(index);
        populateBrowser(*ct->r, *ct->b);
        auto it = ct->deleteButtons.end();
        --it;
        Fl_Button* last = static_cast<Fl_Button*>(ct->deleteg->child(n-1));
        ct->deleteg->remove(last);
        ct->deleteButtons.erase(it);
        delete last;

        ct->win->redraw();
    }
}
