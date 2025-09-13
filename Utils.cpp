//
// Created by vigna on 02/09/2025.
//

#include "Utils.h"

bool operator< (const Date &a, const Date &b) {
    if (a.year != b.year) return a.year < b.year;
    if (a.month != b.month) return a.month < b.month;
    return a.day < b.day;
}

bool operator==(const Date &a, const Date &b) {
    if (a.day == b.day && a.month == b.month && a.year == b.year)
        return true;
    return false;
}

Date incrementDate(Date date) {
    //casi: se il mese è 4, 6, 9, 11 e il giorno è 30, aggiorno mese successivo e giorno 1
    //      se il mese è 2 e giorno è 28, se anno % 4 == 0 aggiorna a 29, altrimenri aggiorno mese successivo e giorno 1
    //      se non è nessuno di questi e giorno è 31, aggiorna a mese successivo e giorno 1
    //      se il giorno è 31 e il mese è 12, aggiorna a 1/1 e anno +1
    //      altrimenti giorno +1
    Date newDate;

    if (date.day == 31) {
        if (date.month == 12)
            newDate = {1, 1, date.year + 1};
        else
            newDate = {1, date.month + 1, date.year};
    } else if (date.day == 30 && (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11))
        newDate = {1, date.month + 1, date.year};
    else if (date.day == 29 && date.month == 2)
        newDate = {1, 3, date.year};
    else if (date.day == 28 && date.month == 2) {
        if (date.year % 4 == 0)
            newDate = {29, 2, date.year};
        else
            newDate = {1, 3, date.year};
    }else
        newDate = {date.day + 1, date.month, date.year};

    return newDate;
}

Date decrementDate(Date date) {
    //casi: se giorno è 1, aggiorno mese precedente e giorno in base a nuovo mese
    //      se giorno è 1 e mese è 1, aggiorna a 31/12 e anno -1
    //      altrimenti giorno -1
    Date newDate;

    if (date.day == 1) {
        if (date.month == 1) {
            if (date.year == 2000)
                newDate = date;
            else
                newDate = {31, 12, date.year - 1};
        }else if (date.month == 5 || date.month == 7 || date.month == 10 || date.month == 12)
            newDate = {30, date.month - 1, date.year};
        else if (date.month == 3) {
            if (date.year % 4 == 0)
                newDate = {29, 2, date.year};
            else
                newDate = {28, 2, date.year};
        }else
            newDate = {31, date.month - 1, date.year};
    } else
        newDate = {date.day - 1, date.month, date.year};

    return newDate;
}

string labelToColor(Label label) {
    switch (label) {
        case Label::Generic:
            return "@C25● ";
        case Label::Fun:
            return "@C26● ";
        case Label::Sport:
            return "@C27● ";
        case Label::Light_Activity:
            return "@C28● ";
        case Label::Wellness:
            return "@C29● ";
        case Label::Work:
            return "@C30● ";
        case Label::Other:
            return "@C31● ";
        default:
            return "@C25● ";
    }
}

int labelToIndex(Label label) {
    switch (label) {
        case Label::Fun:
            return 1;
        case Label::Sport:
            return 2;
        case Label::Light_Activity:
            return 3;
        case Label::Wellness:
            return 4;
        case Label::Work:
            return 5;
        case Label::Other:
            return 6;
        default:
            return 0;
    }
}

