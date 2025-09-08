//
// Created by vigna on 02/09/2025.
//

#ifndef ACTIVITYTRACKER_UTILS_H
#define ACTIVITYTRACKER_UTILS_H

#include <map>
#include <string>
#include "Activity.h"
#include "Register.h"
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>

using namespace std;

struct context {
    Register *r;
    Fl_Window* win;
    Fl_Browser* b;
    Fl_Group* deleteg;
    vector<Fl_Widget*> allButtons;
    map<Fl_Button*, int> deleteButtons;
};

bool operator< (const Date& a, const Date& b);

void populateBrowser(const Register& r, Fl_Browser& b);
string getPreview (const Activity& a, int maxLen = 30);

void newAct_cb(Fl_Widget* w, void* data);
void removeButton_cb(Fl_Widget* w, void* data);
void deleteButton_cb(Fl_Widget* w, void* data);



#endif //ACTIVITYTRACKER_UTILS_H