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
#include "AutoDiff.h"
#include "AutoDiff.cpp"
#include "test_vars.h"

void ADLibrary_testcheck(){
    printf("Starting AutoDiff Dual tests...\n");
}

using namespace std;

TEST(CONSTRUCTOR,SINGLE){
	std::vector<double> seed_x;
	seed_x.push_back(1.0);
    AutoDiff x(2.0,seed_x);

    /* test getters */
    EXPECT_NEAR(x.val(),2.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
}

TEST(CONSTRUCTOR,SETTER){
	std::vector<double> seed_x;
	seed_x.push_back(1.0);
    AutoDiff x(2.0,seed_x);

    /* test setters */
    x.setVal(-2.0);
    EXPECT_NEAR(x.val(),-2.0,DTOL);
    x.set_dval_wrt(0,1.99);
    EXPECT_NEAR(x.dval_wrt(0),1.99,DTOL);
    seed_x[0] = 1.89;
    x.set_dval(seed_x);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);

    std::vector<double> seed_copy = x.gradient();
    seed_copy[0] = -.1;
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);

    /* test error msg */
    try {
        x.set_dval_wrt(1,3.0);
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
// AutoDiff += double and AutoDiff += AutoDiff
TEST(OPERATOR,ADDEQUAL){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	x += 3.0;
	EXPECT_NEAR(x.val(),5.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);

    std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(1.3);
    AutoDiff x1(2.0,seed_x1);
    AutoDiff x2(3.0,seed_x2);
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

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	x2 += x3;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff + AutoDiff
TEST(OPERATOR,ADD){
	std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(1.3);
    AutoDiff x1(2.0,seed_x1);
    AutoDiff x2(3.0,seed_x2);
    AutoDiff sum = x1 + x2;

	// x2 should be unchanged
    EXPECT_NEAR(sum.val(),5.0,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(sum.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(sum.gradient().size(),2);
    EXPECT_EQ(sum.countVar(),2);
    EXPECT_NEAR(sum.gradient().at(0),1.0,DTOL);
    EXPECT_NEAR(sum.gradient().at(1),1.3,DTOL);

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	AutoDiff sum = x2 + x3;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff + double
TEST(OPERATOR,ADDAFTER){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff sum = x + 3.3;
	
	EXPECT_NEAR(sum.val(),5.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),3.0,DTOL);
}

// double + AutoDiff
TEST(OPERATOR,ADDBEFORE){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff sum = 3.3 + x;
	
	EXPECT_NEAR(sum.val(),5.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),3.0,DTOL);
}


/////////////////////////////////////////// SUB TESTS
// AutoDiff -= double and AutoDiff -= AutoDiff
TEST(OPERATOR,MINUSEQUAL){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	x -= -3.0;
	EXPECT_NEAR(x.val(),5.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);

    std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    AutoDiff x1(2.0,seed_x1);
    AutoDiff x2(-3.0,seed_x2);
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

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	x2 -= x3;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff = -AutoDiff
TEST(OPERATOR,NEGATE){
	std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(0.7);
    seed_x.push_back(1.91);
    AutoDiff x(2.0,seed_x);

    EXPECT_NEAR(x.val(),2.0,DTOL);
    EXPECT_EQ(x.gradient().size(),3);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(1),0.7,DTOL);
    EXPECT_NEAR(x.dval_wrt(2),1.91,DTOL);
    EXPECT_EQ(x.gradient().size(),3);
    EXPECT_EQ(x.countVar(),3);
    EXPECT_NEAR(x.gradient().at(0),seed_x.at(0),DTOL);
    EXPECT_NEAR(x.gradient().at(1),seed_x.at(1),DTOL);
    EXPECT_NEAR(x.gradient().at(2),seed_x.at(2),DTOL);

    seed_x.push_back(-0.2);
    seed_x[0] = 1.99999;
    // check nothing changed to x
    EXPECT_NEAR(x.val(),2.0,DTOL);
    EXPECT_EQ(x.gradient().size(),3);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(1),0.7,DTOL);
    EXPECT_EQ(x.gradient().size(),3);
    EXPECT_EQ(x.countVar(),3);
    EXPECT_NEAR(x.gradient().at(0),1.0,DTOL);
    EXPECT_NEAR(x.gradient().at(1),0.7,DTOL);
    EXPECT_NEAR(x.gradient().at(2),1.91,DTOL);
}

// AutoDiff - AutoDiff
TEST(OPERATOR,MINUS){
	std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    AutoDiff x1(2.0,seed_x1);
    AutoDiff x2(-3.0,seed_x2);
    AutoDiff diff = x1 - x2;

	// x2 should be unchanged
    EXPECT_NEAR(diff.val(),5.0,DTOL);
    EXPECT_NEAR(diff.dval_wrt(0),1.0,DTOL);
    EXPECT_NEAR(diff.dval_wrt(1),1.3,DTOL);
    EXPECT_EQ(diff.gradient().size(),2);
    EXPECT_EQ(diff.countVar(),2);
    EXPECT_NEAR(diff.gradient().at(0),1.0,DTOL);
    EXPECT_NEAR(diff.gradient().at(1),1.3,DTOL);

    // error message
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	AutoDiff diff = x3 - x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff - double
TEST(OPERATOR,MINUSAFTER){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff sum = x - 3.3;
	
	EXPECT_NEAR(sum.val(),-1.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),3.0,DTOL);
}

// double - AutoDiff
TEST(OPERATOR,MINUSBEFORE){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff sum = 3.3 - x;
	
	EXPECT_NEAR(sum.val(),1.3,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),-3.0,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),-3.0,DTOL);
}

