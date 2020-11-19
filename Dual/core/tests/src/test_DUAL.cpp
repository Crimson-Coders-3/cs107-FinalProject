/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <cmath>

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

TEST(Getter,int){
    int real = 3;
    int dual = 7;
    Dual<int> x1(real,dual);

    /* test getters */
    EXPECT_EQ(x1.real(),real);  // note: EXECT_EQ used only for integers
    EXPECT_EQ(x1.dual(),dual);
}

TEST(Getter,double){
    double real = 3.3;
    double dual = 7.8;
    Dual<double> x1(real,dual);

    /* test getters */
    EXPECT_NEAR(x1.real(),real,DTOL);
    EXPECT_NEAR(x1.dual(),dual,DTOL);
}

TEST(Getter,float){
    float real = 3.3f;
    float dual = 7.8f;
    Dual<float> x1(real,dual);

    /* test getters */
    EXPECT_NEAR(x1.real(),real,DTOL);
    EXPECT_NEAR(x1.dual(),dual,DTOL);
}

TEST(Constructor,object){
	int real = 3;
    int dual = 7;
    /* test constructor using object of the same class */
    Dual<int> x1(real,dual);
	Dual<int> x2(x1);

    EXPECT_EQ(x2.real(),real);
    EXPECT_EQ(x2.dual(),dual);

    double real_d = 3.2;
    double dual_d = 7.19;
    Dual<double> y1(real_d,dual_d);
	Dual<double> y2(y1);

    EXPECT_NEAR(y2.real(),real_d,DTOL);
    EXPECT_NEAR(y2.dual(),dual_d,DTOL);

    float real_f = 3.2f;
    float dual_f = 2.1f;
    Dual<float> z1(real_f,dual_f);
	Dual<float> z2(z1);

    EXPECT_NEAR(z2.real(),real_f,DTOL);
    EXPECT_NEAR(z2.dual(),dual_f,DTOL);

    // now, trying different type casting
    // int->float, int->double, float->double
    Dual<float> f1(x1);
    Dual<double> d1(x1);
    Dual<double> d2(z1);
    EXPECT_NEAR(f1.real(),real,DTOL);
    EXPECT_NEAR(f1.dual(),dual,DTOL);
    EXPECT_NEAR(d1.real(),real,DTOL);
    EXPECT_NEAR(d1.dual(),dual,DTOL);
    EXPECT_NEAR(d2.real(),real_f,DTOL);
    EXPECT_NEAR(d2.dual(),dual_f,DTOL);
}

TEST(Constructor, default){
	/* test default constructor */
	Dual<int> x;
	EXPECT_EQ(x.real(),0);
    EXPECT_EQ(x.dual(),1);

    Dual<double> y;
	EXPECT_NEAR(y.real(), 0.00, DTOL);
	EXPECT_NEAR(y.dual(), 1.00, DTOL);

	Dual<float> z;
	EXPECT_NEAR(z.real(), 0.00f, DTOL);
	EXPECT_NEAR(z.dual(), 1.00f, DTOL);
}

TEST(Constructor, Scalar){
	/* test default constructor */
	Dual<int> x(1);
	EXPECT_EQ(x.real(),1);
    EXPECT_EQ(x.dual(),1);

    Dual<double> y(1.00);
	EXPECT_NEAR(y.real(), 1.00, DTOL);
	EXPECT_NEAR(y.dual(), 1.00, DTOL);

	Dual<float> z(1.00f);
	EXPECT_NEAR(z.real(), 1.00f, DTOL);
	EXPECT_NEAR(z.dual(), 1.00f, DTOL);
}

TEST(MemberOperator,AssignScalar){
	Dual<int> x1(3,9);
	x1 = 2;
	EXPECT_EQ(x1.real(),2); 
	EXPECT_EQ(x1.dual(),0);

	Dual<double> y1(3.9,9.3);
	y1 = 2.9;
	EXPECT_NEAR(y1.real(),2.9,DTOL); 
	EXPECT_NEAR(y1.dual(),0,DTOL);

	Dual<float> z1(3.9f,9.3f);
	z1 = 34.9;
	EXPECT_NEAR(z1.real(),34.9f,DTOL); 
	EXPECT_NEAR(z1.dual(),0,DTOL);
}

