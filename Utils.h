//
// Created by vigna on 02/09/2025.
//

#ifndef ACTIVITYTRACKER_UTILS_H
#define ACTIVITYTRACKER_UTILS_H

#include <string>
#include "Activity.h"
#include "Register.h"
#include <FL/Fl_Browser.H>

using namespace std;

bool operator< (const Date& a, const Date& b);

void populateBrowser(const Register& r, Fl_Browser& b);
string getPreview (const Activity& a, int maxLen = 30);

void newAct_cb(Fl_Widget* w, void* data);



#endif //ACTIVITYTRACKER_UTILS_H