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
#include "ADFuncVector.h"
#include "ADFuncVector.cpp"
#include "ADFunc.h"
#include "test_vars.h"

void ADLibrary_vectortest(){
    printf("Starting ADFuncVector Class Unit tests...\n");
}

TEST(VECTOR,CONSTRUCTOR){
	std::vector<double> init_values = {1.0,2.0,3.9};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
    ADFunc x = multi_vars[0];
    ADFunc y = multi_vars[1];
    ADFunc z = multi_vars[2];
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);

    EXPECT_TRUE(Fvec.size()==3);
    EXPECT_TRUE(Fvec.checkValid());
}


TEST(VECTOR,INDEX){
	std::vector<double> init_values = {1.0,2.0,3.9};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
    ADFunc x = (multi_vars[0]);
    ADFunc y = (multi_vars[1]);
    ADFunc z = (multi_vars[2]);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);

    EXPECT_NEAR(Fvec.index(0)->val(),8.2515279087505959,DTOL);
    Fvec.index(0)->setVal(2.0);
    EXPECT_NEAR(Fvec.index(0)->val(),2.0,DTOL);

    std::vector<double> newseed = {1.0,0.0,0.0};
    EXPECT_NEAR(Fvec.index(0)->dval_wrt(0),2.63506,0.0001);
    Fvec.index(0)->set_seed(newseed);
    EXPECT_NEAR(Fvec.index(0)->dval_wrt(0),1.0,DTOL);
}

TEST(VECTOR,SETTER){
	std::vector<double> init_values = {1.0,2.0,3.9};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
    ADFunc x = (multi_vars[0]);
    ADFunc y = (multi_vars[1]);
    ADFunc z = (multi_vars[2]);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	Fvec.clear();
	Fvec.setSize(2);
	std::vector<double> new_values = {1.0,2.0};
	std::vector<ADFunc> new_multi_vars = multiVar(new_values);
	Fvec.setFuncVec(new_multi_vars);
    EXPECT_NEAR(Fvec.size(),2.0,DTOL);
}

TEST(VECTOR,ONE_D_DVAL_SINGLE){
    
}

TEST(VECTOR,ONE_D_DVAL_MULTI){
    
}

TEST(VECTOR,TWO_D_DVAL_MULTI){
    
}