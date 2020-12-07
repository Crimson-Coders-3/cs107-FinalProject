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

void ADLibrary_nestedtest(){
    printf("Starting ADFunc Class Nested Operation tests...\n");
}

using namespace std;

TEST(NESTED,SINGLE){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    ADFunc x(2.0,seed_x,name_x);

    ADFunc res = exp(sin(x))-cos(pow(x,0.5))*sin( pow( (pow(cos(x),2)+pow(x,2)),0.5));
    res.setName(name_x);

    EXPECT_NEAR(res.val(),2.34369,0.001);
    EXPECT_NEAR(res.dval_wrt("x"),-0.639524,0.001);

    x = ADFunc(0.23,seed_x,name_x);
    res = exp(sin(x))-cos(pow(x,0.5))*sin( pow( (pow(cos(x),2)+pow(x,2)),0.5));
    res.setName(name_x);
    EXPECT_NEAR(res.val(),0.509293,0.001);
    EXPECT_NEAR(res.dval_wrt("x"),1.62405,0.001);

    x = ADFunc(999999,seed_x,name_x);
    res = exp(sin(x))-cos(pow(x,0.5))*sin( pow( (pow(cos(x),2)+pow(x,2)),0.5));
    res.setName(name_x);
    EXPECT_NEAR(res.val(),0.926353,0.001);
    EXPECT_NEAR(res.dval_wrt("x"),-0.0398682,0.001);
}

TEST(NESTED,MULTI){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(0.0);
    seed_x.push_back(0.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);

    std::vector<double> seed_y;
    seed_y.push_back(0.0);
    seed_y.push_back(1.0);
    seed_y.push_back(0.0);
    ADFunc y(3.0,seed_y,name_x);

    std::vector<double> seed_z;
    seed_z.push_back(1.0);
    seed_z.push_back(0.0);
    seed_z.push_back(0.0);
    ADFunc z(2.0,seed_z,name_x);

    //ADFunc res = exp(sin(x))-cos(x^0.5)*sin((cos(x)^2+x^2)^0.5);

    //std::cout << res.val() << std::endl;
}