TEST(MemberOperator,AddScalar){
	Dual<int> x(3,9);
	x += 3;
	EXPECT_EQ(x.real(),3+3); 
	EXPECT_EQ(x.dual(),9);

	Dual<double> y(3.9,9.3);
	y += 2.8;
	EXPECT_NEAR(y.real(),3.9+2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3,DTOL);

	Dual<float> z(3.9f,9.3f);
	z += 2.7f;
	EXPECT_NEAR(z.real(),3.9f+2.7f,DTOL); 
	EXPECT_NEAR(z.dual(),9.3f,DTOL);
}

TEST(MemberOperator,SubstractScalar){
	Dual<int> x(3,9);
	x -= 3;
	EXPECT_EQ(x.real(),3-3); 
	EXPECT_EQ(x.dual(),9);

	Dual<double> y(3.9,9.3);
	y -= 2.8;
	EXPECT_NEAR(y.real(),3.9-2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3,DTOL);

	Dual<float> z(3.9f,9.3f);
	z -= 2.7f;
	EXPECT_NEAR(z.real(),3.9f-2.7f,DTOL); 
	EXPECT_NEAR(z.dual(),9.3f,DTOL);
}

TEST(MemberOperator,MutiplyScalar){
	Dual<int> x(3,9);
	x *= 3;
	EXPECT_EQ(x.real(),3*3); 
	EXPECT_EQ(x.dual(),9*3);

	Dual<double> y(3.9,9.3);
	y *= 2.8;
	EXPECT_NEAR(y.real(),3.9*2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3*2.8,DTOL);

	Dual<float> z(3.9f,9.3f);
	z *= 2.7f;
	EXPECT_NEAR(z.real(),3.9f*2.7f,DTOL); 
	EXPECT_NEAR(z.dual(),9.3f*2.7f,DTOL);
}

TEST(MemberOperator,DivideScalar){
	Dual<int> x(3,9);
	x /= 3;
	EXPECT_EQ(x.real(),3/3); 
	EXPECT_EQ(x.dual(),9/3);

	Dual<double> y(3.9,9.3);
	y /= 2.8;
	EXPECT_NEAR(y.real(),3.9/2.8,DTOL); 
	EXPECT_NEAR(y.dual(),9.3/2.8,DTOL);

	Dual<float> z(3.9f,9.3f);
	z /= 2.7f;
	EXPECT_NEAR(z.real(),3.9f/2.7f,DTOL); 
	EXPECT_NEAR(z.dual(),9.3f/2.7f,DTOL);
}

TEST(MemberOperator,AssignObject){
	Dual<int> x1(3,9);
	Dual<int> x2 = x1;
	EXPECT_EQ(x2.real(),3); 
	EXPECT_EQ(x2.dual(),9);

	Dual<double> y1(3.9,9.3);
	Dual<double> y2 = y1;
	EXPECT_NEAR(y2.real(),3.9,DTOL); 
	EXPECT_NEAR(y2.dual(),9.3,DTOL);

	Dual<float> z1(3.9f,9.3f);
	Dual<float> z2 = z1;
	EXPECT_NEAR(z2.real(),3.9f,DTOL); 
	EXPECT_NEAR(z2.dual(),9.3f,DTOL);
}

TEST(MemberOperator,AddObject){
	Dual<int> x1(3,9);
	Dual<int> x;
	x += x1;
	EXPECT_EQ(x.real(),3); 
	EXPECT_EQ(x.dual(),10);
	x += x1;
	EXPECT_EQ(x.real(),6); 
	EXPECT_EQ(x.dual(),19);

	Dual<double> y1(3.9,9.3);
	Dual<double> y;
	y += y1;
	EXPECT_NEAR(y.real(),3.9,DTOL); 
	EXPECT_NEAR(y.dual(),10.3,DTOL);
	y += y1;
	EXPECT_NEAR(y.real(),3.9*2,DTOL); 
	EXPECT_NEAR(y.dual(),9.3+10.3,DTOL);

	Dual<float> z1(3.9f,9.3f);
	Dual<float> z;
	z += z1;
	EXPECT_NEAR(z.real(),3.9f,DTOL); 
	EXPECT_NEAR(z.dual(),10.3f,DTOL);
	z += z1;
	EXPECT_NEAR(z.real(),3.9f*2,DTOL); 
	EXPECT_NEAR(z.dual(),9.3f+10.3f,DTOL);
}


