//
// Created by vigna on 11/08/2025.
//

#include <iostream>
#include "Activity.h"

string labelToString(const Label &l) {
    switch (l) {
        case Label::Sport: return "Sport";
        case Label::Wellness: return "Wellness";
        case Label::Light_Activity: return "Light Activity";
        case Label::Fun: return "Fun";
        case Label::Work: return "Work";
        case Label::Other: return "Other";
    }
    return "Generic";
}

string timeToString(const Act::Time &t) {
    string stringTime;
    if (t.hours < 10)
        stringTime = "0" + to_string(t.hours);
    else stringTime = to_string(t.hours);
    if (t.minutes < 10)
        stringTime = stringTime + ":0" + to_string(t.minutes);
    else stringTime = stringTime + ":" + to_string(t.minutes);
    if (t.seconds < 10)
        stringTime = stringTime + ":0" + to_string(t.seconds);
    else stringTime = stringTime + ":" + to_string(t.seconds);
    return stringTime;
}


Activity::Activity() {
    title = "Untitled activity";
    description = "";
    setTime(0,0,0);
    label = Label::Generic;
    actTime.hours = 0;
    actTime.minutes = 0;
    actTime.seconds = 0;
}

Activity::Activity(const string& title, const string& description, int hrs, int mins, int secs, Label lab) {
    this->title = title;
    this->description = description;
    setTime(hrs, mins, secs);
    label = lab;
}

void Activity::setTitle(const string& newTitle) {
    title = newTitle;
}

void Activity::setDescription(const string& newDescr) {
    description = newDescr;
}

void Activity::setLabel(Label l) {
    label = l;
}


void Activity::setTime(int h, int min, int sec, bool mess) {
    if (!setHours(h) && mess)
        cerr << "Invalid value for hours" << endl;
    if (!setMinutes(min) && mess)
        cerr << "Invalid value for minutes" << endl;
    if (!setSeconds(sec) && mess)
        cerr << "Invalid value for hours" << endl;
}


bool Activity::setHours(int h) {
    if (h < 0 || h > 23) {
        actTime.hours = 0;
        return false;
    }
    actTime.hours = h;
    return true;
}


bool Activity::setMinutes(int m) {
    if (m < 0 || m > 59) {
        actTime.minutes = 0;
        return false;
    }
    actTime.minutes = m;
    return true;
}

bool Activity::setSeconds(int s) {
    if (s < 0 || s > 59) {
        actTime.seconds = 0;
        return false;
    }
    actTime.seconds = s;
    return true;
}

string Activity::getTitle() const {
    return  title;
}

string Activity::getDescription() const {
    return description;
}

Label Activity::getLabel() const {
    return label;
}


Act::Time Activity::getTime() const {
    return actTime;
}


int Activity::getHours() const {
    return actTime.hours;
}

int Activity::getMinutes() const {
    return actTime.minutes;
}

int Activity::getSeconds() const {
    return actTime.seconds;
}
