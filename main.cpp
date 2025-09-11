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

    Fl::set_color(25, 0,204,0);             //green
    Fl::set_color(26, 255,255,0);           //yellow
    Fl::set_color(27, 204,0,0);             //red
    Fl::set_color(28, 255,128,0);           //orange
    Fl::set_color(29, 0,204,204);           //light blue
    Fl::set_color(30, 76, 0, 153);          //dark violet
    Fl::set_color(31, 0,204,102);           //dark aqua

    //Activity act1;
    //Activity act2("Title", "Long description to let it cut for the preview", 0, 2, 30);

    context* ct = new context;

    Register reg(day, month, year);
    ct->r = &reg;
    //reg.addActivity(act1);
    //reg.addActivity(act2);
    Fl_Window window (1000, 750, "ACTIVITY TRACKER");
    ct->win = &window;
    string dateLabel = dateToString(today);
    Fl_Box* dateBox = new Fl_Box(5, 5, 990, 30, dateLabel.c_str());
    dateBox->labelfont(FL_BOLD);
    Fl_Multi_Browser* browser = new Fl_Multi_Browser(5, 35, 990, 660);
    ct->b = browser;
    window.resizable(browser);
    populateBrowser(ct);

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
    Fl_Menu_Button* labelFilter = new Fl_Menu_Button (500, 695, 248, 50, "Filter by Label");
    labelFilter->add("All");
    labelFilter->add(labelToString(Label::Generic).c_str());
    labelFilter->add(labelToString(Label::Fun).c_str());
    labelFilter->add(labelToString(Label::Light_Activity).c_str());
    labelFilter->add(labelToString(Label::Sport).c_str());
    labelFilter->add(labelToString(Label::Wellness).c_str());
    labelFilter->add(labelToString(Label::Work).c_str());
    labelFilter->add(labelToString(Label::Other).c_str());
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

    Fl_Window* popup = new Fl_Window(700,520, "New Activity");
    ct->newAct = popup;
    popup->begin();
    Fl_Input* insertTitle = new Fl_Input(130, 20, 300, 40, "Title: " );
    Fl_Multiline_Input* insertDescription = new Fl_Multiline_Input(130, 80, 500, 140, "Description: ");
    insertDescription->wrap(true);
    Fl_Spinner* insertHour = new Fl_Spinner(190, 270, 70, 50);
    insertHour->type(FL_INT_INPUT);
    insertHour->range(0, 23);
    insertHour->value(0);
    insertHour->step(1);
    Fl_Spinner* insertMinutes = new Fl_Spinner(290, 270, 70, 50);
    insertMinutes->type(FL_INT_INPUT);
    insertMinutes->range(0, 59);
    insertMinutes->value(0);
    insertMinutes->step(1);
    Fl_Spinner* insertSeconds = new Fl_Spinner(390, 270, 70, 50);
    insertSeconds->type(FL_INT_INPUT);
    insertSeconds->range(0, 59);
    insertSeconds->value(0);
    insertSeconds->step(1);
    Fl_Button* createB = new Fl_Button(430, 420, 100, 50, "Create");        //child 5
    createB->callback(createNew_cb, ct);
    Fl_Button* cancelB = new Fl_Button(550, 420, 100, 50, "Cancel");        //child 6
    cancelB->callback(cancelNew_cb, ct);
    Fl_Choice* inputLabel = new Fl_Choice(510, 20, 150, 40, "Label: " );
    inputLabel->add(labelToString(Label::Generic).c_str());
    inputLabel->add(labelToString(Label::Fun).c_str());
    inputLabel->add(labelToString(Label::Light_Activity).c_str());
    inputLabel->add(labelToString(Label::Sport).c_str());
    inputLabel->add(labelToString(Label::Wellness).c_str());
    inputLabel->add(labelToString(Label::Work).c_str());
    inputLabel->add(labelToString(Label::Other).c_str());
    Fl_Button* saveMod = new Fl_Button(430, 420, 100, 50, "Save");          //child 8
    saveMod->callback(save_cb, ct);
    saveMod->hide();
    Fl_Button* cancelMod = new Fl_Button(550, 420, 100, 50, "Cancel");      //child 9
    cancelMod->callback(modify_canc_cb, ct);
    cancelMod->hide();
    ct->ps = new parameters{insertTitle, insertDescription, insertHour, insertMinutes, insertSeconds, inputLabel};
    popup->end();
    popup->hide();

    populateBrowser(ct);

    browser->callback(lineSelect_cb, ct);
    newAct->callback(newAct_cb, ct);                        //callback complete
    removeAct->callback(removeButton_cb, ct);               //callback complete
    labelFilter->callback(visualizeByLabel_cb, ct);
    //TODO implementare visualizzazione per etichetta
    window.end();
    window.show();
    return Fl::run();
}