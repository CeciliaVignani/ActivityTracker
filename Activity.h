//
// Created by vigna on 11/08/2025.
//

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>

using namespace std;

class Activity {
public:

    Activity();
    Activity(const string& title);

    void setTitle (const string& newTitle);
    void setDescription  (const string& newDescr);
    string getTitle () const;
    string getDescription () const;

private:
    string title;
    string description;
};


#endif //ACTIVITY_H
