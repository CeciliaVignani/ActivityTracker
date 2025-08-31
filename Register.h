//
// Created by vigna on 17/08/2025.
//

#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Activity.h"

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

string dateToString(const Date &date);
int daysInMonth (int m, int y);

class Register {
public:

    Register (int d, int m, int y, bool mess = true);

    void setDate (int d, int m, int y, bool mess = true);
    bool setDay (int d);
    bool setMonth (int m);
    bool setYear (int y);
    void addActivity (const Activity &act);

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    Date getDate() const;

    vector<Activity> getVector();

private:
    Date date{};
    vector<Activity> activities;
};



#endif //REGISTER_H
