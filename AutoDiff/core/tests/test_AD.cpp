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

/////////////////////////////////////////// ADD TESTS
// autodiff + autodiff
TEST(OPERATOR,ADD){
	AutoDiff x(-0.5,4.0);
	AutoDiff y(0.5,4.3);
	AutoDiff sum = x + y;
	
	EXPECT_NEAR(sum.getVal(),0.0,DTOL);
    EXPECT_NEAR(sum.getDer(),8.3,DTOL);
}

// autodiff + double
TEST(OPERATOR,ADDAFTER){
	AutoDiff x(-0.5,4.0);
	double y = 9.0;
	AutoDiff sum = x + y;
	
	EXPECT_NEAR(sum.getVal(),8.5,DTOL);
    EXPECT_NEAR(sum.getDer(),4.0,DTOL);
}

// double + autodiff
TEST(OPERATOR,ADDBEFORE){
	double x = 9.0;
	AutoDiff y(-0.5,4.0);
	AutoDiff sum = x + y;
	
	EXPECT_NEAR(sum.getVal(),8.5,DTOL);
    EXPECT_NEAR(sum.getDer(),4.0,DTOL);
}


/////////////////////////////////////////// SUB TESTS
// autodiff - autodiff
TEST(OPERATOR,SUB){
	AutoDiff x(-0.5,4.0);
	AutoDiff y(0.5,4.3);
	AutoDiff sum = x - y;
	
	EXPECT_NEAR(sum.getVal(),-1.0,DTOL);
    EXPECT_NEAR(sum.getDer(),-0.3,DTOL);
}

// autodiff - double
TEST(OPERATOR,SUBAFTER){
	AutoDiff x(-0.5,4.0);
	double y = 9.0;
	AutoDiff sum = x - y;
	
	EXPECT_NEAR(sum.getVal(),-9.5,DTOL);
    EXPECT_NEAR(sum.getDer(),4.0,DTOL);
}

// double - autodiff
TEST(OPERATOR,SUBBEFORE){
	double x = 9.0;
	AutoDiff y(-0.5,4.0);
	AutoDiff sum = x - y;
	
	EXPECT_NEAR(sum.getVal(),8.5,DTOL);
    EXPECT_NEAR(sum.getDer(),-4.0,DTOL);
}


/////////////////////////////////////////// TIMES TESTS
// autodiff * autodiff
TEST(OPERATOR,TIMES){
	AutoDiff x(2.0,4.0);
	AutoDiff y(5.0,3.0);
	AutoDiff prod = x * y;
	
	EXPECT_NEAR(prod.getVal(),10.0,DTOL);
    EXPECT_NEAR(prod.getDer(),26.0,DTOL);
}

// autodiff * double
TEST(OPERATOR,TIMESAFTER){
	AutoDiff x(5.0,3.0);
	double y = 2.0;
	AutoDiff prod = x * y;
	
	EXPECT_NEAR(prod.getVal(),10.0,DTOL);
    EXPECT_NEAR(prod.getDer(),6.0,DTOL);
}

// double * autodiff
TEST(OPERATOR,TIMESBEFORE){
	double x = 2.0;
	AutoDiff y(5.0,3.0);
	AutoDiff prod = x * y;
	
	EXPECT_NEAR(prod.getVal(),10.0,DTOL);
    EXPECT_NEAR(prod.getDer(),6.0,DTOL);
}


/////////////////////////////////////////// DIVIDE TESTS
// autodiff / autodiff
TEST(OPERATOR,QUO){
	AutoDiff x(20.0,5.0);
	AutoDiff y(10.0,5.0);
	AutoDiff quo = x / y;
	
	EXPECT_NEAR(quo.getVal(),2.0,DTOL);
    EXPECT_NEAR(quo.getDer(),-0.5,DTOL);
}

// autodiff / double
TEST(OPERATOR,QUOAFTER){
	AutoDiff x(10.0,5.0);
	double y = 5.0;
	AutoDiff quo = x / y;
	
	EXPECT_NEAR(quo.getVal(),2.0,DTOL);
    EXPECT_NEAR(quo.getDer(),1.0,DTOL);
}

// double * autodiff
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
	EXPECT_NEAR(tanx.getVal(),exp(-0.5),DTOL);
	EXPECT_NEAR(tanx.getDer(),exp(-0.5) * 4.0, DTOL);
}


/////////////////////////////////////////// LOG TESTS
TEST(MATH,LOG){
	AutoDiff x(-0.5,4.0);
	AutoDiff logx = log(x);
	EXPECT_NEAR(logx.getVal(),log(-0.5),DTOL);
	EXPECT_NEAR(tanx.getDer(),(1/(-0.5)) * 4.0, DTOL);
}