/////////////////////////////////////////// TIMES TESTS
// AutoDiff *= double and AutoDiff *= AutoDiff
TEST(OPERATOR,TIMESEQUAL){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	x *= 3.0;
	EXPECT_NEAR(x.val(),6.0,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),9.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),9.0,DTOL);

    std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    AutoDiff x1(2.0,seed_x1);
    AutoDiff x2(-3.0,seed_x2);
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

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	x3 *= x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff * AutoDiff
TEST(OPERATOR,TIMES){
	std::vector<double> seed_x1;
    seed_x1.push_back(1.0);
    seed_x1.push_back(0.0);
    std::vector<double> seed_x2;
    seed_x2.push_back(0.0);
    seed_x2.push_back(-1.3);
    AutoDiff x1(2.0,seed_x1);
    AutoDiff x2(-3.0,seed_x2);
    AutoDiff prod = x1 * x2;

    // x1 should be changed
    EXPECT_NEAR(prod.val(),-6.0,DTOL);
    EXPECT_NEAR(prod.dval_wrt(0),-3.0,DTOL);
    EXPECT_NEAR(prod.dval_wrt(1),-2.6,DTOL);
    EXPECT_EQ(prod.gradient().size(),2);
    EXPECT_EQ(prod.countVar(),2);
    EXPECT_NEAR(prod.gradient().at(0),-3.0,DTOL);
    EXPECT_NEAR(prod.gradient().at(1),-2.6,DTOL);

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	AutoDiff prod = x3 * x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff * double
TEST(OPERATOR,TIMESAFTER){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff sum = x * 3.3;
	
	EXPECT_NEAR(sum.val(),6.6,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),9.9,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),9.9,DTOL);
}

// double * AutoDiff
TEST(OPERATOR,TIMESBEFORE){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff sum = 3.3 * x;
	
	EXPECT_NEAR(sum.val(),6.6,DTOL);
    EXPECT_NEAR(sum.dval_wrt(0),9.9,DTOL);
    EXPECT_EQ(sum.gradient().size(),1);
    EXPECT_EQ(sum.countVar(),1);
    EXPECT_NEAR(sum.gradient().at(0),9.9,DTOL);
}