TEST(MemberOperator,SubstractObject){
	Dual<int> x1(3,9);
	Dual<int> x;
	x -= x1;
	EXPECT_EQ(x.real(),-3); 
	EXPECT_EQ(x.dual(),-8);
	x -= x1;
	EXPECT_EQ(x.real(),-6); 
	EXPECT_EQ(x.dual(),-17);

	Dual<double> y1(3.9,9.3);
	Dual<double> y;
	y -= y1;
	EXPECT_NEAR(y.real(),-3.9,DTOL); 
	EXPECT_NEAR(y.dual(),-8.3,DTOL);
	y -= y1;
	EXPECT_NEAR(y.real(),-3.9*2,DTOL); 
	EXPECT_NEAR(y.dual(),-9.3-8.3,DTOL);

	Dual<float> z1(3.9f,9.3f);
	Dual<float> z;
	z -= z1;
	EXPECT_NEAR(z.real(),-3.9f,DTOL); 
	EXPECT_NEAR(z.dual(),-8.3f,DTOL);
	z -= z1;
	EXPECT_NEAR(z.real(),-3.9f*2,DTOL); 
	EXPECT_NEAR(z.dual(),-9.3f-8.3f,DTOL);
}

TEST(MemberOperator,MutiplyObject){
	// (3+9e) * (3+9e) = 9+81e^2+54e = 9+54e
	Dual<int> x1(3,9);
	Dual<int> x = x1;
	x *= x1;
	EXPECT_EQ(x.real(),9); 
	EXPECT_EQ(x.dual(),54);
	x *= x1;
	// (9+54e)*(3+9e) = 27+ ((9*9)+(3*54))e
	EXPECT_EQ(x.real(),27); 
	EXPECT_EQ(x.dual(),9*9+3*54);

	Dual<double> y1(3.0,9.0);
	Dual<double> y = y1;
	y *= y1;
	EXPECT_NEAR(y.real(),9.0,DTOL); 
	EXPECT_NEAR(y.dual(),54.0,DTOL);
	y *= y1;
	EXPECT_NEAR(y.real(),27.0,DTOL); 
	EXPECT_NEAR(y.dual(),9*9.0+3*54.0,DTOL);

	Dual<float> z1(3.0f,9.0f);
	Dual<float> z = z1;
	z *= z1;
	EXPECT_NEAR(z.real(),9.0f,DTOL); 
	EXPECT_NEAR(z.dual(),54.0f,DTOL);
	z *= z1;
	EXPECT_NEAR(z.real(),27.0f,DTOL); 
	EXPECT_NEAR(z.dual(),9*9.0f+3*54.0f,DTOL);
}


TEST(MemberOperator,DivideObject){
	// (u+u'e)/(v+v'e) = u/v + (u'v-v'u)e/v^2
	Dual<int> x1(3,9);
	Dual<int> x(3,3);
	x /= x1;
	EXPECT_EQ(x.real(),1); 
	// (3*3-9*3)/3**2 = (-18)/9
	EXPECT_EQ(x.dual(),-2);
	
	Dual<double> y1(3.0,9.0);
	Dual<double> y(3.00,3.00);
	y /= y1;
	EXPECT_NEAR(y.real(),1.0,DTOL); 
	EXPECT_NEAR(y.dual(),-2.0,DTOL);

	Dual<float> z1(3.0f,9.0f);
	Dual<float> z(3.0f,3.0f);
	z /= z1;
	EXPECT_NEAR(z.real(),1.0f,DTOL); 
	EXPECT_NEAR(z.dual(),-2.0f,DTOL);
}

TEST(NonMemberOperator,IOstream){
	Dual<int> x(3,9);
	testing::internal::CaptureStdout();
	cout << x;
	string output_x = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output_x.compare("3+9e")==0);

	Dual<double> y(3.0,9.0);
	testing::internal::CaptureStdout();
	cout << y;
	string output_y = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output_y.compare("3+9e")==0);

	Dual<double> y1(3.2,9.0);
	testing::internal::CaptureStdout();
	cout << y1;
	string output_y1 = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output_y1.compare("3.2+9e")==0);

	Dual<float> z(3.2f,9.0f);
	testing::internal::CaptureStdout();
	cout << z;
	string output_z = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output_z.compare("3.2+9e")==0);
}

