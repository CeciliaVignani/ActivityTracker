//
// Created by vigna on 11/08/2025.
//

#include <iostream>
#include "Activity.h"

Activity::Activity() {
    title = "Untitled activity";
    description = "";
}

Activity::Activity(const string& title) {
    this->title = title;

}

void Activity::setTitle(const string& newTitle) {
    title = newTitle;
}

void Activity::setDescription(const string& newDescr) {
    description = newDescr;
}

string Activity::getTitle() const {
    return title;
}

string Activity::getDescription() const {
    return description;
}

