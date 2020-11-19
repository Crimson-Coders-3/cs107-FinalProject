/* system header files */
#include <stdlib.h>
#include <stdio.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "Dual.h"
#include "Dual.cpp"
#include "test_vars.h"

void DualLibrary_testcheck(){
    printf("Starting AutoDiff Dual tests...\n");
}

using namespace std;

TEST(Getter,int){
    int real = 3;
    int dual = 7;
    Dual<int> x1(real,dual);

    /* test getters */
    EXPECT_EQ(x1.real(),real);  // note: EXECT_EQ used only for integers
    EXPECT_EQ(x1.dual(),dual);
}

TEST(Getter,int){
    int real = 3;
    int dual = 7;
    Dual<int> x1(real,dual);
    Dual<int> x2(x1);

    /* test getters */
    EXPECT_EQ(x1.real(),real);  // note: EXECT_EQ used only for integers
    EXPECT_EQ(x1.dual(),dual);
}