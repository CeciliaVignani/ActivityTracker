//
// Created by vigna on 28/08/2025.
//

#include "gtest/gtest.h"
#include "../Register.h"

TEST(RegisterTest, DateToStringMethod) {
    Date testDate;
    testDate.day = 3;
    testDate.month = 9;
    testDate.year = 2010;
    EXPECT_EQ (dateToString(testDate), "03/09/2010");

    testDate.day = 8;
    testDate.month = 11;
    testDate.year = 2025;
    EXPECT_EQ (dateToString(testDate), "08/11/2025");

    testDate.day = 11;
    testDate.month = 10;
    testDate.year = 2007;
    EXPECT_EQ (dateToString(testDate), "11/10/2007");
}


TEST(RegisterTest, ConstructorTest) {
    Register reg(1, 9, 2025);
    EXPECT_EQ (reg.getDay(), 1);
    EXPECT_EQ (reg.getMonth(), 9);
    EXPECT_EQ (reg.getYear(), 2025);
}


    TEST(RegisterTest, SetAndGetAttributes) {
    Register reg(32, 20, 1999, false);
    EXPECT_EQ (reg.getDay(), 1);
    EXPECT_EQ (reg.getMonth(), 1);
    EXPECT_EQ (reg.getYear(), 2000);

    reg.setDate(4, 2, 2010);
    Date d = reg.getDate();
    EXPECT_EQ(reg.getDay(), 4);
    EXPECT_EQ(reg.getMonth(), 2);
    EXPECT_EQ(reg.getYear(), 2010);

    Activity a1("", "", 2, 0, 30);
    Activity a2("name", "description", 1, 30, 25);
    reg.addActivity(a1);
    reg.addActivity(a2);
    EXPECT_EQ (reg.getVector()[0].getTitle(), a2.getTitle());
    EXPECT_EQ (reg.getVector()[1].getDescription(), a1.getDescription());
}