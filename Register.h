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

string dateToString(Date date);
int daysInMonth (int m, int y);

class Register {
public:

    Register (int d, int m, int y);

    void setDate (int d, int m, int y, bool mess = true);
    bool setDay (int d);
    bool setMonth (int m);
    bool setYear (int y);
    void addActivity (Activity act);

    int getDay();
    int getMonth();
    int getYear();
    Date getDate();

private:
    Date date{};
    vector<Activity> activities;
};



#endif //REGISTER_H