TEST(NonMemberOperator,Comparator){
	// equal sign
	Dual<int> x(3,9);
	int real = 3;
	EXPECT_TRUE(x==3);
	EXPECT_TRUE(x==real);
	EXPECT_TRUE(real==x);
	Dual<int> y(3,8);
	EXPECT_TRUE(x==y);

	// unequal sign
	Dual<int> z(4,8);
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
	Dual<int> x(3,9);
	Dual<int> neg_x = -x;
	EXPECT_EQ(neg_x.real(),-3); 
	EXPECT_EQ(neg_x.dual(),-9); 

	Dual<int> y(-4,8);
	Dual<int> diff1 = x - y;
	EXPECT_EQ(diff1.real(),7); 
	EXPECT_EQ(diff1.dual(),1);
	
	Dual<int> diff2 = y - x;
	EXPECT_EQ(diff2.real(),-7); 
	EXPECT_EQ(diff2.dual(),-1);

	Dual<int> diff3 = x - 3;
	EXPECT_EQ(diff3.real(),0); 
	EXPECT_EQ(diff3.dual(),9);

	Dual<int> diff4 = 3 - x;
	EXPECT_EQ(diff4.real(),0); 
	EXPECT_EQ(diff4.dual(),-9);
}

TEST(NonMemberOperator,Add){
	Dual<int> x(3,9);
	Dual<int> y(-4,8);
	Dual<int> sum1 = x + y;
	EXPECT_EQ(sum1.real(),-1); 
	EXPECT_EQ(sum1.dual(),17);
	
	Dual<int> sum2 = y + x;
	EXPECT_EQ(sum2.real(),-1); 
	EXPECT_EQ(sum2.dual(),17);

	Dual<int> sum3 = x + 3;
	EXPECT_EQ(sum3.real(),6); 
	EXPECT_EQ(sum3.dual(),9);

	Dual<int> sum4 = 5 + x;
	EXPECT_EQ(sum4.real(),8); 
	EXPECT_EQ(sum4.dual(),9);
}

TEST(NonMemberOperator,Multiply){
	Dual<int> x(3,9);
	Dual<int> y(-4,8);
	Dual<int> prod1 = x * y;
	EXPECT_EQ(prod1.real(),-12); 
	EXPECT_EQ(prod1.dual(),(-4)*9+3*8);
	
	Dual<int> prod2 = y * x;
	EXPECT_EQ(prod2.real(),-12); 
	EXPECT_EQ(prod2.dual(),(-4)*9+3*8);

	Dual<int> prod3 = x * 3;
	EXPECT_EQ(prod3.real(),9); 
	EXPECT_EQ(prod3.dual(),27);

	Dual<int> prod4 = 5 * x;
	EXPECT_EQ(prod4.real(),15); 
	EXPECT_EQ(prod4.dual(),45);
}

TEST(NonMemberOperator,Divide){
	Dual<double> x(3.0,9.0);
	Dual<double> y(-4.0,8.0);
	Dual<double> quo1 = x / y;
	EXPECT_NEAR(quo1.real(),-0.75,DTOL); 
	EXPECT_NEAR(quo1.dual(),(-9*4.0-3.0*8.0)/16,DTOL);

	Dual<double> quo2 = x / 3.0;
	EXPECT_NEAR(quo2.real(),1.0,DTOL); 
	EXPECT_NEAR(quo2.dual(),3.0,DTOL);

	// (5.0+0e)/(3+9.0e) = 5/3 + (-5.0*9)/(9)
	Dual<double> quo3 = 5.0 / x;
	EXPECT_NEAR(quo3.real(),5.0/3,DTOL); 
	EXPECT_NEAR(quo3.dual(),(-5.0*9.0)/9,DTOL);
}

TEST(MATH,ACOS){
	Dual<double> x(-0.5,4.0);
	Dual<double> acosx = acos(x);
	EXPECT_NEAR(acosx.real(),acos(-0.5),DTOL);
	EXPECT_NEAR(acosx.dual(),-4.0/sqrt(1 - 0.25),DTOL);
}

TEST(MATH,ASIN){
	Dual<double> x(-0.5,4.0);
	Dual<double> asinx = asin(x);
	EXPECT_NEAR(asinx.real(),asin(-0.5),DTOL);
	EXPECT_NEAR(asinx.dual(),4.0/sqrt(1 - 0.25),DTOL);
}

