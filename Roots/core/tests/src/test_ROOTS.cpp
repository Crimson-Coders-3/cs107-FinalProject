/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "Roots.h"
#include "Roots.cpp"
#include "test_vars.h"

void RootsLibrary_testcheck(){
    printf("Starting Roots tests...\n");
}

using namespace std;

TEST(Getter,double){
    double real = 3.3;
    double dual = 7.8;
    Dual x1(real,dual);

    /* test getters */
    EXPECT_NEAR(x1.real(),real,DTOL);
    EXPECT_NEAR(x1.dual(),dual,DTOL);
}


TEST(Constructor,object){

    double real_d = 3.2;
    double dual_d = 7.19;
    Dual y1(real_d,dual_d);
	Dual y2(y1);

    EXPECT_NEAR(y2.real(),real_d,DTOL);
    EXPECT_NEAR(y2.dual(),dual_d,DTOL);
}

TEST(Constructor, default){
	/* test default constructor */
    Dual y;
	EXPECT_NEAR(y.real(), 0.00, DTOL);
	EXPECT_NEAR(y.dual(), 1.00, DTOL);
}

TEST(Constructor, Scalar){
	/* test default constructor */
    Dual y(1.00);
	EXPECT_NEAR(y.real(), 1.00, DTOL);
	EXPECT_NEAR(y.dual(), 1.00, DTOL);
}
