#include <iostream>
#include <ctime>

#include "Activity.h"
#include "Register.h"
#include "Utils.h"

int main() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    int day = local->tm_mday;
    int month = local->tm_mon +1;
    int year = local->tm_year + 1900;
    Date today {day, month, year};

    Activity act1;
    Activity act2("Title", "Long description to let it cut for the previwe", 0, 2, 30);

    context* ct = new context;

    Register reg(day, month, year);
    ct->r = &reg;
    reg.addActivity(act1);
    reg.addActivity(act2);
    Fl_Window window (1000, 750, "ACTIVITY TRACKER");
    ct->win = &window;
    string dateLabel = dateToString(today);
    Fl_Box* dateBox = new Fl_Box(5, 5, 990, 30, dateLabel.c_str());
    dateBox->labelfont(FL_BOLD);
    Fl_Browser* browser = new Fl_Browser(5, 35, 990, 660);
    ct->b = browser;
    window.resizable(browser);
    populateBrowser(reg,*browser);

    Fl_Button* prevDay = new Fl_Button(5,5, 60, 30, "<<");
    ct->allButtons.push_back(prevDay);
    Fl_Button* nextDay = new Fl_Button(935, 5, 60, 30, ">>");
    ct->allButtons.push_back(nextDay);
    prevDay->align(FL_ALIGN_CENTER);
    prevDay->labelfont(FL_BOLD);
    nextDay->align(FL_ALIGN_CENTER);
    nextDay->labelfont(FL_BOLD);
    Fl_Button* newAct = new Fl_Button(5, 695, 247, 50, "New");
    ct->allButtons.push_back(newAct);
    Fl_Button* removeAct = new Fl_Button(252, 695, 248, 50, "Remove");
    ct->allButtons.push_back(removeAct);
    Fl_Button* labelFilter = new Fl_Button (500, 695, 248, 50, "Filter by Label");
    ct->allButtons.push_back(labelFilter);
    Fl_Button* orderBy = new Fl_Button (748, 695, 247, 50, "Order by:");
    ct->allButtons.push_back(orderBy);
    newAct->align(FL_ALIGN_CENTER);
    removeAct->align(FL_ALIGN_CENTER);
    labelFilter->align(FL_ALIGN_CENTER);
    orderBy->align(FL_ALIGN_CENTER);

    Fl_Group* group = new Fl_Group(945, 35, 50, 660);
    ct->deleteg = group;
    group->begin();
    int n = reg.getVector().size();
    for (int i = 0; i < n; i++) {
        Fl_Button* deleteB = new Fl_Button(945, 35 + (50*i), 50, 50, "X");
        ct->deleteButtons[deleteB] = i;
        deleteB->callback(deleteButton_cb, ct);             //callback complete
    }
    group->end();
    group->hide();

    //Fl_Window* popup = new Fl_Window()

    newAct->callback(newAct_cb, ct);
    removeAct->callback(removeButton_cb, ct);               //callback complete

    window.end();
    window.show();
    return Fl::run();
}