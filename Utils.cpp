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

    ct->ps->ititle->value("");
    ct->ps->idescr->value("");
    ct->ps->dh->value(0);
    ct->ps->dm->value(0);
    ct->ps->ds->value(0);
    ct->ps->label->value(0);
    ct->newAct->show();

    Fl_Button* createB = static_cast<Fl_Button *>(ct->newAct->child(5));
    createB->callback(createNew_cb, ct);
    Fl_Button* cancelB = static_cast<Fl_Button *>(ct->newAct->child(6));
    cancelB->callback(cancelNew_cb, ct);

}

void createNew_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);

    string texts[2] = {ct->ps->ititle->value(), ct->ps->idescr->value()};
    Label actLabel = Label::Generic;

    int ind = ct->ps->label->value();
    switch (ind) {
        case 1:
            actLabel = Label::Fun;
        case 2:
            actLabel = Label::Light_Activity;
            break;
        case 3:
            actLabel = Label::Sport;
            break;
        case 4:
            actLabel = Label::Wellness;
            break;
        case 5:
            actLabel = Label::Work;
            break;
        case 6:
            actLabel = Label::Other;
    }

    Activity newActivity(texts[0],texts[1], ct->ps->dh->value(), ct->ps->dm->value(), ct->ps->ds->value(), actLabel);
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

    int choice = fl_choice(question.c_str(), "Cancel", "Confirm", 0);
    if (choice == 1) {
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

void visualizeByLabel_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context*>(data);


}
