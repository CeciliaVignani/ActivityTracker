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
    context* ct = static_cast<context*>(data);

    Fl_Input* titleInput = static_cast<Fl_Input*>(ct->newAct->child(0));
    titleInput->value("");
    Fl_Multiline_Input* descriptionInput = static_cast<Fl_Multiline_Input *>(ct->newAct->child(1));
    descriptionInput->value("");
    Fl_Spinner* hoursInput = static_cast<Fl_Spinner *>(ct->newAct->child(2));
    hoursInput->value(0);
    Fl_Spinner* minutesInput = static_cast<Fl_Spinner *>(ct->newAct->child(3));
    minutesInput->value(0);
    Fl_Spinner* secondsInput = static_cast<Fl_Spinner *>(ct->newAct->child(4));
    secondsInput->value(0);
    ct->newAct->show();

    ct->ps = new parameters{titleInput, descriptionInput, hoursInput, minutesInput, secondsInput};

    ct->newAct->child(5)->callback(createNew_cb, ct);
    ct->newAct->child(6)->callback(cancelNew_cb, ct);
}

void createNew_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);

    string texts[2] = {ct->ps->it->value(), ct->ps->id->value()};

    Activity newActivity(texts[0], texts[1], ct->ps->dh->value(), ct->ps->dm->value(), ct->ps->ds->value());
    ct->r->addActivity(newActivity);
    populateBrowser(*ct->r, *ct->b);
    int n = ct->r->getVector().size();
    Fl_Button* deleteB = new Fl_Button(945, 35 + (50*(n-1)), 50, 50, "X");
    ct->deleteg->add(deleteB);
    ct->deleteButtons[deleteB] = n-1;
    deleteB->callback(deleteButton_cb, ct);

    ct->newAct->hide();
}

void cancelNew_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);

    int choice = fl_choice("Are you sure you want to cancel the creation of a new activity? All set data will be lost.\nInstead, you can create an empty activity and modify it in future", "Delete", "Create empty", 0);
    if (choice == 1) {
        Activity newActivity;
        ct->r->addActivity(newActivity);
        populateBrowser(*ct->r, *ct->b);
        int n = ct->r->getVector().size();
        Fl_Button* deleteB = new Fl_Button(945, 35 + (50*(n-1)), 50, 50, "X");
        ct->deleteg->add(deleteB);
        ct->deleteButtons[deleteB] = n-1;
        deleteB->callback(deleteButton_cb, ct);
    }
    ct->newAct->hide();
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