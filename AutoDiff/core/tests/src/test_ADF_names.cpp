/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADFunc.h"
#include "test_vars.h"

void ADFLibrary_nametest(){
    printf("Starting ADFunc Class Names tests, eg. 'x', 'y', 'z' for input variables...\n");
}

using namespace std;

TEST(NAME_CONSTRUCTOR,SINGLE){
	std::vector<double> seed_x;
	seed_x.push_back(1.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");

    ADFunc x(2.0,seed_x,name_x);

    /* test getters */
    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==1);
    EXPECT_EQ(x.getName().at(0),"x");
}

TEST(NAME_CONSTRUCTOR,MULTI){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");

    ADFunc x(2.0,seed_x,name_x);

    /* test getters */
    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==2);
    EXPECT_EQ(x.getName().at(0),"x");
    EXPECT_EQ(x.getName().at(1),"y");
}

TEST(NAME_SETTER,SINGLE){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");

    ADFunc x(2.0,seed_x,name_x);
    x.setName(0,"y");

    /* test getters */
    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==1);
    EXPECT_EQ(x.getName().at(0),"y");
}

TEST(NAME_SETTER,MULTI){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    name_x[0] = "z";
    name_x[1] = "y";
    name_x[2] = "x";
    x.setName(name_x);

    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==3);
    EXPECT_EQ(x.getName().at(0),"z");
    EXPECT_EQ(x.getName().at(1),"y");
    EXPECT_EQ(x.getName().at(2),"x");
}

TEST(NAME_SETTER,CLEAR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    x.clearName();

    EXPECT_FALSE(x.hasName());
    EXPECT_TRUE(x.getName().size()==0);
}

TEST(NAME_GETTER,DVAL){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);

    EXPECT_NEAR(x.dval_wrt("x"),1.0,DTOL);
    EXPECT_NEAR(x.dval_wrt("y"),9.0,DTOL);
    EXPECT_NEAR(x.dval_wrt("z"),13.0,DTOL);
}