/////////////////////////////////////////// POW TESTS
// autodiff ^ double (e.g. x^2)
TEST(MATH,LEFTPOW){
	AutoDiff x(-0.5,4.0);
	AutoDiff powx = pow(x, 2.0);
	EXPECT_NEAR(powx.getVal(),pow(-0.5, 2.0),DTOL);
	EXPECT_NEAR(powx.getDer(),2.0*pow(-0.5, 1.0), DTOL);
}

// autodiff & autodiff (e.g. x^y)
TEST(MATH,POW_TWOVAR){
	AutoDiff x(-0.5,4.0);
	AutoDiff y(2.0,3.0);
	AutoDiff powxy = pow(x, y);
	EXPECT_NEAR(powxy.getVal(),pow(-0.5, 2.0),DTOL);
	EXPECT_NEAR(powxy.getDer(),pow(-0.5, 2.0) * 3.0 * log(-0.5) + pow(-0.5, 2.0 - 1.0) * 2.0 * 4.0, DTOL);
}

// double ^ autodiff (e.g. 2^x)
TEST(MATH,RIGHTPOW){
	AutoDiff x(-0.5,4.0);
	AutoDiff powx = pow(2.0, x);
	EXPECT_NEAR(powx.getVal(),pow(2.0, -0.5),DTOL);
	EXPECT_NEAR(powx.getDer(),log(2.0) * 4.0 * pow(2, -0.5), DTOL);
}


/////////////////////////////////////////// TRIG FUNCTION TESTS
// sin autodiff
TEST(MATH,SIN){
	AutoDiff x(-0.5,4.0);
	AutoDiff sinx = sin(x);
	EXPECT_NEAR(sinx.getVal(),sin(-0.5),DTOL);
	EXPECT_NEAR(sinx.getDer(),cos(-0.5)*4.0,DTOL);
}

// cos autodiff
TEST(MATH,COS){
	AutoDiff x(-0.5,4.0);
	AutoDiff cosx = cos(x);
	EXPECT_NEAR(cosx.getVal(),cos(-0.5),DTOL);
	EXPECT_NEAR(cosx.getDer(),-sin(-0.5)*4.0,DTOL);
}

// tan autodiff
TEST(MATH,TAN){
	AutoDiff x(-0.5,4.0);
	AutoDiff tanx = tan(x);
	EXPECT_NEAR(tanx.getVal(),cos(-0.5),DTOL);
	EXPECT_NEAR(tanx.getDer(), (1/pow(cos(-0.5), 2)) * 4.0,DTOL);
}

// arcsin autodiff
TEST(MATH,ARCSIN){
	AutoDiff x(-0.5,4.0);
	AutoDiff arcsinx = asin(x);
	EXPECT_NEAR(arcsinx.getVal(),asin(-0.5),DTOL);
	EXPECT_NEAR(arcsinx.getDer(), (1/pow(cos(-0.5), 2)) * 4.0,DTOL);
}

// arccos autodiff
TEST(MATH,ARCCOS){
	AutoDiff x(-0.5,4.0);
	AutoDiff arcsinx = acos(x);
	EXPECT_NEAR(tanx.getVal(),acos(-0.5),DTOL);
	EXPECT_NEAR(tanx.getDer(), -(1/sqrt(1 - pow(-0.5, 2))) * 4.0,DTOL);
}

// arctan autodiff
TEST(MATH,ARCTAN){
	AutoDiff x(-0.5,4.0);
	AutoDiff arctanx = atan(x);
	EXPECT_NEAR(tanx.getVal(),atan(-0.5),DTOL);
	EXPECT_NEAR(tanx.getDer(), (1/(1+pow(-0.5, 2))) * 4.0,DTOL);
}

// sinh autodiff
TEST(MATH,SINH){
	AutoDiff x(-0.5,4.0);
	AutoDiff sinhx = sinh(x);
	EXPECT_NEAR(sinhx.getVal(),sinh(-0.5),DTOL);
	EXPECT_NEAR(sinhx.getDer(),cosh(-0.5) * 4.0, DTOL);
}

// cosh autodiff
TEST(MATH,COSH){
	AutoDiff x(-0.5,4.0);
	AutoDiff coshx = cosh(x);
	EXPECT_NEAR(coshx.getVal(),cosh(-0.5),DTOL);
	EXPECT_NEAR(coshx.getDer(),sinh(-0.5) * 4.0, DTOL);
}

// tanh autodiff
TEST(MATH,TANH){
	AutoDiff x(-0.5,4.0);
	AutoDiff tanhx = tanh(x);
	EXPECT_NEAR(tanhx.getVal(),tanhx(-0.5),DTOL);
	EXPECT_NEAR(tanhx.getDer(),(1/pow(cosh(-0.5), 2)) * 4.0, DTOL);
}