/////////////////////////////////////////// DIVIDE TESTS
// AutoDiff /= double and AutoDiff /= AutoDiff
TEST(OPERATOR,QUOEQUAL){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	x /= 3;
	
	EXPECT_NEAR(x.val(),2.0/3,DTOL);
    EXPECT_NEAR(x.dval_wrt(0),1.0,DTOL);
    EXPECT_EQ(x.gradient().size(),1);
    EXPECT_EQ(x.countVar(),1);
    EXPECT_NEAR(x.gradient().at(0),1.0,DTOL);

    std::vector<double> seed_x1;
	seed_x1.push_back(1.0);
	seed_x1.push_back(0.0);
	AutoDiff x1(2.0,seed_x1);
	std::vector<double> seed_x2;
	seed_x2.push_back(0.0);
	seed_x2.push_back(5.0);
	AutoDiff x2(9.0,seed_x2);
	x1 /= x2;

	// x1 should be changed
	// x1.dval_wrt(0),[(1.0*9.0)-(0.0) ] / 81
	// x1.dval_wrt(1),[(0.0-2.0*5.0)]/81 
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

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	x3 /= x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }

}

// AutoDiff / AutoDiff
TEST(OPERATOR,QUO){
	std::vector<double> seed_x1;
	seed_x1.push_back(1.0);
	seed_x1.push_back(0.0);
	AutoDiff x1(2.0,seed_x1);
	std::vector<double> seed_x2;
	seed_x2.push_back(0.0);
	seed_x2.push_back(5.0);
	AutoDiff x2(9.0,seed_x2);
	AutoDiff quo = x1 / x2;

    EXPECT_NEAR(quo.val(),2.0/9,DTOL);
    EXPECT_NEAR(quo.dval_wrt(0),1.0/9,DTOL);
    EXPECT_NEAR(quo.dval_wrt(1),-10.0/81,DTOL);
    EXPECT_EQ(quo.gradient().size(),2);
    EXPECT_EQ(quo.countVar(),2);
    EXPECT_NEAR(quo.gradient().at(0),1.0/9,DTOL);
    EXPECT_NEAR(quo.gradient().at(1),-10.0/81,DTOL);

    // test error msg
    try {
    	std::vector<double> seed_x3;
	    seed_x3.push_back(1.3);
	    AutoDiff x3(3.9,seed_x3);
    	AutoDiff quo = x3 / x2;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
}

// AutoDiff / double
TEST(OPERATOR,QUOAFTER){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff quo = x / 3;
	
	EXPECT_NEAR(quo.val(),2.0/3,DTOL);
    EXPECT_NEAR(quo.dval_wrt(0),1.0,DTOL);
    EXPECT_EQ(quo.gradient().size(),1);
    EXPECT_EQ(quo.countVar(),1);
    EXPECT_NEAR(quo.gradient().at(0),1.0,DTOL);
}

// double * AutoDiff
TEST(OPERATOR,QUOBEFORE){
	std::vector<double> seed_x;
	seed_x.push_back(3.0);
	AutoDiff x(2.0,seed_x);

	AutoDiff quo = 3 / x;
	
	EXPECT_NEAR(quo.val(),1.5,DTOL);
    EXPECT_NEAR(quo.dval_wrt(0),-9.0/4,DTOL);
    EXPECT_EQ(quo.gradient().size(),1);
    EXPECT_EQ(quo.countVar(),1);
    EXPECT_NEAR(quo.gradient().at(0),-9.0/4,DTOL);
}

/////////////////////////////////////////// POW TESTS
// AutoDiff ^ double (e.g. x^2)
TEST(MATH,LEFTPOW){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(-0.5,seed_x);

	AutoDiff powx = pow(x, 2.0);
	EXPECT_NEAR(powx.val(),pow(-0.5, 2.0),DTOL);
	EXPECT_NEAR(powx.dval_wrt(0),4.0*2.0*pow(-0.5,1.0), DTOL);
	EXPECT_EQ(powx.gradient().size(),1);
    EXPECT_EQ(powx.countVar(),1);
	EXPECT_NEAR(powx.gradient().at(0),4.0*2.0*pow(-0.5, 1.0), DTOL);
}

// AutoDiff & AutoDiff (e.g. x^y)
TEST(MATH,POW_TWOVAR){
	std::vector<double> seed_z1;
	seed_z1.push_back(4.0);
	seed_z1.push_back(1.0);
	
	std::vector<double> seed_z2;
	seed_z2.push_back(2.3);
	seed_z2.push_back(3.0);

	AutoDiff z1(0.5,seed_z1);
	AutoDiff z2(2.0, seed_z2);

	// powxy = (4x+y)^(2.3x+3y)
	// dval with repect to x: (2.3x+3y)*(4x+y)^(2.3x+3y-1)*4+(4x+y)^(2.3x+3y)*2.3*log(0.5)
	//                        ~~~~~~~~~~                      ~~~~     
	//                            2.0                          0.5    
	//                                2.0*(0.5)*4+(0.25)*2.3*log(0.5)  
	// dval with repect to y: (2.3x+3y)*(4x+y)^(2.3x+3y-1)+(4x+y)^(2.3x+3y)*3*log(0.5)
	//                                2.0*0.5+(0.25)*3*log(0.5)
	AutoDiff powz = pow(z1, z2);
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
	    AutoDiff x1(3.9,seed_x1);
	    std::vector<double> seed_x2;
	    seed_x2.push_back(1.0);
	    AutoDiff x2(1.8,seed_x2);
    	
    	AutoDiff powx = pow(x1, x2);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vectors dimension not matched!"));
    }
    
    try {
    	std::vector<double> seed_y1;
	    seed_y1.push_back(1.3);
	    seed_y1.push_back(1.3);
	    AutoDiff y1(-3.9,seed_y1);
	    std::vector<double> seed_y2;
	    seed_y2.push_back(1.0);
	    seed_y2.push_back(1.0);
	    AutoDiff y2(1.8,seed_y2);
    	
    	AutoDiff powy = pow(y1, y2);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    
    try {
    	std::vector<double> seed_w1;
	    seed_w1.push_back(1.3);
	    seed_w1.push_back(1.3);
	    AutoDiff w1(0,seed_w1);
	    std::vector<double> seed_w2;
	    seed_w2.push_back(1.0);
	    seed_w2.push_back(1.0);
	    AutoDiff w2(1.8,seed_w2);
    	
    	AutoDiff poww = pow(w1, w2);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0!"));
    }
}

// double ^ AutoDiff (e.g. 2^x)
TEST(MATH,RIGHTPOW){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff powx = pow(2.0, x);
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
	    AutoDiff y1(3.9,seed_y1);
    	
    	AutoDiff powy = pow(-0.2, y1);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
    
    try {
    	std::vector<double> seed_w1;
	    seed_w1.push_back(1.3);
	    seed_w1.push_back(1.3);
	    AutoDiff w1(3.8,seed_w1);
    	
    	AutoDiff poww = pow(0, w1);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0!"));
    }
}

/////////////////////////////////////////// EXP TESTS
TEST(MATH,EXP){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff expx = exp(x);
	EXPECT_NEAR(expx.val(),exp(0.5),DTOL);
	EXPECT_EQ(expx.gradient().size(),1);
    EXPECT_EQ(expx.countVar(),1);
	EXPECT_NEAR(expx.dval_wrt(0), exp(0.5) * 4.0, DTOL);
	EXPECT_NEAR(expx.gradient().at(0), exp(0.5) * 4.0, DTOL);
}


/////////////////////////////////////////// LOG TESTS
TEST(MATH,LOG){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);
	AutoDiff logx = log(x);
	EXPECT_NEAR(logx.val(),log(0.5),DTOL);
	EXPECT_EQ(logx.gradient().size(),1);
    EXPECT_EQ(logx.countVar(),1);
	EXPECT_NEAR(logx.dval_wrt(0), (1/(0.5)) * 4.0, DTOL);
	EXPECT_NEAR(logx.gradient().at(0), (1/(0.5)) * 4.0, DTOL);

	// test error msg
	try {
    	std::vector<double> seed_x1;
	    seed_x1.push_back(1.3);
	    AutoDiff x1(-1.0,seed_x1);
    	AutoDiff logx1 = log(x1);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }

    try {
    	std::vector<double> seed_w1;
	    seed_w1.push_back(1.3);
	    seed_w1.push_back(1.3);
	    AutoDiff w1(0,seed_w1);
    	
    	AutoDiff logw1 = log(w1);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value equals 0!"));
    }
}

