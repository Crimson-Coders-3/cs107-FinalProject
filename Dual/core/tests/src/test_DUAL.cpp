/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "Dual.h"
#include "Dual.cpp"
#include "test_vars.h"

void DualLibrary_testcheck(){
    printf("Starting AutoDiff Dual tests...\n");
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

TEST(MemberOperator,AssignScalar){

	Dual y1(3.9,9.3);
	y1 = 2.9;
	EXPECT_NEAR(y1.real(),2.9,DTOL); 
	EXPECT_NEAR(y1.dual(),0.0,DTOL);
}

TEST(MemberOperator,AddScalar){

	Dual y(3.9,9.3);
	y += 2.8;
	EXPECT_NEAR(y.real(),3.9+2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3,DTOL);
}

TEST(MemberOperator,SubstractScalar){
	Dual y(3.9,9.3);
	y -= 2.8;
	EXPECT_NEAR(y.real(),3.9-2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3,DTOL);
}

TEST(MemberOperator,MutiplyScalar){

	Dual y(3.9,9.3);
	y *= 2.8;
	EXPECT_NEAR(y.real(),3.9*2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3*2.8,DTOL);
}

TEST(MemberOperator,DivideScalar){
	Dual y(3.9,9.3);
	y /= 2.8;
	EXPECT_NEAR(y.real(),3.9/2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3/2.8,DTOL);
}

TEST(MemberOperator,AssignObject){


	Dual y1(3.9,9.3);
	Dual y2 = y1;
	EXPECT_NEAR(y2.real(),3.9,DTOL); 
	EXPECT_NEAR(y2.dual(),9.3,DTOL);

}

TEST(MemberOperator,AddObject){
	
	Dual y1(3.9,9.3);
	Dual y;
	y += y1;
	EXPECT_NEAR(y.real(),3.9,DTOL); 
	EXPECT_NEAR(y.dual(),10.3,DTOL);
	y += y1;
	EXPECT_NEAR(y.real(),3.9*2,DTOL); 
	EXPECT_NEAR(y.dual(),9.3+10.3,DTOL);

}


TEST(MemberOperator,SubstractObject){


	Dual y1(3.9,9.3);
	Dual y;
	y -= y1;
	EXPECT_NEAR(y.real(),-3.9,DTOL); 
	EXPECT_NEAR(y.dual(),-8.3,DTOL);
	y -= y1;
	EXPECT_NEAR(y.real(),-3.9*2,DTOL); 
	EXPECT_NEAR(y.dual(),-9.3-8.3,DTOL);

}

TEST(MemberOperator,MutiplyObject){

	Dual y1(3.0,9.0);
	Dual y = y1;
	y *= y1;
	EXPECT_NEAR(y.real(),9.0,DTOL); 
	EXPECT_NEAR(y.dual(),54.0,DTOL);
	y *= y1;
	EXPECT_NEAR(y.real(),27.0,DTOL); 
	EXPECT_NEAR(y.dual(),9*9.0+3*54.0,DTOL);

}


TEST(MemberOperator,DivideObject){
	
	Dual y1(3.0,9.0);
	Dual y(3.00,3.00);
	y /= y1;
	EXPECT_NEAR(y.real(),1.0,DTOL); 
	EXPECT_NEAR(y.dual(),-2.0,DTOL);
}

TEST(NonMemberOperator,IOstream){
	
	Dual y(3.0,9.0);
	testing::internal::CaptureStdout();
	cout << y;
	string output_y = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output_y.compare("3+9e")==0);

	Dual y1(3.2,9.0);
	testing::internal::CaptureStdout();
	cout << y1;
	string output_y1 = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output_y1.compare("3.2+9e")==0);
}