Label indexToLabel(int i) {
    switch (i) {
        case 1:
            return Label::Fun;
        case 2:
            return Label::Light_Activity;
        case 3:
            return Label::Sport;
        case 4:
            return Label::Wellness;
        case 5:
            return Label::Work;
        case 6:
            return Label::Other;
        default:
            return Label::Generic;
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

        for (int i = 0; i < padding; i++)
            ct->b->add("");

        ct->b->textfont(FL_TIMES_BOLD);
        ct->b->textcolor(FL_LIGHT1);
        ct->b->textsize(20);
        string msg = sp + "        The register is empty";
        ct->b->add(msg.c_str());
        msg = sp + "Add your first activity to get started!";
        ct->b->add(msg.c_str());
    } else {
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

void revPopulateBrowser(context *ct) {
    ct->b->clear();

    if (ct->activities.empty()) {

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

        for (int i = 0; i < padding; i++)
            ct->b->add("");

        ct->b->textfont(FL_TIMES_BOLD);
        ct->b->textcolor(FL_LIGHT1);
        ct->b->textsize(20);
        string msg = sp + "        The register is empty";
        ct->b->add(msg.c_str());
        msg = sp + "Add your first activity to get started!";
        ct->b->add(msg.c_str());
    } else {
        ct->b->textfont(FL_TIMES);
        ct->b->textcolor(FL_BLACK);
        ct->b->textsize(21);

        for (const Activity& act : ct->activities) {
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

Register& getOrCreateRegister(context* ct, Date date) {
    bool found = false;

    for (auto& reg : ct->registers) {
        if (reg.getDate() == date)
            return reg;
    }

    Register newReg (date.day, date.month, date.year);
    ct->registers.push_back(newReg);
    return ct->registers.back();
}

void prevDay_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);
    Date newDate = decrementDate(ct->r->getDate());
    ct->dateBox->label(dateToString(newDate).c_str());

    ct->r = &getOrCreateRegister(ct, newDate);
    populateBrowser(ct);
}

void nextDay_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);
    Date newDate = incrementDate(ct->r->getDate());
    ct->dateBox->label(dateToString(newDate).c_str());

    ct->r = &getOrCreateRegister(ct, newDate);
    populateBrowser(ct);
}

void lineSelect_cb(Fl_Widget* w, void* data) {
    Fl_Multi_Browser* browser = static_cast<Fl_Multi_Browser *>(w);
    context* ct = static_cast<context *>(data);

    if (Fl::event_clicks()) {
        int line = browser->value();
        int index = (line - 1) / 2;                 //calculate the activity index into the register vector based on the line clicked
        if (ct->r->getVector().empty())
            return;
        ct->ps->act_index = index;
        Activity act;

        if (ct->originalFlag)
            act = ct->r->getVector()[index];
        else
            act = ct->activities[index];

        ct->ps->ititle->value(act.getTitle().c_str());
        ct->ps->idescr->value(act.getDescription().c_str());
        ct->ps->dh->value(act.getHours());
        ct->ps->dm->value(act.getMinutes());
        ct->ps->ds->value(act.getSeconds());
        ct->ps->label->value(labelToIndex(act.getLabel()));

        ct->newAct->child(5)->hide();
        ct->newAct->child(6)->hide();
        ct->newAct->child(8)->show();
        ct->newAct->child(9)->show();
        ct->newAct->show();
    }
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
}

void createNew_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);

    string texts[2] = {ct->ps->ititle->value(), ct->ps->idescr->value()};

    int ind = ct->ps->label->value();
    Label actLabel = indexToLabel(ind);

    Activity newActivity(texts[0],texts[1], ct->ps->dh->value(), ct->ps->dm->value(), ct->ps->ds->value(), actLabel);
    ct->r->addActivity(newActivity);
    addActivityInVector(ct, newActivity);

    if (ct->originalFlag) populateBrowser(ct);
    else revPopulateBrowser(ct);
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
        addActivityInVector(ct, newActivity);
        if (ct->originalFlag) populateBrowser(ct);
        else revPopulateBrowser(ct);
        int n = ct->r->getVector().size();
        Fl_Button* deleteB = new Fl_Button(945, 35 + (50*(n-1)), 50, 50, "X");
        ct->deleteg->add(deleteB);
        ct->deleteButtons[deleteB] = n-1;
        deleteB->callback(deleteButton_cb, ct);
    }
    ct->newAct->hide();
}