TEST(MATH,LOG10){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);
	AutoDiff logx = log10(x);
	EXPECT_NEAR(logx.val(),log10(0.5),DTOL);
	EXPECT_EQ(logx.gradient().size(),1);
    EXPECT_EQ(logx.countVar(),1);
	EXPECT_NEAR(logx.dval_wrt(0), (1/(0.5)) * 4.0/log(10), DTOL);
	EXPECT_NEAR(logx.gradient().at(0), (1/(0.5)) * 4.0/log(10), DTOL);

	// test error msg
	try {
    	std::vector<double> seed_x1;
	    seed_x1.push_back(1.3);
	    AutoDiff x1(-1.0,seed_x1);
    	AutoDiff logx1 = log(x1);
        FAIL() << "Expected std::domain_error";
    }
    catch(std::domain_error const & err) {
        EXPECT_EQ(err.what(),std::string("Value less than 0! NaN occurs!"));
    }
}

/////////////////////////////////////////// PRINT

TEST(IOSTREAM, PRINT){
	// single variable
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);
	testing::internal::CaptureStdout();
	std::cout << x;
	string output_x = testing::internal::GetCapturedStdout();
	string expected_x = "Information of AutoDiff object: \nValue at 0.5. \
1 variable(s) in total.\n   0th variable: dval = 4\n";
	EXPECT_TRUE(output_x.compare(expected_x)==0);

	// three variables
	std::vector<double> seed_y;
	seed_y.push_back(4.0);
	seed_y.push_back(5.0);
	seed_y.push_back(6.0);
	AutoDiff y(0.5,seed_y);
	testing::internal::CaptureStdout();
	std::cout << y;
	string output_y = testing::internal::GetCapturedStdout();
	string expected_y = "Information of AutoDiff object: \nValue at 0.5. \
3 variable(s) in total.\n   0th variable: dval = 4\n   1th variable: dval = 5\n   2th variable: dval = 6\n";
	EXPECT_TRUE(output_y.compare(expected_y)==0);
}


