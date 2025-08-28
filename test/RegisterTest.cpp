//
// Created by vigna on 28/08/2025.
//

#include "gtest/gtest.h"
#include "../Register.h"

TEST(RegisterTest, ConstructorTest) {
    Register reg(1, 9, 2025);
    EXPECT_EQ (reg.getDay(), 1);
    EXPECT_EQ (reg.getMonth(), 9);
    EXPECT_EQ (reg.getYear(), 2025);
}


TEST(RegisterTest, SetAndGetAttributes) {
    Register reg(4, 2, 2010);
    EXPECT_EQ (reg.getDay(), 4);
    EXPECT_EQ (reg.getMonth(), 2);
    EXPECT_EQ (reg.getYear(), 2010);

    reg.setDate(32, 20, 1999);
    /*EXPECT_FALSE (reg.getDay());
    EXPECT_FALSE (reg.getMonth());
    EXPECT_FALSE (reg.getYear());*/
    //TODO sistemare errore test

    EXPECT_EQ (reg.getDay(), 1);
    EXPECT_EQ (reg.getMonth(), 1);
    EXPECT_EQ (reg.getYear(), 2000);
}