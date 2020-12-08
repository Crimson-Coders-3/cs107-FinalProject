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
#include "ADFunc.cpp"
#include "test_vars.h"

void ADLibrary_unittest(){
    printf("Starting ADFunc Class Unit tests...\n");
}

using namespace std;

/////////////////////////////////////////// CONSTRUCTOR TESTS
TEST(CONSTRUCTOR,SINGLE){
	std::vector<double> seed_x;
	seed_x.push_back(1.0);
    ADFunc x(2.0,seed_x);

    /* test getters */
    EXPECT_NEAR(x.val(),2.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_TRUE(x.hasName()==false);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
}

TEST(CONSTRUCTOR,MULTI){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(0.0);
    seed_x.push_back(0.0);
    std::vector<double> seed_y;
    seed_y.push_back(0.0);
    seed_y.push_back(1.0);
    seed_y.push_back(0.0);
    std::vector<double> seed_z;
    seed_z.push_back(0.0);
    seed_z.push_back(0.0);
    seed_z.push_back(1.0);

    ADFunc x(2.0,seed_x);
    ADFunc y(3.0,seed_y);
    ADFunc z(5.0,seed_z);

    EXPECT_NEAR(x.val(),2.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(2),0.0,DTOL);
    EXPECT_EQ(x.gradient().size(),3);
    EXPECT_EQ(x.countVar(),3);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
    EXPECT_NEAR(x.gradient().at(1),seed_x.at(1),DTOL);
    EXPECT_NEAR(x.gradient().at(2),seed_x.at(2),DTOL);

    EXPECT_NEAR(y.val(),3.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(1),1.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(2),0.0,DTOL);
    EXPECT_EQ(y.gradient().size(),3);
    EXPECT_EQ(y.countVar(),3);
    EXPECT_NEAR(y.gradient().at(0),seed_y.at(0),DTOL);
    EXPECT_NEAR(y.gradient().at(1),seed_y.at(1),DTOL);
    EXPECT_NEAR(y.gradient().at(2),seed_y.at(2),DTOL);

    EXPECT_NEAR(z.val(),5.0,DTOL);
    EXPECT_NEAR(z.dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(z.dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(z.dval_wrt(2),1.0,DTOL);
    EXPECT_EQ(z.gradient().size(),3);
    EXPECT_EQ(z.countVar(),3);
    EXPECT_NEAR(z.gradient().at(0),seed_z.at(0),DTOL);
    EXPECT_NEAR(z.gradient().at(1),seed_z.at(1),DTOL);
    EXPECT_NEAR(z.gradient().at(2),seed_z.at(2),DTOL);
}

TEST(CONSTRUCTOR,ASSIGN){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(0.0);
    seed_x.push_back(0.0);
    ADFunc x(2.0,seed_x);

    ADFunc y = x;
    EXPECT_NEAR(y.val(),2.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(2),0.0,DTOL);
    EXPECT_EQ(y.gradient().size(),3);
    EXPECT_EQ(y.countVar(),3);
    EXPECT_NEAR(y.gradient().at(0),seed_x.at(0),DTOL);
    EXPECT_NEAR(y.gradient().at(1),seed_x.at(1),DTOL);
    EXPECT_NEAR(y.gradient().at(2),seed_x.at(2),DTOL);

    // change x val, y should be unchanged
    x.setVal(3.0);
    EXPECT_NEAR(y.val(),2.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(y.dval_wrt(2),0.0,DTOL);
    EXPECT_EQ(y.gradient().size(),3);
    EXPECT_EQ(y.countVar(),3);
    EXPECT_NEAR(y.gradient().at(0),seed_x.at(0),DTOL);
    EXPECT_NEAR(y.gradient().at(1),seed_x.at(1),DTOL);
    EXPECT_NEAR(y.gradient().at(2),seed_x.at(2),DTOL);

    // change x_seed and x, y should be unchanged
    seed_x[0] = 9.0;
    EXPECT_NEAR(x.val(),3.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(1),0.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(2),0.0,DTOL);
    EXPECT_EQ(x.gradient().size(),3);
    EXPECT_EQ(x.countVar(),3);
    EXPECT_NEAR(x.gradient().at(0),1,DTOL);
    EXPECT_NEAR(x.gradient().at(1),0,DTOL);
    EXPECT_NEAR(x.gradient().at(2),0,DTOL);
}


/////////////////////////////////////////// SETTER TESTS
TEST(SETTER, SINGLE){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    ADFunc x(2.0,seed_x);

    x.setVal(-2.0);
    EXPECT_NEAR(x.val(),-2.0,DTOL);
    x.set_seed_wrt(0,1.99);
    EXPECT_NEAR(x.dval_wrt(0),1.99,DTOL);
    seed_x[0] = 1.89;
    x.set_seed(seed_x);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
}

TEST(SETTER, MULTI){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(0.0);
    seed_x.push_back(0.0);
    ADFunc x(2.0,seed_x);

    /* test setters */
    x.setVal(-2.0);
    EXPECT_NEAR(x.val(),-2.0,DTOL);
    x.set_seed_wrt(0,1.99);
    EXPECT_NEAR(x.dval_wrt(0),1.99,DTOL);
    x.set_seed_wrt(1,1.99);
    EXPECT_NEAR(x.dval_wrt(1),1.99,DTOL);
    EXPECT_NEAR(x.gradient().at(1),1.99,DTOL);
    seed_x[0] = 1.89;
    seed_x[2] = 1.89;
    x.set_seed(seed_x);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
    EXPECT_NEAR(x.gradient().at(2),seed_x.at(2),DTOL);

    seed_x[0] = -.1;
    EXPECT_NEAR(x.gradient().at(0),1.89,DTOL);
}

TEST(SETTER, ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    ADFunc x(2.0,seed_x);

    /* test error msg */
    try {
        x.set_seed_wrt(1,3.0);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range!"));
    }
    try {
    	x.dval_wrt(1);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range!"));
    }
}

/////////////////////////////////////////// ADD TESTS
// ADFunc += double
TEST(ADD, EQUAL_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	x += 3.0;
	EXPECT_NEAR(x.val(),5.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
}

// ADFunc += ADFunc
TEST(ADD, EQUAL_ADFunc){
    std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(1.3);
    ADFunc x1(2.0,seed_x1);
    ADFunc x2(3.0,seed_x2);
    x1 += x2;

    // x1 should be changed
    EXPECT_NEAR(x1.val(),5.0,DTOL);
    EXPECT_NEAR(x1.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x1.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(x1.gradient().size(),2);
    EXPECT_EQ(x1.countVar(),2);
    EXPECT_NEAR(x1.gradient().at(0),seed_x1.at(0),DTOL);
    EXPECT_NEAR(x1.gradient().at(1),seed_x2.at(1),DTOL);

    // x2 should be unchanged
    EXPECT_NEAR(x2.val(),3.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(x2.gradient().size(),2);
    EXPECT_EQ(x2.countVar(),2);
    EXPECT_NEAR(x2.gradient().at(0),seed_x2.at(0),DTOL);
    EXPECT_NEAR(x2.gradient().at(1),seed_x2.at(1),DTOL);
}

// ADFunc += ADFunc, dimension error
TEST(ADD, EQUAL_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(1.3);
    ADFunc x2(3.0,seed_x2);

    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	x2 += x3;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc + ADFunc
TEST(ADD, ADFunc_ADFunc){
	std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(1.3);
    ADFunc x1(2.0,seed_x1);
    ADFunc x2(3.0,seed_x2);
    ADFunc sum = x1 + x2;

	// x2 should be unchanged
    EXPECT_NEAR(sum.val(),5.0,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(sum.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(sum.gradient().size(),2);
    EXPECT_EQ(sum.countVar(),2);
    EXPECT_NEAR(sum.gradient().at(0),1.0,DTOL);
    EXPECT_NEAR(sum.gradient().at(1),1.3,DTOL);
}

// ADFunc + ADFunc, dimension error
TEST(ADD, ADFunc_ADFunc_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(1.3);
    ADFunc x2(3.0,seed_x2);

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	ADFunc sum = x2 + x3;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc + double
TEST(ADD, ADFunc_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc sum = x + 3.3;
	
	EXPECT_NEAR(sum.val(),5.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),3.0,DTOL);
}

// double + ADFunc
TEST(ADD, SCALAR_ADFunc){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc sum = 3.3 + x;
	
	EXPECT_NEAR(sum.val(),5.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),3.0,DTOL);
}


/////////////////////////////////////////// MINUS TESTS
// ADFunc -= double
TEST(MINUS,EQUAL_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	x -= -3.0;
	EXPECT_NEAR(x.val(),5.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
}

// ADFunc -= ADFunc
TEST(MINUS, EQUAL_ADFunc){
    std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x1(2.0,seed_x1);
    ADFunc x2(-3.0,seed_x2);
    x1 -= x2;

    // x1 should be changed
    EXPECT_NEAR(x1.val(),5.0,DTOL);
    EXPECT_NEAR(x1.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x1.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(x1.gradient().size(),2);
    EXPECT_EQ(x1.countVar(),2);
    EXPECT_NEAR(x1.gradient().at(0),seed_x1.at(0),DTOL);
    EXPECT_NEAR(x1.gradient().at(1),1.3,DTOL);

    // x2 should be unchanged
    EXPECT_NEAR(x2.val(),-3.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(1),-1.3,DTOL);
    EXPECT_EQ(x2.gradient().size(),2);
    EXPECT_EQ(x2.countVar(),2);
    EXPECT_NEAR(x2.gradient().at(0),seed_x2.at(0),DTOL);
    EXPECT_NEAR(x2.gradient().at(1),seed_x2.at(1),DTOL);
}

// ADFunc -= ADFunc, dimension error 
TEST(MINUS, EQUAL_ADFunc_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x2(-3.0,seed_x2);

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	x2 -= x3;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc = -ADFunc
TEST(MINUS,NEGATE){
	std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(0.7);
    seed_x.push_back(1.91);
    ADFunc x1(2.0,seed_x);
    ADFunc x2 = -x1;

    EXPECT_NEAR(x2.val(),-2.0,DTOL);
    EXPECT_EQ(x2.gradient().size(),3);
    EXPECT_NEAR(x2.dval_wrt(0),-1.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(1),-0.7,DTOL);
    EXPECT_NEAR(x2.dval_wrt(2),-1.91,DTOL);
    EXPECT_EQ(x2.gradient().size(),3);
    EXPECT_EQ(x2.countVar(),3);
    EXPECT_NEAR(x2.gradient().at(0),-seed_x.at(0),DTOL);
    EXPECT_NEAR(x2.gradient().at(1),-seed_x.at(1),DTOL);
    EXPECT_NEAR(x2.gradient().at(2),-seed_x.at(2),DTOL);

    x1.set_seed_wrt(0,4.2);
    // check nothing changed to x
    EXPECT_NEAR(x2.val(),-2.0,DTOL);
    EXPECT_EQ(x2.gradient().size(),3);
    EXPECT_NEAR(x2.dval_wrt(0),-1.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(1),-0.7,DTOL);
    EXPECT_NEAR(x2.dval_wrt(2),-1.91,DTOL);
    EXPECT_EQ(x2.gradient().size(),3);
    EXPECT_EQ(x2.countVar(),3);
    EXPECT_NEAR(x2.gradient().at(0),-seed_x.at(0),DTOL);
    EXPECT_NEAR(x2.gradient().at(1),-seed_x.at(1),DTOL);
    EXPECT_NEAR(x2.gradient().at(2),-seed_x.at(2),DTOL);
}

// ADFunc - ADFunc
TEST(MINUS, ADFunc_ADFunc){
	std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x1(2.0,seed_x1);
    ADFunc x2(-3.0,seed_x2);
    ADFunc diff = x1 - x2;

	// x2 should be unchanged
    EXPECT_NEAR(diff.val(),5.0,DTOL);
    EXPECT_NEAR(diff.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(diff.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(diff.gradient().size(),2);
    EXPECT_EQ(diff.countVar(),2);
    EXPECT_NEAR(diff.gradient().at(0),1.0,DTOL);
    EXPECT_NEAR(diff.gradient().at(1),1.3,DTOL);
}

// ADFunc - ADFunc, Dimension Error
TEST(MINUS, ADFunc_ADFunc_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x2(-3.0,seed_x2);

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	ADFunc diff = x3 - x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc - double
TEST(MINUS, ADFunc_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc sum = x - 3.3;
	
	EXPECT_NEAR(sum.val(),-1.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),3.0,DTOL);
}

// double - ADFunc
TEST(MINUS, SCALAR_ADFunc){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc sum = 3.3 - x;
	
	EXPECT_NEAR(sum.val(),1.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),-3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),-3.0,DTOL);
}

/////////////////////////////////////////// TIMES TESTS
// ADFunc *= double
TEST(TIMES, EQUAL_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	x *= 3.0;
	EXPECT_NEAR(x.val(),6.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),9.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),9.0,DTOL);
}

// ADFunc *= ADFunc
TEST(TIMES, EQUAL_ADFunc){
    std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x1(2.0,seed_x1);
    ADFunc x2(-3.0,seed_x2);
    x1 *= x2;

    // x1 should be changed
    EXPECT_NEAR(x1.val(),-6.0,DTOL);
    EXPECT_NEAR(x1.dval_wrt(0),-3.0,DTOL);
    EXPECT_NEAR(x1.dval_wrt(1),-2.6,DTOL);
    EXPECT_EQ(x1.gradient().size(),2);
    EXPECT_EQ(x1.countVar(),2);
    EXPECT_NEAR(x1.gradient().at(0),-3.0,DTOL);
    EXPECT_NEAR(x1.gradient().at(1),-2.6,DTOL);

    // x2 should be unchanged
    EXPECT_NEAR(x2.val(),-3.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(1),-1.3,DTOL);
    EXPECT_EQ(x2.gradient().size(),2);
    EXPECT_EQ(x2.countVar(),2);
    EXPECT_NEAR(x2.gradient().at(0),seed_x2.at(0),DTOL);
    EXPECT_NEAR(x2.gradient().at(1),seed_x2.at(1),DTOL);
}

// ADFunc *= ADFunc, dimension error
TEST(TIMES, EQUAL_ADFunc_ERROR){

    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x2(-3.0,seed_x2);

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	x3 *= x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc * ADFunc
TEST(TIMES,ADFunc_ADFunc){
    // x * (-1.3y) = -1.3xy
    // x = 2, (-1.3y)=-3
    // partial derivative wrt x: -1.3y
    // partial derivative wrt y: -1.3x
	std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x1(2.0,seed_x1);
    ADFunc x2(-3.0,seed_x2);
    ADFunc prod = x1 * x2;

    // x1 should be changed
    EXPECT_NEAR(prod.val(),-6.0,DTOL);
    EXPECT_NEAR(prod.dval_wrt(0),-3.0,DTOL);
    EXPECT_NEAR(prod.dval_wrt(1),-2.6,DTOL);
    EXPECT_EQ(prod.gradient().size(),2);
    EXPECT_EQ(prod.countVar(),2);
    EXPECT_NEAR(prod.gradient().at(0),-3.0,DTOL);
    EXPECT_NEAR(prod.gradient().at(1),-2.6,DTOL);
}

// ADFunc * ADFunc, dimension error
TEST(TIMES,ADFunc_ADFunc_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    ADFunc x2(-3.0,seed_x2);

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	ADFunc prod = x3 * x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc * double
TEST(TIMES, ADFunc_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc prod = x * 3.3;
	
	EXPECT_NEAR(prod.val(),6.6,DTOL);
    EXPECT_NEAR(prod.dval_wrt(0),9.9,DTOL);
    EXPECT_EQ(prod.gradient().size(),1);
    EXPECT_EQ(prod.countVar(),1);
    EXPECT_NEAR(prod.gradient().at(0),9.9,DTOL);
}

// double * ADFunc
TEST(TIMES, SCALAR_ADFunc){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc prod = 3.3 * x;
	
	EXPECT_NEAR(prod.val(),6.6,DTOL);
    EXPECT_NEAR(prod.dval_wrt(0),9.9,DTOL);
    EXPECT_EQ(prod.gradient().size(),1);
    EXPECT_EQ(prod.countVar(),1);
    EXPECT_NEAR(prod.gradient().at(0),9.9,DTOL);
}

/////////////////////////////////////////// DIVIDE TESTS
// ADFunc /= double
TEST(QUO,EQUAL_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	x /= 3;
	
	EXPECT_NEAR(x.val(),2.0/3,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),1.0,DTOL);
}

// ADFunc /= ADFunc
TEST(QUO, EQUAL_ADFunc){
    // x1 = x = 2, x2 = 5y = 9
    // x1 = x1/x2 = x/(5y)
    std::vector<double> seed_x1;
	seed_x1.push_back(1.0);
	seed_x1.push_back(0.0);
	ADFunc x1(2.0,seed_x1);
	std::vector<double> seed_x2;
	seed_x2.push_back(0.0);
	seed_x2.push_back(5.0);
	ADFunc x2(9.0,seed_x2);
	x1 /= x2;

	// x1 should be changed
	// x1.dval_wrt("x"), 1/(5y) = 1/ 9, or [(1.0*9.0)-(0.0) ] / 81
	// x1.dval_wrt("y"), 0-x*5/(25y^2)= -10/81, [(0.0-2.0*5.0)]/81 
    EXPECT_NEAR(x1.val(),2.0/9,DTOL);
    EXPECT_NEAR(x1.dval_wrt(0),1.0/9,DTOL);
    EXPECT_NEAR(x1.dval_wrt(1),-10.0/81,DTOL);
    EXPECT_EQ(x1.gradient().size(),2);
    EXPECT_EQ(x1.countVar(),2);
    EXPECT_NEAR(x1.gradient().at(0),1.0/9,DTOL);
    EXPECT_NEAR(x1.gradient().at(1),-10.0/81,DTOL);

    // x2 should be unchanged
    EXPECT_NEAR(x2.val(),9.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(0),0.0,DTOL);
    EXPECT_NEAR(x2.dval_wrt(1),5.0,DTOL);
    EXPECT_EQ(x2.gradient().size(),2);
    EXPECT_EQ(x2.countVar(),2);
    EXPECT_NEAR(x2.gradient().at(0),0.0,DTOL);
    EXPECT_NEAR(x2.gradient().at(1),5.0,DTOL);
}

// ADFunc /= ADFunc, dimension error
TEST(QUO, EQUAL_ADFunc_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(4.0);
    seed_x2.push_back(3.0);
    ADFunc x2(2.0,seed_x2);

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	x3 /= x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }

}

// ADFunc / ADFunc
TEST(QUO, ADFunc_ADFunc){
	std::vector<double> seed_x1;
	seed_x1.push_back(1.0);
	seed_x1.push_back(0.0);
	ADFunc x1(2.0,seed_x1);
	std::vector<double> seed_x2;
	seed_x2.push_back(0.0);
	seed_x2.push_back(5.0);
	ADFunc x2(9.0,seed_x2);
	ADFunc quo = x1 / x2;

    EXPECT_NEAR(quo.val(),2.0/9,DTOL);
    EXPECT_NEAR(quo.dval_wrt(0),1.0/9,DTOL);
    EXPECT_NEAR(quo.dval_wrt(1),-10.0/81,DTOL);
    EXPECT_EQ(quo.gradient().size(),2);
    EXPECT_EQ(quo.countVar(),2);
    EXPECT_NEAR(quo.gradient().at(0),1.0/9,DTOL);
    EXPECT_NEAR(quo.gradient().at(1),-10.0/81,DTOL);
}

// ADFunc / ADFunc, dimension error
TEST(QUO, ADFunc_ADFunc_ERROR){
    std::vector<double> seed_x2;
    seed_x2.push_back(4.0);
    seed_x2.push_back(3.0);
    ADFunc x2(2.0,seed_x2);

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    ADFunc x3(3.9,seed_x3);
    	ADFunc quo = x3 / x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// ADFunc / double
TEST(QUO, ADFunc_SCALAR){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc quo = x / 3;
	
	EXPECT_NEAR(quo.val(),2.0/3,DTOL);
    EXPECT_NEAR(quo.dval_wrt(0),1.0,DTOL);
    EXPECT_EQ(quo.gradient().size(),1);
    EXPECT_EQ(quo.countVar(),1);
    EXPECT_NEAR(quo.gradient().at(0),1.0,DTOL);
}

// double / ADFunc
TEST(QUO, SCALAR_ADFunc){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	ADFunc x(2.0,seed_x);

	ADFunc quo = 3 / x;
	
	EXPECT_NEAR(quo.val(),1.5,DTOL);
    EXPECT_NEAR(quo.dval_wrt(0),-9.0/4,DTOL);
    EXPECT_EQ(quo.gradient().size(),1);
    EXPECT_EQ(quo.countVar(),1);
    EXPECT_NEAR(quo.gradient().at(0),-9.0/4,DTOL);
}

/////////////////////////////////////////// LOGIC TESTS

TEST(LOGIC, EQUAL){
    std::vector<double> seed_x;
    seed_x.push_back(3.0);
    ADFunc x(2.0,seed_x);

    EXPECT_TRUE(x==2.0);
    EXPECT_TRUE(2.0==x);

    ADFunc y(2.0,seed_x);
    EXPECT_TRUE(x==y);
}

TEST(LOGIC, NEQUAL){
    std::vector<double> seed_x;
    seed_x.push_back(3.0);
    ADFunc x(2.0,seed_x);

    EXPECT_TRUE(x!=3.0);
    EXPECT_TRUE(5.0!=x);

    ADFunc y(1.0,seed_x);
    EXPECT_TRUE(x!=y);
    seed_x[0] = 2.9;
    ADFunc z(2.0,seed_x);
    EXPECT_TRUE(z!=x);
    seed_x.push_back(2.0);
    ADFunc q(2.0,seed_x);
    EXPECT_TRUE(q!=x);
}

TEST(LOGIC, LAGER){
    std::vector<double> seed_x;
    seed_x.push_back(3.0);
    ADFunc x(2.0,seed_x);

    EXPECT_TRUE(x>1.0);
    EXPECT_TRUE(3.0>x);
    ADFunc y(3.0,seed_x);
    EXPECT_TRUE(y>x);
}

TEST(LOGIC, SMALLER){
    std::vector<double> seed_x;
    seed_x.push_back(3.0);
    ADFunc x(2.0,seed_x);

    EXPECT_FALSE(x<1.0);
    EXPECT_FALSE(3.0<x);
    ADFunc y(3.0,seed_x);
    EXPECT_FALSE(y<x);
}

TEST(LOGIC, LARGEREQUAL){
    std::vector<double> seed_x;
    seed_x.push_back(3.0);
    ADFunc x(2.0,seed_x);

    EXPECT_TRUE(x>=1.0);
    EXPECT_TRUE(3.0>=x);
    ADFunc y(3.0,seed_x);
    EXPECT_TRUE(y>=x);
}

TEST(LOGIC, SMALLEREQUAL){
    std::vector<double> seed_x;
    seed_x.push_back(3.0);
    ADFunc x(2.0,seed_x);

    EXPECT_FALSE(x<=1.0);
    EXPECT_FALSE(3.0<=x);
    ADFunc y(3.0,seed_x);
    EXPECT_FALSE(y<=x);
}

/////////////////////////////////////////// POW TESTS
// ADFunc ^ double (e.g. x^2)
TEST(POW,LEFTPOW){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(-0.5,seed_x);

	ADFunc powx = pow(x, 2.0);
	EXPECT_NEAR(powx.val(),pow(-0.5, 2.0),DTOL);
	EXPECT_NEAR(powx.dval_wrt(0),4.0*2.0*pow(-0.5,1.0), DTOL);
	EXPECT_EQ(powx.gradient().size(),1);
    EXPECT_EQ(powx.countVar(),1);
	EXPECT_NEAR(powx.gradient().at(0),4.0*2.0*pow(-0.5, 1.0), DTOL);
}

// ADFunc & ADFunc (e.g. x^y)
TEST(POW,POW_TWOVAR){
	std::vector<double> seed_z1;
	seed_z1.push_back(4.0);
	seed_z1.push_back(1.0);
	
	std::vector<double> seed_z2;
	seed_z2.push_back(2.3);
	seed_z2.push_back(3.0);

	ADFunc z1(0.5,seed_z1);
	ADFunc z2(2.0,seed_z2);

	// powxy = (4x+y)^(2.3x+3y)
	// dval with repect to x: (2.3x+3y)*(4x+y)^(2.3x+3y-1)*4+(4x+y)^(2.3x+3y)*2.3*log(0.5)
	//                        ~~~~~~~~~~                      ~~~~     
	//                            2.0                          0.5    
	//                                2.0*(0.5)*4+(0.25)*2.3*log(0.5)  
	// dval with repect to y: (2.3x+3y)*(4x+y)^(2.3x+3y-1)+(4x+y)^(2.3x+3y)*3*log(0.5)
	//                                2.0*0.5+(0.25)*3*log(0.5)
	ADFunc powz = pow(z1, z2);
	EXPECT_NEAR(powz.val(),pow(0.5, 2.0),DTOL);
	EXPECT_NEAR(powz.dval_wrt(0),2.0*(0.5)*4+(0.25)*2.3*log(0.5), DTOL);
	EXPECT_NEAR(powz.dval_wrt(1),2.0*0.5+(0.25)*3*log(0.5), DTOL);
	EXPECT_EQ(powz.gradient().size(),2);
    EXPECT_EQ(powz.countVar(),2);
	EXPECT_NEAR(powz.gradient().at(0),2.0*(0.5)*4+(0.25)*2.3*log(0.5), DTOL);
	EXPECT_NEAR(powz.gradient().at(1),2.0*0.5+(0.25)*3*log(0.5), DTOL);

	// test error msg
	try {
    	std::vector<double> seed_x1;
	    seed_x1.push_back(1.3);
	    seed_x1.push_back(1.3);
	    ADFunc x1(3.9,seed_x1);
	    std::vector<double> seed_x2;
	    seed_x2.push_back(1.0);
	    ADFunc x2(1.8,seed_x2);
    	
    	ADFunc powx = pow(x1, x2);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
    
    try {
    	std::vector<double> seed_y1;
	    seed_y1.push_back(1.3);
	    seed_y1.push_back(1.3);
	    ADFunc y1(-3.9,seed_y1);
	    std::vector<double> seed_y2;
	    seed_y2.push_back(1.0);
	    seed_y2.push_back(1.0);
	    ADFunc y2(1.8,seed_y2);
    	
    	ADFunc powy = pow(y1, y2);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    
    try {
    	std::vector<double> seed_w1;
	    seed_w1.push_back(1.3);
	    seed_w1.push_back(1.3);
	    ADFunc w1(0,seed_w1);
	    std::vector<double> seed_w2;
	    seed_w2.push_back(1.0);
	    seed_w2.push_back(1.0);
	    ADFunc w2(1.8,seed_w2);
    	
    	ADFunc poww = pow(w1, w2);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0!"));
    }
}

// double ^ ADFunc (e.g. 2^x)
TEST(POW,RIGHTPOW){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc powx = pow(2.0, x);
	EXPECT_NEAR(powx.val(),pow(2.0, 0.5),DTOL);
	EXPECT_NEAR(powx.dval_wrt(0),pow(2.0, 0.5)*4.0*log(2.0), DTOL);
	EXPECT_EQ(powx.gradient().size(),1);
    EXPECT_EQ(powx.countVar(),1);
    EXPECT_NEAR(powx.gradient().at(0),pow(2.0, 0.5)*4.0*log(2.0), DTOL);

    // test error msg
    try {
    	std::vector<double> seed_y1;
	    seed_y1.push_back(1.3);
	    seed_y1.push_back(1.3);
	    ADFunc y1(3.9,seed_y1);
    	
    	ADFunc powy = pow(-0.2, y1);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    
    try {
    	std::vector<double> seed_w1;
	    seed_w1.push_back(1.3);
	    seed_w1.push_back(1.3);
	    ADFunc w1(3.8,seed_w1);
    	
    	ADFunc poww = pow(0, w1);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0!"));
    }
}

// square root of ADFunc
TEST(POW,SQRT){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(0.25,seed_x);

    ADFunc sqrtx = sqrt(x);
    EXPECT_NEAR(sqrtx.val(),0.5,DTOL);
    EXPECT_NEAR(sqrtx.dval_wrt(0),4.0, DTOL);
    EXPECT_EQ(sqrtx.gradient().size(),1);
    EXPECT_EQ(sqrtx.countVar(),1);
    EXPECT_NEAR(sqrtx.gradient().at(0),4.0, DTOL);

    try {
        x.setVal(-0.5);
        
        sqrtx = sqrt(x);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
}

// cubic root of ADFunc
TEST(POW,CUBIC){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(27,seed_x);

    ADFunc cubx = cbrt(x);
    EXPECT_NEAR(cubx.val(),3.0,DTOL);
    EXPECT_NEAR(cubx.dval_wrt(0),(1.0/3) * pow(27.0,-2.0/3) * 4.0, DTOL);
    EXPECT_EQ(cubx.gradient().size(),1);
    EXPECT_EQ(cubx.countVar(),1);
    EXPECT_NEAR(cubx.gradient().at(0),(1.0/3) * pow(27.0,-2.0/3) * 4.0, DTOL);
}

// the hypotenuse of a right-angled triangle whose legs are lhs and rhs
TEST(POW,HYPOT){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    seed_x.push_back(0.0);
    ADFunc x(3.0,seed_x);
    std::vector<double> seed_y;
    seed_y.push_back(2.0);
    seed_y.push_back(8.0);
    ADFunc y(4.0,seed_y);
    //sqrt((4x)^2+(2x+8y)^2) = sqrt(16x^2+4x^2+64y^2+32xy)
    // dval wrt x: 1/2/sqrt(16x^2+4x^2+64y^2+32xy)*(32x+8x+32y)
    //             1/10 * (24+16) = 4.0
    // dval wrt y: 1/2/sqrt(16x^2+4x^2+64y^2+32xy)*(128y+32x)
    //             1/10 * (16*4) = 6.4

    ADFunc hypotx = hypot(x,y);
    EXPECT_NEAR(hypotx.val(),5.0,DTOL);
    EXPECT_NEAR(hypotx.dval_wrt(0),4.0, DTOL);
    EXPECT_NEAR(hypotx.dval_wrt(1),6.4, DTOL);
    EXPECT_EQ(hypotx.gradient().size(),2);
    EXPECT_EQ(hypotx.countVar(),2);
    EXPECT_NEAR(hypotx.gradient().at(0),4.0, DTOL);
    EXPECT_NEAR(hypotx.gradient().at(1),6.4, DTOL);
}

/////////////////////////////////////////// EXPONENT TESTS

// e ^ ADFunc
TEST(EXP,EXP){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc expx = exp(x);
	EXPECT_NEAR(expx.val(),exp(0.5),DTOL);
	EXPECT_EQ(expx.gradient().size(),1);
    EXPECT_EQ(expx.countVar(),1);
	EXPECT_NEAR(expx.dval_wrt(0), exp(0.5) * 4.0, DTOL);
	EXPECT_NEAR(expx.gradient().at(0), exp(0.5) * 4.0, DTOL);
}

// 2 ^ ADFunc
TEST(EXP,EXP2){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(0.5,seed_x);

    ADFunc expx = exp2(x);
    EXPECT_NEAR(expx.val(),exp2(0.5),DTOL);
    EXPECT_EQ(expx.gradient().size(),1);
    EXPECT_EQ(expx.countVar(),1);
    EXPECT_NEAR(expx.dval_wrt(0), pow(2.0,0.5)*log(2.0)*4, DTOL);
    EXPECT_NEAR(expx.gradient().at(0), pow(2.0,0.5)*log(2.0)*4, DTOL);
}

// e^ADFunc -1
TEST(EXP,EXP_MINUS1){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(0.5,seed_x);

    ADFunc expmx1 = expm1(x);
    ADFunc expmx2 = exp(x) - 1;
    EXPECT_NEAR(expmx1.val(), expmx2.val(),DTOL);
    EXPECT_EQ(expmx1.gradient().size(),1);
    EXPECT_EQ(expmx1.countVar(),1);
    EXPECT_NEAR(expmx1.dval_wrt(0), expmx2.dval_wrt(0), DTOL);
    EXPECT_NEAR(expmx1.gradient().at(0), expmx2.dval_wrt(0), DTOL);
}

/////////////////////////////////////////// LOG TESTS

// natural log, log_e(x)
TEST(LOG,LOGE){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);
	ADFunc logx = log(x);
	EXPECT_NEAR(logx.val(),log(0.5),DTOL);
	EXPECT_EQ(logx.gradient().size(),1);
    EXPECT_EQ(logx.countVar(),1);
	EXPECT_NEAR(logx.dval_wrt(0), (1/(0.5)) * 4.0, DTOL);
	EXPECT_NEAR(logx.gradient().at(0), (1/(0.5)) * 4.0, DTOL);

	// test error msg
	try {
    	std::vector<double> seed_x1;
	    seed_x1.push_back(1.3);
	    ADFunc x1(-1.0,seed_x1);
    	ADFunc logx1 = log(x1);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }

    try {
    	std::vector<double> seed_w1;
	    seed_w1.push_back(1.3);
	    seed_w1.push_back(1.3);
	    ADFunc w1(0,seed_w1);
    	
    	ADFunc logw1 = log(w1);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0! NaN occurs!"));
    }
}

// log_10(x)
TEST(LOG,LOG10){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);
	ADFunc logx = log10(x);
	EXPECT_NEAR(logx.val(),log10(0.5),DTOL);
	EXPECT_EQ(logx.gradient().size(),1);
    EXPECT_EQ(logx.countVar(),1);
	EXPECT_NEAR(logx.dval_wrt(0), (1/(0.5)) * 4.0/log(10), DTOL);
	EXPECT_NEAR(logx.gradient().at(0), (1/(0.5)) * 4.0/log(10), DTOL);

	// test error msg
	try {
    	x.setVal(-1.0);
    	logx = log10(x);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    try {
        x.setVal(0);
        logx = log10(x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0! NaN occurs!"));
    }
}

// log_2(x)
TEST(LOG,LOG2){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(0.5,seed_x);
    ADFunc logx = log2(x);
    EXPECT_NEAR(logx.val(),log2(0.5),DTOL);
    EXPECT_EQ(logx.gradient().size(),1);
    EXPECT_EQ(logx.countVar(),1);
    EXPECT_NEAR(logx.dval_wrt(0), (1/(0.5)) * 4.0/log(2), DTOL);
    EXPECT_NEAR(logx.gradient().at(0), (1/(0.5)) * 4.0/log(2), DTOL);

    // test error msg
    try {
        x.setVal(-1.0);
        logx = log2(x);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    try {
        x.setVal(0);
        logx = log2(x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0! NaN occurs!"));
    }
}

// log_e(x+1)
TEST(LOG,LOGPLUS1){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(0.5,seed_x);
    ADFunc logx = log1p(x);
    EXPECT_NEAR(logx.val(),log1p(0.5),DTOL);
    EXPECT_EQ(logx.gradient().size(),1);
    EXPECT_EQ(logx.countVar(),1);
    EXPECT_NEAR(logx.dval_wrt(0), (1/(1.5)) * 4.0, DTOL);
    EXPECT_NEAR(logx.gradient().at(0), (1/(1.5)) * 4.0, DTOL);

    // test error msg
    try {
        x.setVal(-2.0);
        logx = log1p(x);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    try {
        x.setVal(-1.0);
        logx = log1p(x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0! NaN occurs!"));
    }
}

/////////////////////////////////////////// PRINT

TEST(IOSTREAM, PRINT){
	// single variable
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);
	testing::internal::CaptureStdout();
	std::cout << x;
	string output_x = testing::internal::GetCapturedStdout();
	string expected_x = "Information of ADFunc object: \nValue at 0.5. \
1 variable(s) in total.\n   0th variable: dval = 4\n";
	EXPECT_TRUE(output_x.compare(expected_x)==0);

	// three variables
	std::vector<double> seed_y;
	seed_y.push_back(4.0);
	seed_y.push_back(5.0);
	seed_y.push_back(6.0);
	ADFunc y(0.5,seed_y);
	testing::internal::CaptureStdout();
	std::cout << y;
	string output_y = testing::internal::GetCapturedStdout();
	string expected_y = "Information of ADFunc object: \nValue at 0.5. \
3 variable(s) in total.\n   0th variable: dval = 4\n   1th variable: dval = 5\n   2th variable: dval = 6\n";
	EXPECT_TRUE(output_y.compare(expected_y)==0);
}


/////////////////////////////////////////// TRIG FUNCTION TESTS
// sin ADFunc 
TEST(TRIG,SIN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc sinx = sin(x);
	EXPECT_NEAR(sinx.val(),sin(0.5),DTOL);
	EXPECT_EQ(sinx.gradient().size(),1);
    EXPECT_EQ(sinx.countVar(),1);
	EXPECT_NEAR(sinx.dval_wrt(0), cos(0.5)*4.0, DTOL);
	EXPECT_NEAR(sinx.gradient().at(0), cos(0.5)*4.0, DTOL);
}

// cos ADFunc
TEST(TRIG,COS){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc cosx = cos(x);
	EXPECT_NEAR(cosx.val(),cos(0.5),DTOL);
	EXPECT_EQ(cosx.gradient().size(),1);
    EXPECT_EQ(cosx.countVar(),1);
	EXPECT_NEAR(cosx.dval_wrt(0), -sin(0.5)*4.0, DTOL);
	EXPECT_NEAR(cosx.gradient().at(0), -sin(0.5)*4.0, DTOL);
}

// tan ADFunc
TEST(TRIG,TAN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc tanx = tan(x);
	EXPECT_NEAR(tanx.val(),tan(0.5),DTOL);
	EXPECT_EQ(tanx.gradient().size(),1);
    EXPECT_EQ(tanx.countVar(),1);
	EXPECT_NEAR(tanx.dval_wrt(0), 4.0/(cos(0.5)*cos(0.5)), DTOL);
	EXPECT_NEAR(tanx.gradient().at(0), 4.0/(cos(0.5)*cos(0.5)), DTOL);
}

// arcsin ADFunc
TEST(TRIG,ARCSIN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc arcsinx = asin(x);
	EXPECT_NEAR(arcsinx.val(),asin(0.5),DTOL);
	EXPECT_EQ(arcsinx.gradient().size(),1);
    EXPECT_EQ(arcsinx.countVar(),1);
	EXPECT_NEAR(arcsinx.dval_wrt(0),(1/sqrt(1-pow(0.5, 2)))*4.0,DTOL);
	EXPECT_NEAR(arcsinx.gradient().at(0),(1/sqrt(1-pow(0.5, 2)))*4.0,DTOL);
}

// arccos ADFunc
TEST(TRIG,ARCCOS){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc arccosx = acos(x);
	EXPECT_NEAR(arccosx.val(),acos(0.5),DTOL);
	EXPECT_EQ(arccosx.gradient().size(),1);
    EXPECT_EQ(arccosx.countVar(),1);
	EXPECT_NEAR(arccosx.dval_wrt(0), -(1/sqrt(1 - pow(0.5, 2))) * 4.0,DTOL);
	EXPECT_NEAR(arccosx.gradient().at(0),-(1/sqrt(1-pow(0.5, 2)))*4.0,DTOL);
}

// arctan ADFunc
TEST(TRIG,ARCTAN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(0.5,seed_x);

	ADFunc arctanx = atan(x);
	EXPECT_NEAR(arctanx.val(),atan(0.5),DTOL);
	EXPECT_EQ(arctanx.gradient().size(),1);
    EXPECT_EQ(arctanx.countVar(),1);
	EXPECT_NEAR(arctanx.dval_wrt(0), (1/(1+pow(0.5, 2))) * 4.0,DTOL);
	EXPECT_NEAR(arctanx.gradient().at(0),(1/(1+pow(0.5, 2))) * 4.0,DTOL);
}

/////////////////////////////////////////// HYPERBOLIC FUNCTIONS

// sinh ADFunc
TEST(TRIG,SINH){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(-0.5,seed_x);

	ADFunc sinhx = sinh(x);
	EXPECT_NEAR(sinhx.val(),sinh(-0.5),DTOL);
	EXPECT_EQ(sinhx.gradient().size(),1);
    EXPECT_EQ(sinhx.countVar(),1);
	EXPECT_NEAR(sinhx.dval_wrt(0),cosh(-0.5) * 4.0, DTOL);
	EXPECT_NEAR(sinhx.gradient().at(0),cosh(-0.5) * 4.0, DTOL);
}

// cosh ADFunc
TEST(TRIG,COSH){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(-0.5,seed_x);

	ADFunc coshx = cosh(x);
	EXPECT_NEAR(coshx.val(),cosh(-0.5),DTOL);
	EXPECT_EQ(coshx.gradient().size(),1);
    EXPECT_EQ(coshx.countVar(),1);
	EXPECT_NEAR(coshx.dval_wrt(0),sinh(-0.5) * 4.0, DTOL);
	EXPECT_NEAR(coshx.gradient().at(0),sinh(-0.5) * 4.0, DTOL);
}

// tanh ADFunc
TEST(TRIG,TANH){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	ADFunc x(-0.5,seed_x);

	ADFunc tanhx = tanh(x);
	EXPECT_NEAR(tanhx.val(),tanh(-0.5),DTOL);
	EXPECT_EQ(tanhx.gradient().size(),1);
    EXPECT_EQ(tanhx.countVar(),1);
	EXPECT_NEAR(tanhx.dval_wrt(0),(1/pow(cosh(-0.5), 2)) * 4.0, DTOL);
	EXPECT_NEAR(tanhx.gradient().at(0),(1/pow(cosh(-0.5), 2)) * 4.0, DTOL);
}

// asinh ADFunc
TEST(TRIG,ASINH){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(-0.5,seed_x);

    ADFunc asinhx = asinh(x);
    EXPECT_NEAR(asinhx.val(),asinh(-0.5),DTOL);
    EXPECT_EQ(asinhx.gradient().size(),1);
    EXPECT_EQ(asinhx.countVar(),1);
    EXPECT_NEAR(asinhx.dval_wrt(0),1/sqrt(0.25+1)*4, DTOL);
    EXPECT_NEAR(asinhx.gradient().at(0),1/sqrt(0.25+1)*4, DTOL);
}

// acosh ADFunc
TEST(TRIG,ACOSH){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(3,seed_x);

    ADFunc acoshx = acosh(x);
    EXPECT_NEAR(acoshx.val(),acosh(3),DTOL);
    EXPECT_EQ(acoshx.gradient().size(),1);
    EXPECT_EQ(acoshx.countVar(),1);
    EXPECT_NEAR(acoshx.dval_wrt(0),1/sqrt(8)*4, DTOL);
    EXPECT_NEAR(acoshx.gradient().at(0),1/sqrt(8)*4, DTOL);

    // test error msg
    try {
        x.setVal(-0.5);
        acoshx = acosh(x);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Sqrt of value less than 0! NaN occurs!"));
    }

    try {
        x.setVal(1);
        acoshx = acosh(x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Denominator equals 0!"));
    }
}

// atanh ADFunc
TEST(TRIG,ATANH){
    std::vector<double> seed_x;
    seed_x.push_back(4.0);
    ADFunc x(-0.5,seed_x);

    ADFunc atanhx = atanh(x);
    EXPECT_NEAR(atanhx.val(),atanh(-0.5),DTOL);
    EXPECT_EQ(atanhx.gradient().size(),1);
    EXPECT_EQ(atanhx.countVar(),1);
    EXPECT_NEAR(atanhx.dval_wrt(0),1/0.75*4, DTOL);
    EXPECT_NEAR(atanhx.gradient().at(0),1/0.75*4, DTOL);

    try {
        x.setVal(1);
        atanhx = atanh(x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Denominator equals 0!"));
    }
}