/////////////////////////////////////////// TRIG FUNCTION TESTS
// sin AutoDiff 
TEST(MATH,SIN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff sinx = sin(x);
	EXPECT_NEAR(sinx.val(),sin(0.5),DTOL);
	EXPECT_EQ(sinx.gradient().size(),1);
    EXPECT_EQ(sinx.countVar(),1);
	EXPECT_NEAR(sinx.dval_wrt(0), cos(0.5)*4.0, DTOL);
	EXPECT_NEAR(sinx.gradient().at(0), cos(0.5)*4.0, DTOL);
}

// cos AutoDiff
TEST(MATH,COS){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff cosx = cos(x);
	EXPECT_NEAR(cosx.val(),cos(0.5),DTOL);
	EXPECT_EQ(cosx.gradient().size(),1);
    EXPECT_EQ(cosx.countVar(),1);
	EXPECT_NEAR(cosx.dval_wrt(0), -sin(0.5)*4.0, DTOL);
	EXPECT_NEAR(cosx.gradient().at(0), -sin(0.5)*4.0, DTOL);
}

// tan AutoDiff
TEST(MATH,TAN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff tanx = tan(x);
	EXPECT_NEAR(tanx.val(),tan(0.5),DTOL);
	EXPECT_EQ(tanx.gradient().size(),1);
    EXPECT_EQ(tanx.countVar(),1);
	EXPECT_NEAR(tanx.dval_wrt(0), 4.0/(cos(0.5)*cos(0.5)), DTOL);
	EXPECT_NEAR(tanx.gradient().at(0), 4.0/(cos(0.5)*cos(0.5)), DTOL);
}