TEST(MATH,ATAN){
	Dual<double> x(-0.5,4.0);
	Dual<double> atanx = atan(x);
	EXPECT_NEAR(atanx.real(),atan(-0.5),DTOL);
	EXPECT_NEAR(atanx.dual(),4.0/(1 + 0.25),DTOL);
}

TEST(MATH,ATAN2){
	Dual<double> x(-10.0,4.0);
	Dual<double> y(10.0,2.0);
	Dual<double> atanx2 = atan2(x,y);
	EXPECT_NEAR(atanx2.real(),atan2(-10.0,10.0),DTOL);
	EXPECT_NEAR(atanx2.dual(),atan(x/y).dual(),DTOL);
}

TEST(MATH,COS){
	Dual<double> x(-0.5,4.0);
	Dual<double> cosx = cos(x);
	EXPECT_NEAR(cosx.real(),cos(-0.5),DTOL);
	EXPECT_NEAR(cosx.dual(),-sin(-0.5)*4.0,DTOL);
}

TEST(MATH,COSH){
	Dual<double> x(-0.5,4.0);
	Dual<double> coshx = cosh(x);
	EXPECT_NEAR(coshx.real(),cosh(-0.5),DTOL);
	EXPECT_NEAR(coshx.dual(),sinh(-0.5)*4.0,DTOL);
}

TEST(MATH,EXP){
	Dual<double> x(-0.5,4.0);
	Dual<double> expx = exp(x);
	EXPECT_NEAR(expx.real(),exp(-0.5),DTOL);
	EXPECT_NEAR(expx.dual(),4.0*exp(-0.5),DTOL);
}

TEST(MATH,LOG){
	Dual<double> x(0.5,4.0);
	Dual<double> logx = log(x);
	EXPECT_NEAR(logx.real(),log(0.5),DTOL);
	EXPECT_NEAR(logx.dual(),4.0/(0.5),DTOL);
}

TEST(MATH,LOG10){
	Dual<double> x(0.5,4.0);
	Dual<double> logx10 = log10(x);
	EXPECT_NEAR(logx10.real(),log10(0.5),DTOL);
	EXPECT_NEAR(logx10.dual(),4.0/(log(10)*(0.5)),DTOL);
}

TEST(MATH,POW){
	Dual<double> x(0.5,4.0);
	Dual<double> powx = pow(x,3.0);
	EXPECT_NEAR(powx.real(),pow(0.5,3.0),DTOL);
	EXPECT_NEAR(powx.dual(),pow(0.5,2.0)*4.0*3.0,DTOL);
}

TEST(MATH,SIN){
	Dual<double> x(0.5,4.0);
	Dual<double> sinx = sin(x);
	EXPECT_NEAR(sinx.real(),sin(0.5),DTOL);
	EXPECT_NEAR(sinx.dual(),cos(0.5)*4,DTOL);
}

TEST(MATH,SINH){
	Dual<double> x(0.5,4.0);
	Dual<double> sinhx = sinh(x);
	EXPECT_NEAR(sinhx.real(),sinh(0.5),DTOL);
	EXPECT_NEAR(sinhx.dual(),cosh(0.5)*4.0,DTOL);
}

TEST(MATH,SQRT){
	Dual<double> x(9.00,4.0);
	Dual<double> sqrtx = sqrt(x);
	EXPECT_NEAR(sqrtx.real(),3.0,DTOL);
	EXPECT_NEAR(sqrtx.dual(),pow(x,0.5).dual(),DTOL);
}

TEST(MATH,TAN){
	Dual<double> x(0.5,4.0);
	Dual<double> tanx = tan(x);
	EXPECT_NEAR(tanx.real(),tan(0.5),DTOL);
	EXPECT_NEAR(tanx.dual(),4.0/(cos(0.5)*cos(0.5)),DTOL);
}

TEST(MATH,TANH){
	Dual<double> x(0.5,4.0);
	Dual<double> tanhx = tanh(x);
	EXPECT_NEAR(tanhx.real(),tanh(0.5),DTOL);
	EXPECT_NEAR(tanhx.dual(),4.0*(1-tanh(0.5)*tanh(0.5)),DTOL);
}
