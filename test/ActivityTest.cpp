//
// Created by vigna on 14/08/2025.
//

#include "gtest/gtest.h"
#include "../Activity.h"

TEST(ActivityTest, ConstructorTest) {
    Activity activity;
    EXPECT_EQ (activity.getTitle(), "Untitled activity");
    EXPECT_EQ (activity.getDescription(), "");
    EXPECT_EQ (activity.getHours(), 0);
    EXPECT_EQ (activity.getMinutes(), 0);
    EXPECT_EQ (activity.getSeconds(), 0);

    Activity act2 ("no name", "no description", 1, 26, 56);
    EXPECT_EQ (act2.getTitle(), "no name");
    EXPECT_EQ (act2.getDescription(), "no description");
    EXPECT_EQ (act2.getHours(), 1);
    EXPECT_EQ (act2.getMinutes(), 26);
    EXPECT_EQ (act2.getSeconds(), 56);
}


TEST(ActivityTest, SetAndGetAttributes) {
    Activity activity;
    activity.setTime(-1, 99, 70, false);
    EXPECT_EQ (activity.getHours(), 0);
    EXPECT_EQ (activity.getMinutes(), 0);
    EXPECT_EQ (activity.getSeconds(), 0);

    activity.setTime(0,23,55);
    Time t = activity.getTime();
    EXPECT_EQ (t.hours, 0);
    EXPECT_EQ (t.minutes, 23);
    EXPECT_EQ (t.seconds, 55);
}