void addActivityInVector(context *ct, Activity act) {
    auto it = ct->activities.begin();
    bool found = false;
    while (it != ct->activities.end()) {
        if (it->getHours() < act.getHours()) {
            ct->activities.insert(it, act);
            return;
        }else if (it->getHours() == act.getHours() && it->getMinutes() < act.getMinutes()) {
            ct->activities.insert(it, act);
            return;
        }else if (it->getHours() == act.getHours() && it->getMinutes() == act.getMinutes() && it->getSeconds() < act.getSeconds()) {
            ct->activities.insert(it, act);
            return;
        }
        ++it;
    }
    ct->activities.insert(it, act);
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
    Activity act;
    if (ct->originalFlag) act = ct->r->getVector()[index];
    else act = ct->activities[index];
    string question = "Do you really want to remove the activity with title '" + act.getTitle() + "' ?";

    int choice = fl_choice(question.c_str(), "Cancel", "Confirm", 0);
    if (choice == 1) {
        if (ct->originalFlag) {
            ct->r->removeActivity(index);
            removeActivityInVector(ct, act);
            populateBrowser(ct);
        } else {
            int pos;
            for (int i = 0; i < n; i++) {
                if (strcmp(ct->r->getVector()[i].getTitle().c_str(), act.getTitle().c_str()) == 0 && strcmp(ct->r->getVector()[i].getDescription().c_str(), act.getDescription().c_str()) == 0)
                    pos = i;
            }
            ct->r->removeActivity(pos);
            removeActivityInVector(ct, act);
            revPopulateBrowser(ct);
        }

        auto it = ct->deleteButtons.end();
        --it;
        Fl_Button* last = static_cast<Fl_Button*>(ct->deleteg->child(n-1));
        ct->deleteg->remove(last);
        ct->deleteButtons.erase(it);
        delete last;

        ct->win->redraw();
    }
}

void removeActivityInVector(context *ct, Activity act) {
    auto it = ct->activities.begin();
    bool found = false;
    for (auto it = ct->activities.begin(); it != ct->activities.end(); ++it) {
        if (it->getTitle() == act.getTitle() && it->getDescription() == act.getDescription()) {
            ct->activities.erase(it);
            break;
        }
    }
}

void save_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);

    int n = ct->r->getVector().size();
    int index = ct->ps->act_index;
    //TODO errore importante nella rimozione dell'attività in vettore e registro. Gestire rimozione in base a flag di modo
    if (ct->originalFlag) {
        Activity act = ct->r->getVector()[index];
        ct->r->removeActivity(index);
        removeActivityInVector(ct, act);
    } else {
        int pos;
        for (int i = 0; i < n; i++) {
            if (strcmp(ct->r->getVector()[i].getTitle().c_str(), ct->activities[index].getTitle().c_str()) == 0 && strcmp(ct->r->getVector()[i].getDescription().c_str(), ct->activities[index].getDescription().c_str()) == 0)
                pos = i;
        }
        Activity act = ct->r->getVector()[pos];
        ct->r->removeActivity(pos);
        removeActivityInVector(ct, act);
    }

    auto it = ct->deleteButtons.end();
    --it;
    Fl_Button* last = static_cast<Fl_Button*>(ct->deleteg->child(n-1));
    ct->deleteg->remove(last);
    ct->deleteButtons.erase(it);
    delete last;

    createNew_cb(w, ct);

    ct->newAct->child(8)->hide();
    ct->newAct->child(9)->hide();
    ct->newAct->child(5)->show();
    ct->newAct->child(6)->show();
}

void modify_canc_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context *>(data);

    int choice = fl_choice("Delete all changes? All the changes will be lost", "Cancel", "Delete", 0);
    if (choice == 1) {
        ct->newAct->child(8)->hide();
        ct->newAct->child(9)->hide();
        ct->newAct->child(5)->show();
        ct->newAct->child(6)->show();
        ct->newAct->hide();
    }
}

void changeOrder_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context*>(data);
    Fl_Button* orderButton = static_cast<Fl_Button *>(w);

    if (ct->originalFlag) {
        ct->activities.clear();
        ct->allButtons[0]->deactivate();
        ct->allButtons[1]->deactivate();
        for (auto i = ct->r->getVector().rbegin(); i != ct->r->getVector().rend(); ++i)
            ct->activities.push_back(*i);

        revPopulateBrowser(ct);
        orderButton->label("Order by: shortest duration first");
        ct->originalFlag = false;
    } else {
        ct->activities.clear();
        ct->allButtons[0]->activate();
        ct->allButtons[1]->activate();
        populateBrowser(ct);
        orderButton->label("Order by: longest duration first");
        ct->originalFlag = true;
    }
    ct->b->redraw();
}

void visualizeByLabel_cb(Fl_Widget *w, void *data) {
    context* ct = static_cast<context*>(data);

    //usare una window con browser per la visualizzazione e basta
    //per la modifica, rimandare al browser principale

}
