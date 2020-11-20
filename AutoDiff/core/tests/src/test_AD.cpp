/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "AutoDiff.h"
#include "AutoDiff.cpp"
#include "test_vars.h"

void ADLibrary_testcheck(){
    printf("Starting AutoDiff Dual tests...\n");
}

using namespace std;

TEST(CONSTRUCTOR,SINGLE){
    AutoDiff x(2.0);

    /* test getters */
    EXPECT_NEAR(x.getVal(),2.0,DTOL);
    EXPECT_NEAR(x.getDer(),1.0,DTOL);
}