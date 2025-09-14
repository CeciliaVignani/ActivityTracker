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
    int act_index;
};

struct context {
    Register *r;
    Fl_Window* win;
    Fl_Box* dateBox;
    Fl_Multi_Browser* b;
    Fl_Group* deleteg;
    vector<Fl_Widget*> allButtons;
    map<Fl_Button*, int> deleteButtons;
    Fl_Window* newAct;
    parameters* ps;
    bool originalFlag = true;
    vector<Activity> activities;
    vector<Register> registers;
    Fl_Window* filter;
    Fl_Multi_Browser* bFilter;
};

bool operator< (const Date& a, const Date& b);
bool operator ==(const Date& a, const Date &b);
Date incrementDate(Date date);
Date decrementDate(Date date);
string labelToColor(Label label);
int labelToIndex (Label label);
Label indexToLabel(int i);

void populateBrowser(context* ct);
void revPopulateBrowser(context* ct);
void populateByLabel(context* ct, Label label);
string getPreview (const Activity& a, int maxLen = 30);
Register& getOrCreateRegister(context* ct, Date date);

void prevDay_cb(Fl_Widget* w, void* data);
void nextDay_cb(Fl_Widget* w, void* data);
void lineSelect_cb(Fl_Widget* w, void* data);
void newAct_cb(Fl_Widget* w, void* data);
void createNew_cb(Fl_Widget* w, void* data);
void cancelNew_cb(Fl_Widget* w, void* data);
void addActivityInVector(context* ct, Activity act);
void removeButton_cb(Fl_Widget* w, void* data);
void deleteButton_cb(Fl_Widget* w, void* data);
void removeActivityInVector(context* ct, Activity act);
void save_cb(Fl_Widget* w, void* data);
void modify_canc_cb(Fl_Widget* w, void* data);
void changeOrder_cb(Fl_Widget* w, void* data);
void visualizeByLabel_cb(Fl_Widget* w, void* data);
void filterLineSelect_cb(Fl_Widget* w, void* data);



#endif //ACTIVITYTRACKER_UTILS_H