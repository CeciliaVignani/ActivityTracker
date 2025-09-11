//
// Created by vigna on 02/09/2025.
//

#ifndef ACTIVITYTRACKER_UTILS_H
#define ACTIVITYTRACKER_UTILS_H

#include <map>
#include <string>
#include "Activity.h"
#include "Register.h"
#include <FL/Fl.H>
#include <FL/Fl_Multi_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Choice.H>

using namespace std;

struct parameters {
    Fl_Input* ititle;
    Fl_Multiline_Input* idescr;
    Fl_Spinner* dh;
    Fl_Spinner* dm;
    Fl_Spinner* ds;
    Fl_Choice* label;
};

struct context {
    Register *r;
    Fl_Window* win;
    Fl_Multi_Browser* b;
    Fl_Group* deleteg;
    vector<Fl_Widget*> allButtons;
    map<Fl_Button*, int> deleteButtons;
    Fl_Window* newAct;
    parameters* ps;
};

bool operator< (const Date& a, const Date& b);
string labelToColor(Label label);

void populateBrowser(context* ct);
string getPreview (const Activity& a, int maxLen = 30);

void newAct_cb(Fl_Widget* w, void* data);
void createNew_cb(Fl_Widget* w, void* data);
void cancelNew_cb(Fl_Widget* w, void* data);
void removeButton_cb(Fl_Widget* w, void* data);
void deleteButton_cb(Fl_Widget* w, void* data);
void visualizeByLabel_cb(Fl_Widget* w, void* data);



#endif //ACTIVITYTRACKER_UTILS_H