TEST(NonMemberOperator,Comparator){
	// equal sign
	Dual x(3.0,9.0);
	double real = 3.0;
	EXPECT_TRUE(x==3.0);
	EXPECT_TRUE(x==real);
	EXPECT_TRUE(real==x);
	Dual y(3.0,8.0);
	EXPECT_TRUE(x==y);

	// unequal sign
	Dual z(4.0,8.0);
	EXPECT_TRUE(x!=4);
	EXPECT_TRUE(4!=x);
	EXPECT_TRUE(z!=x);

	// strictly larger, smaller >, <
	EXPECT_TRUE(x<4);
	EXPECT_TRUE(4>x);
	EXPECT_TRUE(x<z);
	EXPECT_TRUE(z>x);
	EXPECT_TRUE(x>2);
	EXPECT_TRUE(2<x);

	// >=, <=
	EXPECT_TRUE(x<=4);
	EXPECT_TRUE(4>=x);
	EXPECT_TRUE(x>=2);
	EXPECT_TRUE(2<=x);
	EXPECT_TRUE(x<=z);
	EXPECT_TRUE(z>=x);
}

TEST(NonMemberOperator,Minus){
	Dual x(3.0,9.0);
	Dual neg_x = -x;
	EXPECT_EQ(neg_x.real(),-3); 
	EXPECT_EQ(neg_x.dual(),-9); 

	Dual y(-4.0,8.0);
	Dual diff1 = x - y;
	EXPECT_EQ(diff1.real(),7); 
	EXPECT_EQ(diff1.dual(),1);
	
	Dual diff2 = y - x;
	EXPECT_EQ(diff2.real(),-7); 
	EXPECT_EQ(diff2.dual(),-1);

	Dual diff3 = x - 3;
	EXPECT_EQ(diff3.real(),0); 
	EXPECT_EQ(diff3.dual(),9);

	Dual diff4 = 3 - x;
	EXPECT_EQ(diff4.real(),0); 
	EXPECT_EQ(diff4.dual(),-9);
}

TEST(NonMemberOperator,Add){
	Dual x(3,9);
	Dual y(-4,8);
	Dual sum1 = x + y;
	EXPECT_EQ(sum1.real(),-1); 
	EXPECT_EQ(sum1.dual(),17);
	
	Dual sum2 = y + x;
	EXPECT_EQ(sum2.real(),-1); 
	EXPECT_EQ(sum2.dual(),17);

	Dual sum3 = x + 3;
	EXPECT_EQ(sum3.real(),6); 
	EXPECT_EQ(sum3.dual(),9);

	Dual sum4 = 5 + x;
	EXPECT_EQ(sum4.real(),8); 
	EXPECT_EQ(sum4.dual(),9);
}

TEST(NonMemberOperator,Multiply){
	Dual x(3,9);
	Dual y(-4,8);
	Dual prod1 = x * y;
	EXPECT_EQ(prod1.real(),-12); 
	EXPECT_EQ(prod1.dual(),(-4)*9+3*8);
	
	Dual prod2 = y * x;
	EXPECT_EQ(prod2.real(),-12); 
	EXPECT_EQ(prod2.dual(),(-4)*9+3*8);

	Dual prod3 = x * 3;
	EXPECT_EQ(prod3.real(),9); 
	EXPECT_EQ(prod3.dual(),27);

	Dual prod4 = 5 * x;
	EXPECT_EQ(prod4.real(),15); 
	EXPECT_EQ(prod4.dual(),45);
}

TEST(NonMemberOperator,Divide){
	Dual x(3.0,9.0);
	Dual y(-4.0,8.0);
	Dual quo1 = x / y;
	EXPECT_NEAR(quo1.real(),-0.75,DTOL); 
	EXPECT_NEAR(quo1.dual(),(-9*4.0-3.0*8.0)/16,DTOL);

	Dual quo2 = x / 3.0;
	EXPECT_NEAR(quo2.real(),1.0,DTOL); 
	EXPECT_NEAR(quo2.dual(),3.0,DTOL);

	// (5.0+0e)/(3+9.0e) = 5/3 + (-5.0*9)/(9)
	Dual quo3 = 5.0 / x;
	EXPECT_NEAR(quo3.real(),5.0/3,DTOL); 
	EXPECT_NEAR(quo3.dual(),-5.0,DTOL);
}

