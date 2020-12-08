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
    seed_z.push_back(0.0);
    seed_z.push_back(0.0);
    seed_z.push_back(1.0);
    ADFunc z(10.0,seed_z,name_x);

    ADFunc res = exp(sin(z))-log2(cos(pow(x,0.5)))*sin( pow( pow(cos(x),2)+pow(x,2),0.5))*y/pow(3,z);

    EXPECT_NEAR(res.val(),0.580531,0.001);
    EXPECT_NEAR(res.dval_wrt("x"),0.0000740872,0.00001);
    EXPECT_NEAR(res.dval_wrt("y"),0.0000404364,0.00001);
    EXPECT_NEAR(res.dval_wrt("z"),-0.487138,0.001);
}


TEST(NESTED,VECTORINPUT){
    std::vector<double> init_values = {1.0,2.0,3.9};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
    ADFunc* x = &(multi_vars[0]);
    ADFunc* y = &(multi_vars[1]);
    ADFunc* z = &(multi_vars[2]);

    EXPECT_NEAR(x->val(),1.0,DTOL);
    EXPECT_NEAR(y->val(),2.0,DTOL);
    EXPECT_NEAR(z->val(),3.9,DTOL);

    EXPECT_NEAR(x->dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x->dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(x->dval_wrt(2),0.0,DTOL);
    EXPECT_NEAR(y->dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(y->dval_wrt(1),1.0,DTOL);
    EXPECT_NEAR(y->dval_wrt(2),0.0,DTOL);
    EXPECT_NEAR(z->dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(z->dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(z->dval_wrt(2),1.0,DTOL);

    //modify
    x->setVal(100.0);
    EXPECT_NEAR( (multi_vars[0]).val(),100.0,DTOL);
    EXPECT_NEAR(x->val(),100.0,DTOL);
}