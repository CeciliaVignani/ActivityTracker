//
// Created by vigna on 02/09/2025.
//

#include "Utils.h"

bool operator< (const Date &a, const Date &b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

string labelToColor(Label label) {
    switch (label) {
        case Label::Generic:
            return "@C25●";
        case Label::Fun:
            return "@C26●";
        case Label::Sport:
            return "@C27●";
        case Label::Light_Activity:
            return "@C28●";
        case Label::Wellness:
            return "@C29●";
        case Label::Work:
            return "@C30●";
        case Label::Other:
            return "@C31●";
    }
}

void populateBrowser(context* ct) {
    ct->b->clear();

    if (ct->r->getVector().empty()) {

        int browser_h = ct->b->h();
        int line_h = ct->b->textsize();
        int total_lines = browser_h / line_h;
        int padding = total_lines / 3;
        int browser_w = ct->b->w();
        int char_w = ct->b->textsize();
        int spaces = browser_w / char_w;
        string sp = "";
        for (int i = 0; i < spaces; i++)
            sp += " ";

        for (int i = 0; i < padding; i++) {
            ct->b->add("");
        }

        ct->b->textfont(FL_TIMES_BOLD);
        ct->b->textcolor(FL_LIGHT1);
        ct->b->textsize(20);
        string msg = sp + "        The register is empty";
        ct->b->add(msg.c_str());
        msg = sp + "Add your first activity to get started!";
        ct->b->add(msg.c_str());
    }
    else {
        ct->b->textfont(FL_TIMES);
        ct->b->textcolor(FL_BLACK);
        ct->b->textsize(21);

        for (const Activity& act : ct->r->getVector()) {
            string title = "@b" + labelToColor(act.getLabel()) + act.getTitle();
            string descr = "   " + getPreview(act) + " ---    Duration: " + timeToString(act.getTime());

            ct->b->add(title.c_str());
            ct->b->add(descr.c_str());
        }
    }
}

string getPreview (const Activity& a, int maxLen) {
    string descr = a.getDescription();
    if (descr.length() > maxLen)
        descr = descr.substr(0, maxLen) + "...";
    return descr;
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
            break;
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

    populateBrowser(ct);
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
        populateBrowser(ct);
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
        populateBrowser(ct);
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