TEST(MATH,ACOS){
	Dual x(-0.5,4.0);
	Dual acosx = acos(x);
	EXPECT_NEAR(acosx.real(),acos(-0.5),DTOL);
	EXPECT_NEAR(acosx.dual(),-4.0/sqrt(1 - 0.25),DTOL);
}

TEST(MATH,ASIN){
	Dual x(-0.5,4.0);
	Dual asinx = asin(x);
	EXPECT_NEAR(asinx.real(),asin(-0.5),DTOL);
	EXPECT_NEAR(asinx.dual(),4.0/sqrt(1 - 0.25),DTOL);
}

TEST(MATH,ATAN){
	Dual x(-0.5,4.0);
	Dual atanx = atan(x);
	EXPECT_NEAR(atanx.real(),atan(-0.5),DTOL);
	EXPECT_NEAR(atanx.dual(),4.0/(1 + 0.25),DTOL);
}

TEST(MATH,COS){
	Dual x(-0.5,4.0);
	Dual cosx = cos(x);
	EXPECT_NEAR(cosx.real(),cos(-0.5),DTOL);
	EXPECT_NEAR(cosx.dual(),sin(-0.5)*-4,DTOL);
}

TEST(MATH,COSH){
	Dual x(-0.5,4.0);
	Dual coshx = cosh(x);
	EXPECT_NEAR(coshx.real(),cosh(-0.5),DTOL);
	EXPECT_NEAR(coshx.dual(),sinh(-0.5)*4,DTOL);
}

TEST(MATH,EXP){
	Dual x(-0.5,4.0);
	Dual expx = exp(x);
	EXPECT_NEAR(expx.real(),exp(-0.5),DTOL);
	EXPECT_NEAR(expx.dual(),4*exp(-0.5),DTOL);
}

TEST(MATH,LOG){
	Dual x(0.5,4.0);
	Dual logx = log(x);
	EXPECT_NEAR(logx.real(),log(0.5),DTOL);
	EXPECT_NEAR(logx.dual(),4/0.5,DTOL);
}

TEST(MATH,LOG10){
	Dual x(0.5,4.0);
	Dual logx = log(x);
	EXPECT_NEAR(logx.real(),log(0.5),DTOL);
	EXPECT_NEAR(logx.dual(),4/0.5,DTOL);
}

TEST(MATH,POW){
	Dual x(0.5,4.0);
	Dual y(1.5,4.5);
	Dual powx = pow(x, y);
	EXPECT_NEAR(powx.real(),pow(0.5,1.5),DTOL);
	EXPECT_NEAR(powx.dual(),1.5*4.5*pow(0.5,1.5-1)*4.0,DTOL);
}

TEST(MATH,SIN){
	Dual x(-0.5,4.0);
	Dual sinx = sin(x);
	EXPECT_NEAR(sinx.real(),sin(-0.5),DTOL);
	EXPECT_NEAR(sinx.dual(),4.0*cos(-0.5),DTOL);
}

TEST(MATH,SINH){
	Dual x(0.5,4.0);
	Dual sinhx = sinh(x);
	EXPECT_NEAR(sinhx.real(),sinh(0.5),DTOL);
	EXPECT_NEAR(sinhx.dual(),4.0*cosh(0.5),DTOL);
}

TEST(MATH,SQRT){
	Dual x(0.5,4.0);
	Dual sqrtx = sqrt(x);
	EXPECT_NEAR(sqrtx.real(),sqrt(0.5),DTOL);
	EXPECT_NEAR(sqrtx.dual(),4.0 /(2 * sqrt(0.5)),DTOL);
}

TEST(MATH,TANH){
	Dual x(0.5,4.0);
	Dual tanhx = tanh(x);
	EXPECT_NEAR(tanhx.real(),tanh(0.5),DTOL);
	EXPECT_NEAR(tanhx.dual(),4.0*(1 - tanh(0.5) * tanh(0.5)),DTOL);
}

TEST(MATH,TAN){
	Dual x(0.5,4.0);
	Dual tanx = tan(x);
	EXPECT_NEAR(tanx.real(),tan(0.5),DTOL);
	EXPECT_NEAR(tanx.dual(),4.0 / cos(0.5 * cos(0.5)),DTOL);
}