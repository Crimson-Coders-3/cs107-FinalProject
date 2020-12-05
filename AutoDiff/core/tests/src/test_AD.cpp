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
    try {x.dval_wrt(1);x.set_dval_wrt(1,3.0);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range!"));
    }
}

/////////////////////////////////////////// ADD TESTS
// AutoDiff += double
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

/*
/////////////////////////////////////////// SUB TESTS
// AutoDiff - AutoDiff
TEST(OPERATOR,SUB){
	AutoDiff x(-0.5,4.0);
	AutoDiff y(0.5,4.3);
	AutoDiff sum = x - y;
	
	EXPECT_NEAR(sum.getVal(),-1.0,DTOL);
    EXPECT_NEAR(sum.getDer(),-0.3,DTOL);
}

// AutoDiff - double
TEST(OPERATOR,SUBAFTER){
	AutoDiff x(-0.5,4.0);
	double y = 9.0;
	AutoDiff sum = x - y;
	
	EXPECT_NEAR(sum.getVal(),-9.5,DTOL);
    EXPECT_NEAR(sum.getDer(),4.0,DTOL);
}

// double - AutoDiff
TEST(OPERATOR,SUBBEFORE){
	double x = 9.0;
	AutoDiff y(-0.5,4.0);
	AutoDiff sum = x - y;
	
	EXPECT_NEAR(sum.getVal(),9.5,DTOL);
    EXPECT_NEAR(sum.getDer(),-4.0,DTOL);
}


/////////////////////////////////////////// TIMES TESTS
// AutoDiff * AutoDiff
TEST(OPERATOR,TIMES){
	AutoDiff x(2.0,4.0);
	AutoDiff y(5.0,3.0);
	AutoDiff prod = x * y;
	
	EXPECT_NEAR(prod.getVal(),10.0,DTOL);
    EXPECT_NEAR(prod.getDer(),26.0,DTOL);
}

// AutoDiff * double
TEST(OPERATOR,TIMESAFTER){
	AutoDiff x(5.0,3.0);
	double y = 2.0;
	AutoDiff prod = x * y;
	
	EXPECT_NEAR(prod.getVal(),10.0,DTOL);
    EXPECT_NEAR(prod.getDer(),6.0,DTOL);
}

// double * AutoDiff
TEST(OPERATOR,TIMESBEFORE){
	double x = 2.0;
	AutoDiff y(5.0,3.0);
	AutoDiff prod = x * y;
	
	EXPECT_NEAR(prod.getVal(),10.0,DTOL);
    EXPECT_NEAR(prod.getDer(),6.0,DTOL);
}


/////////////////////////////////////////// DIVIDE TESTS
// AutoDiff / AutoDiff
TEST(OPERATOR,QUO){
	AutoDiff x(20.0,5.0);
	AutoDiff y(10.0,5.0);
	AutoDiff quo = x / y;
	
	EXPECT_NEAR(quo.getVal(),2.0,DTOL);
    EXPECT_NEAR(quo.getDer(),-0.5,DTOL);
}

// AutoDiff / double
TEST(OPERATOR,QUOAFTER){
	AutoDiff x(10.0,5.0);
	double y = 5.0;
	AutoDiff quo = x / y;
	
	EXPECT_NEAR(quo.getVal(),2.0,DTOL);
    EXPECT_NEAR(quo.getDer(),1.0,DTOL);
}

// double * AutoDiff
TEST(OPERATOR,QUOBEFORE){
	double x = 10.0;
	AutoDiff y(5.0,5.0);
	AutoDiff quo = x / y;
	
	EXPECT_NEAR(quo.getVal(),2.0,DTOL);
    EXPECT_NEAR(quo.getDer(),-2.0,DTOL);
}


/////////////////////////////////////////// EXP TESTS
TEST(MATH,EXP){
	AutoDiff x(-0.5,4.0);
	AutoDiff expx = exp(x);
	EXPECT_NEAR(expx.getVal(),exp(-0.5),DTOL);
	EXPECT_NEAR(expx.getDer(),exp(-0.5) * 4.0, DTOL);
}


/////////////////////////////////////////// LOG TESTS
TEST(MATH,LOG){
	AutoDiff x(0.5,4.0);
	AutoDiff logx = log(x);
	EXPECT_NEAR(logx.getVal(),log(0.5),DTOL);
	EXPECT_NEAR(logx.getDer(),(1/(0.5)) * 4.0, DTOL);
}


/////////////////////////////////////////// POW TESTS
// AutoDiff ^ double (e.g. x^2)
TEST(MATH,LEFTPOW){
	AutoDiff x(-0.5,4.0);
	AutoDiff powx = pow(x, 2.0);
	EXPECT_NEAR(powx.getVal(),pow(-0.5, 2.0),DTOL);
	EXPECT_NEAR(powx.getDer(),4.0*2.0*pow(-0.5, 1.0), DTOL);
}

// AutoDiff & AutoDiff (e.g. x^y)
TEST(MATH,POW_TWOVAR){
	AutoDiff x(0.5,4.0);
	AutoDiff y(2.0,3.0);
	AutoDiff powxy = pow(x, y);
	EXPECT_NEAR(powxy.getVal(),pow(0.5, 2.0),DTOL);
	EXPECT_NEAR(powxy.getDer(),pow(0.5, 2.0) * 3.0 * log(0.5) + pow(0.5, 2.0 - 1.0) * 2.0 * 4.0, DTOL);
}

// double ^ AutoDiff (e.g. 2^x)
TEST(MATH,RIGHTPOW){
	AutoDiff x(-0.5,4.0);
	AutoDiff powx = pow(2.0, x);
	EXPECT_NEAR(powx.getVal(),pow(2.0, -0.5),DTOL);
	EXPECT_NEAR(powx.getDer(),log(2.0) * 4.0 * pow(2, -0.5), DTOL);
}


/////////////////////////////////////////// TRIG FUNCTION TESTS
// sin AutoDiff
TEST(MATH,SIN){
	AutoDiff x(-0.5,4.0);
	AutoDiff sinx = sin(x);
	EXPECT_NEAR(sinx.getVal(),sin(-0.5),DTOL);
	EXPECT_NEAR(sinx.getDer(),cos(-0.5)*4.0,DTOL);
}

// cos AutoDiff
TEST(MATH,COS){
	AutoDiff x(-0.5,4.0);
	AutoDiff cosx = cos(x);
	EXPECT_NEAR(cosx.getVal(),cos(-0.5),DTOL);
	EXPECT_NEAR(cosx.getDer(),-sin(-0.5)*4.0,DTOL);
}

// tan AutoDiff
TEST(MATH,TAN){
	AutoDiff x(-0.5,4.0);
	AutoDiff tanx = tan(x);
	EXPECT_NEAR(tanx.getVal(),tan(-0.5),DTOL);
	EXPECT_NEAR(tanx.getDer(), (1/pow(cos(-0.5), 2)) * 4.0,DTOL);
}

// arcsin AutoDiff
TEST(MATH,ARCSIN){
	AutoDiff x(-0.5,4.0);
	AutoDiff arcsinx = asin(x);
	EXPECT_NEAR(arcsinx.getVal(),asin(-0.5),DTOL);
	EXPECT_NEAR(arcsinx.getDer(),(1/sqrt(1-pow(-0.5, 2)))*4.0,DTOL);
}

// arccos AutoDiff
TEST(MATH,ARCCOS){
	AutoDiff x(-0.5,4.0);
	AutoDiff arcsinx = acos(x);
	EXPECT_NEAR(arcsinx.getVal(),acos(-0.5),DTOL);
	EXPECT_NEAR(arcsinx.getDer(), -(1/sqrt(1 - pow(-0.5, 2))) * 4.0,DTOL);
}

// arctan AutoDiff
TEST(MATH,ARCTAN){
	AutoDiff x(-0.5,4.0);
	AutoDiff arctanx = atan(x);
	EXPECT_NEAR(arctanx.getVal(),atan(-0.5),DTOL);
	EXPECT_NEAR(arctanx.getDer(), (1/(1+pow(-0.5, 2))) * 4.0,DTOL);
}

// sinh AutoDiff
TEST(MATH,SINH){
	AutoDiff x(-0.5,4.0);
	AutoDiff sinhx = sinh(x);
	EXPECT_NEAR(sinhx.getVal(),sinh(-0.5),DTOL);
	EXPECT_NEAR(sinhx.getDer(),cosh(-0.5) * 4.0, DTOL);
}

// cosh AutoDiff
TEST(MATH,COSH){
	AutoDiff x(-0.5,4.0);
	AutoDiff coshx = cosh(x);
	EXPECT_NEAR(coshx.getVal(),cosh(-0.5),DTOL);
	EXPECT_NEAR(coshx.getDer(),sinh(-0.5) * 4.0, DTOL);
}

// tanh AutoDiff
TEST(MATH,TANH){
	AutoDiff x(-0.5,4.0);
	AutoDiff tanhx = tanh(x);
	EXPECT_NEAR(tanhx.getVal(),tanh(-0.5),DTOL);
	EXPECT_NEAR(tanhx.getDer(),(1/pow(cosh(-0.5), 2)) * 4.0, DTOL);
}

/////////////////////////////////////////// Nested Operation TESTS

TEST(MATH,NESTED){
	AutoDiff x(-0.5,4.0);
	AutoDiff res = cos(pow(sin(x),AutoDiff(2.0)));
	EXPECT_NEAR(res.getVal(),cos(pow(sin(-0.5),2.0)),DTOL);
	EXPECT_NEAR(res.getDer(),-sin(pow(sin(-0.5),2.0))*2*sin(-0.5)*cos(-0.5), DTOL);
}
*/