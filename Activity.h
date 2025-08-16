//
// Created by vigna on 11/08/2025.
//

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>

using namespace std;

struct Time {
    int hours;
    int minutes;
    int seconds;
};

enum class Label {
    Sport,
    Wellness,
    Work,
    Light_Activity,
    Fun,
    Other
};

string labelToString(Label l);

class Activity {
public:

    Activity();
    Activity(const string& title, const string& description, int hours, int minutes, int seconds);

    void setTitle (const string& newTitle);
    void setDescription  (const string& newDescr);
    void setLabel (Label l);
    void setTime (int h, int min, int sec, bool mess = true);
    bool setHours (int h);
    bool setMinutes (int m);
    bool setSeconds (int s);
    string getTitle () const;
    string getDescription () const;
    string getLabel () const;
    Time getTime() const;
    int getHours () const;
    int getMinutes () const;
    int getSeconds () const;

private:
    string title;
    string description;
    Time actTime;
    Label label;
};


#endif //ACTIVITY_H