// arcsin AutoDiff
TEST(MATH,ARCSIN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff arcsinx = asin(x);
	EXPECT_NEAR(arcsinx.val(),asin(0.5),DTOL);
	EXPECT_EQ(arcsinx.gradient().size(),1);
    EXPECT_EQ(arcsinx.countVar(),1);
	EXPECT_NEAR(arcsinx.dval_wrt(0),(1/sqrt(1-pow(0.5, 2)))*4.0,DTOL);
	EXPECT_NEAR(arcsinx.gradient().at(0),(1/sqrt(1-pow(0.5, 2)))*4.0,DTOL);
}

// arccos AutoDiff
TEST(MATH,ARCCOS){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff arccosx = acos(x);
	EXPECT_NEAR(arccosx.val(),acos(0.5),DTOL);
	EXPECT_EQ(arccosx.gradient().size(),1);
    EXPECT_EQ(arccosx.countVar(),1);
	EXPECT_NEAR(arccosx.dval_wrt(0), -(1/sqrt(1 - pow(0.5, 2))) * 4.0,DTOL);
	EXPECT_NEAR(arccosx.gradient().at(0),-(1/sqrt(1-pow(0.5, 2)))*4.0,DTOL);
}

// arctan AutoDiff
TEST(MATH,ARCTAN){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(0.5,seed_x);

	AutoDiff arctanx = atan(x);
	EXPECT_NEAR(arctanx.val(),atan(0.5),DTOL);
	EXPECT_EQ(arctanx.gradient().size(),1);
    EXPECT_EQ(arctanx.countVar(),1);
	EXPECT_NEAR(arctanx.dval_wrt(0), (1/(1+pow(0.5, 2))) * 4.0,DTOL);
	EXPECT_NEAR(arctanx.gradient().at(0),(1/(1+pow(0.5, 2))) * 4.0,DTOL);
}

// sinh AutoDiff
TEST(MATH,SINH){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(-0.5,seed_x);

	AutoDiff sinhx = sinh(x);
	EXPECT_NEAR(sinhx.val(),sinh(-0.5),DTOL);
	EXPECT_EQ(sinhx.gradient().size(),1);
    EXPECT_EQ(sinhx.countVar(),1);
	EXPECT_NEAR(sinhx.dval_wrt(0),cosh(-0.5) * 4.0, DTOL);
	EXPECT_NEAR(sinhx.gradient().at(0),cosh(-0.5) * 4.0, DTOL);
}

// cosh AutoDiff
TEST(MATH,COSH){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(-0.5,seed_x);

	AutoDiff coshx = cosh(x);
	EXPECT_NEAR(coshx.val(),cosh(-0.5),DTOL);
	EXPECT_EQ(coshx.gradient().size(),1);
    EXPECT_EQ(coshx.countVar(),1);
	EXPECT_NEAR(coshx.dval_wrt(0),sinh(-0.5) * 4.0, DTOL);
	EXPECT_NEAR(coshx.gradient().at(0),sinh(-0.5) * 4.0, DTOL);
}

// tanh AutoDiff
TEST(MATH,TANH){
	std::vector<double> seed_x;
	seed_x.push_back(4.0);
	AutoDiff x(-0.5,seed_x);

	AutoDiff tanhx = tanh(x);
	EXPECT_NEAR(tanhx.val(),tanh(-0.5),DTOL);
	EXPECT_EQ(tanhx.gradient().size(),1);
    EXPECT_EQ(tanhx.countVar(),1);
	EXPECT_NEAR(tanhx.dval_wrt(0),(1/pow(cosh(-0.5), 2)) * 4.0, DTOL);
	EXPECT_NEAR(tanhx.gradient().at(0),(1/pow(cosh(-0.5), 2)) * 4.0, DTOL);
}