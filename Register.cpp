//
// Created by vigna on 17/08/2025.
//

#include "Register.h"

string dateToString(const Date &date) {
    string stringDate;
    if (date.day < 10)
        stringDate = "0" + to_string(date.day);
    else stringDate = to_string(date.day);
    if (date.month < 10)
        stringDate = stringDate + "/0" + to_string(date.month);
    else stringDate = stringDate + "/" + to_string(date.month);
    stringDate = stringDate + "/" + to_string(date.year);
    return stringDate;
}

int daysInMonth(int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            if (y % 4 != 0)
                return 28;
    }
    return 29;
}

Register::Register(int d, int m, int y, bool mess) {
    setDate(d, m, y, mess);
}

void Register::setDate(int d, int m, int y, bool mess) {
    if (!setYear(y) && mess)
        cerr << "invalid value for year, set to 2000" << endl;
    if (!setMonth(m) && mess)
        cerr << "invalid value for month, set to 1" << endl;
    if (!setDay(d) && mess)
        cerr << "invalid value for day, set to 1st" << endl;
}

bool Register::setDay(int d) {
    int max = daysInMonth(date.month, date.year);
    if (d < 1 || d > max) {
        date.day = 1;
        return false;
    }else {
        date.day = d;
        return true;
    }
}

bool Register::setMonth(int m) {
    if (m < 1 || m > 12) {
        date.month = 1;
        return false;
    }else {
        date.month = m;
        return true;
    }
}

bool Register::setYear(int y) {
    if (y < 2000) {
        date.year = 2000;
        return false;
    }
    else {
        date.year = y;
        return true;
    }
}

void Register::addActivity(const Activity &act) {
    auto it = activities.begin();
    bool found = false;
    while (it != activities.end()) {
        if (it->getHours() > act.getHours()) {
            activities.insert(it, act);
            return;
        }else if (it->getHours() == act.getHours() && it->getMinutes() > act.getMinutes()) {
            activities.insert(it, act);
            return;
        }else if (it->getHours() == act.getHours() && it->getMinutes() == act.getMinutes() && it->getSeconds() > act.getSeconds()) {
            activities.insert(it, act);
            return;
        }
        ++it;
    }
    activities.insert(it, act);
}

int Register::getDay() const {
    return date.day;
}

int Register::getMonth() const {
    return date.month;
}

int Register::getYear() const {
    return date.year;
}

Date Register::getDate() const {
    return date;
}

vector<Activity> Register::getVector() {
    return activities;
}
