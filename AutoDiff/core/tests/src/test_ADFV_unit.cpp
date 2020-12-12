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

TEST(VECTOR,CONSTRUCTOR_EMPTY){
	ADFuncVector Fvec();
}

TEST(VECTOR,CONSTRUCTOR_INT){
	ADFuncVector Fvec(4);
	
	try {
        Fvec.size();
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Dimension Not Matched!"));
    }
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

TEST(VECTOR,AT){
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

    EXPECT_NEAR(Fvec.at(0)->val(),8.2515279087505959,DTOL);
    Fvec.at(0)->setVal(2.0);
    EXPECT_NEAR(Fvec.at(0)->val(),2.0,DTOL);
	
	int v1 = 0;

    std::vector<double> newseed = {1.0,0.0,0.0};
    EXPECT_NEAR(Fvec.at(0)->dval_wrt(v1),2.63506,0.0001);
    Fvec.at(0)->set_seed(newseed);
    EXPECT_NEAR(Fvec.at(0)->dval_wrt(v1),1.0,DTOL);
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
	
	try {
        Fvec.setSize(5);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Input size mismatches with previously defined funcVector! Please use clear() before set size."));
    }
}

TEST(VECTOR,EMPTY){
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
	EXPECT_TRUE(Fvec.empty());
}

TEST(VECTOR,DVAL_WRT_INT_INT){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	EXPECT_NEAR(Fvec.dval_wrt(0,0),2.95005,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(2,1),-0.0729587,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(1,2),28.3665,0.0001);
	
	try {
        Fvec.dval_wrt(4,1);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Function index out of range!"));
    }
}

TEST(VECTOR,DVAL_WRT_INT_STR){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	EXPECT_NEAR(Fvec.dval_wrt(0,"a"),2.95005,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(2,"b"),-0.0729587,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(1,"c"),28.3665,0.0001);
	
	try {
        Fvec.dval_wrt(4,"a");
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Function index out of range!"));
    }
}

TEST(VECTOR,DVAL_WRT_INT){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	int v1 = 0;
	int v2 = 1;
	int v3 = 2;	
	
	EXPECT_NEAR(Fvec.dval_wrt(v1).at(0),2.95005,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(v2).at(2),-0.0729587,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(v3).at(1),28.3665,0.0001);
}

TEST(VECTOR,DVAL_WRT_STR){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	std::string v1 = "a";
	std::string v2 = "b";
	std::string v3 = "c";	
	
	EXPECT_NEAR(Fvec.dval_wrt(v1).at(0),2.95005,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(v2).at(2),-0.0729587,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(v3).at(1),28.3665,0.0001);
}

TEST(VECTOR,ONE_D_DVAL_SINGLE){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	std::vector< std::pair<int, int> > p1 = {{0,0}};
	std::vector< std::pair<int, int> > p2 = {{2,1}}; 
	std::vector< std::pair<int, int> >  p3 = {{1,2}}; 
	
	EXPECT_NEAR(Fvec.dval_wrt(p1).at(0),2.95005,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(p2).at(0),-0.0729587,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(p3).at(0),28.3665,0.0001);
	
	try {
        std::vector< std::pair<int, int> > p4 = {{3,0}};
		Fvec.dval_wrt(p4).at(0);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Function index out of range!"));
    }
}

TEST(VECTOR,ONE_D_DVAL_MULTI){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	std::vector< std::pair<int, std::string> > p1 = {{0,"a"}};
	std::vector< std::pair<int, std::string> > p2 = {{2,"b"}}; 
	std::vector< std::pair<int, std::string> > p3 = {{1,"c"}}; 
	
	EXPECT_NEAR(Fvec.dval_wrt(p1).at(0),2.95005,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(p2).at(0),-0.0729587,0.0001);
	EXPECT_NEAR(Fvec.dval_wrt(p3).at(0),28.3665,0.0001);  

	try {
        std::vector< std::pair<int, std::string> > p4 = {{3,"a"}};
		Fvec.dval_wrt(p4).at(0);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Function index out of range!"));
    }
}

TEST(VECTOR,TWO_D_DVAL_MULTI){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	std::vector<std::vector<std::pair<int, int> > > p1 = { {{0,0},{2,1}},{{2,0},{1,1}}};;
	
	EXPECT_NEAR(Fvec.dval_wrt(p1).at(0).at(0),2.95005,0.0001);  
	EXPECT_NEAR(Fvec.dval_wrt(p1).at(0).at(1),-0.0729587,0.0001);	
	
	try {
        std::vector<std::vector<std::pair<int, int> > > p2 = { {{3,0},{2,1}},{{2,0},{1,1}}};
		Fvec.dval_wrt(p2).at(0).at(0);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Function index out of range!"));
    }
}

TEST(VECTOR,TWO_D_DVAL_MULTI_VAR){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	std::vector<std::vector<std::pair<int, std::string> > > p1 = { {{0,"a"},{2,"b"}},{{2,"a"},{1,"b"}}};;
	
	EXPECT_NEAR(Fvec.dval_wrt(p1).at(0).at(0),2.95005,0.0001);  
	EXPECT_NEAR(Fvec.dval_wrt(p1).at(0).at(1),-0.0729587,0.0001);	
	
	try {
        std::vector<std::vector<std::pair<int, std::string> > > p2 = { {{3,"a"},{2,"b"}},{{2,"a"},{1,"b"}}};;
		Fvec.dval_wrt(p2).at(0).at(0);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Function index out of range!"));
    }
}

TEST(VECTOR,COUNTVAR){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	EXPECT_NEAR(Fvec.countVar(),3.0,0.0001); 
}

TEST(VECTOR,PUSHBACK){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2};
    ADFuncVector Fvec(F);
	
	Fvec.push_back(f3);
	
	EXPECT_NEAR(Fvec.countVar(),3.0,0.0001); 
}

TEST(VECTOR,VAL){
	std::vector<double> init_values = {1.0,2.0,3.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
	std::vector<std::string> names {"a","b", "c"};
    ADFunc x = (multi_vars[0]);
	x.setName(names);
    ADFunc y = (multi_vars[1]);
	y.setName(names);
    ADFunc z = (multi_vars[2]);
	z.setName(names);
    ADFunc f1 = 2.0*x + x*y+z/pow(sin(x),0.5);
    ADFunc f2 = exp(z)/pow(sin(x),2.0)-4*pow(x,3.0);
    ADFunc f3 = exp(sin(x)*cos(y)-2);
    std::vector<ADFunc> F = {f1,f2,f3};
    ADFuncVector Fvec(F);
	
	EXPECT_NEAR(Fvec.val(0),7.27041,0.0001); 
}