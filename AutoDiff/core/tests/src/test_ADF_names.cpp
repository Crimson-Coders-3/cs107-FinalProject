/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "ADFunc.h"
#include "test_vars.h"

void ADLibrary_nametest(){
    printf("Starting ADFunc Class Names tests, eg. 'x', 'y', 'z' for input variables...\n");
}

/////////////////////////////////////////// CONSTRUCTOR

TEST(NAME_CONSTRUCTOR,SINGLE){
    std::vector<std::string> name_x;
    name_x.push_back("x");

    ADFunc x(2.0,"x",name_x);

    /* test getters */
    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==1);
    EXPECT_EQ(x.getName().at(0),"x");
}

TEST(NAME_CONSTRUCTOR,MULTI){
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");

    ADFunc x(2.0,"x",name_x);

    /* test getters */
    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==2);
    EXPECT_EQ(x.getName().at(0),"x");
    EXPECT_EQ(x.getName().at(1),"y");
}

TEST(NAME_CONSTRUCTOR, DIMENSION_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");

    try {
        ADFunc x(2.0,seed_x,name_x);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Dimension of seed vector and name vector not matched!"));
    }
}

TEST(NAME_CONSTRUCTOR, UNIQUENESS_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("x");

    try {
        ADFunc x(2.0,seed_x,name_x);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Name must be unique!"));
    }
}

TEST(NAME_CONSTRUCTOR, ASSIGN){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");

    ADFunc f(2.0,seed_x,name_x);
    EXPECT_TRUE(f.hasName());
    ADFunc f_copy = f;
    
    EXPECT_NEAR(f_copy.dval_wrt("x"),1.0,DTOL);
    EXPECT_NEAR(f_copy.dval_wrt("y"),9.0,DTOL);

    f.clearName();
    f_copy = f;
    EXPECT_FALSE(f_copy.hasName());
}

/////////////////////////////////////////// SETTER

TEST(NAME_SETTER,SINGLE){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");

    ADFunc x(2.0,seed_x,name_x);
    x.setName(0,"y");

    /* test getters */
    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==1);
    EXPECT_EQ(x.getName().at(0),"y");
}

TEST(NAME_SETTER,MULTI){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    name_x[0] = "z";
    name_x[1] = "y";
    name_x[2] = "x";
    x.setName(name_x);

    EXPECT_TRUE(x.hasName());
    EXPECT_TRUE(x.getName().size()==3);
    EXPECT_EQ(x.getName().at(0),"z");
    EXPECT_EQ(x.getName().at(1),"y");
    EXPECT_EQ(x.getName().at(2),"x");
}

TEST(NAME_SETTER,CLEAR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    x.clearName();

    EXPECT_FALSE(x.hasName());

    // turn name mode on
    x.setName();
    EXPECT_TRUE(x.hasName());
}

TEST(NAME_SETTER,UNIQUENESS_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);

    try {
        x.setName(0,"z");
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Name must be unique!"));
    }
    x.setName(0,"x");
    x.setName(name_x);

    std::vector<double> seed_y;
    seed_y.push_back(1.0);
    seed_y.push_back(9.0);
    ADFunc y(2.0,seed_y);
    std::vector<std::string> name_y;
    name_y.push_back("y");
    name_y.push_back("y");

    try {
        y.setName(name_y);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Name must be unique!"));
    }
}

TEST(NAME_SETTER,DIMENSION_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);


    try {
        name_x.push_back("d");
        x.setName(name_x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("New name vector's dimension does not matched with the previous name vector's dimension! Please clearName() first!"));
    }
    
    std::vector<double> seed_y;
    seed_y.push_back(1.0);
    seed_y.push_back(9.0);
    ADFunc y(2.0,seed_y);

    try {
        y.setName(name_x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Name vector's dimension does not matched with seed vector's dimension!"));
    }
}

TEST(NAME_SETTER,FIRSTCLEAR_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);

    name_x.push_back("d");
    
    try {
        x.setName(name_x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("New name vector's dimension does not matched with the previous name vector's dimension! Please clearName() first!"));
    }
}

TEST(NAME_SETTER,SEED_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);

    seed_x.push_back(2.1);
    
    try {
        x.set_seed(seed_x);
        FAIL() << "Expected std::range_error";
    }
    catch(std::range_error const & err) {
        EXPECT_EQ(err.what(),std::string("Seed vector's dimension not matched with the name vector's dimension! Please use clearName() first!"));
    }
}

TEST(NAME_GETTER,DVAL){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);

    EXPECT_NEAR(x.dval_wrt("x"),1.0,DTOL);
    EXPECT_NEAR(x.dval_wrt("y"),9.0,DTOL);
    EXPECT_NEAR(x.dval_wrt("z"),13.0,DTOL);
    EXPECT_EQ(x.getName(0),"x");
}

TEST(NAME_GETTER,MODE_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);

    ADFunc x(2.0,seed_x);
    try {
        x.getName(1);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Name mode not initialized!"));
    }
    try {
        x.getName();
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Name mode not initialized!"));
    }
}

TEST(NAME_GETTER,RANGE_ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    try {
        x.getName(4);
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(),std::string("Index out of range!"));
    }
}

TEST(NAME_CHECK,BOTHNAME){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<double> seed_y;
    seed_y.push_back(1.0);
    seed_y.push_back(-9.0);
    seed_y.push_back(3.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    ADFunc y(3.8,seed_y,name_x);

    EXPECT_TRUE(checkName(x,y));
    EXPECT_TRUE(checkName(y,x));
}

TEST(NAME_CHECK,SINGLENAME){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<double> seed_y;
    seed_y.push_back(1.0);
    seed_y.push_back(-9.0);
    seed_y.push_back(3.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    ADFunc y(3.8,seed_y);

    EXPECT_FALSE(checkName(x,y));
    EXPECT_FALSE(checkName(y,x));
}

TEST(NAME_CHECK, ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<double> seed_y;
    seed_y.push_back(1.0);
    seed_y.push_back(-9.0);
    seed_y.push_back(3.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(2.0,seed_x,name_x);
    name_x[0] = "b";
    ADFunc y(3.8,seed_y,name_x);
    try {
        checkName(x,y);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("LHS and RHS objects have different names!"));
    }
}

TEST(IOSTREAM, NAMEPRINT){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");

    ADFunc x(0.5,seed_x,name_x);

    testing::internal::CaptureStdout();
    std::cout << x;
    std::string output_x = testing::internal::GetCapturedStdout();
    std::string expected_x = "Information of ADFunc object: \nValue at 0.5. \
3 variable(s) in total.\n   x's dval = 1\n   y's dval = 9\n   z's dval = 13\n";
    EXPECT_TRUE(output_x.compare(expected_x)==0);
}

TEST(TRANSFER,EQUAL){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.5,seed_x,name_x);
    ADFunc y(3.0,seed_x);

    testing::internal::CaptureStdout();
    y += x;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "RHS is in name mode, LHS is not.\nTransfering RHS's names to LHS ...\n";
    EXPECT_TRUE(output.compare(expected)==0);

    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    // other operation
    y.clearName();
    testing::internal::CaptureStdout();
    y -= x;
    output = testing::internal::GetCapturedStdout();
    expected = "RHS is in name mode, LHS is not.\nTransfering RHS's names to LHS ...\n";
    EXPECT_TRUE(output.compare(expected)==0);

    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    testing::internal::CaptureStdout();
    y /= x;
    output = testing::internal::GetCapturedStdout();
    expected = "RHS is in name mode, LHS is not.\nTransfering RHS's names to LHS ...\n";
    EXPECT_TRUE(output.compare(expected)==0);

    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    testing::internal::CaptureStdout();
    y *= x;
    output = testing::internal::GetCapturedStdout();
    expected = "RHS is in name mode, LHS is not.\nTransfering RHS's names to LHS ...\n";
    EXPECT_TRUE(output.compare(expected)==0);

    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");
}

TEST(TRANSFER,WARNING_ASSIGN){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.5,seed_x,name_x);
    ADFunc y(3.0,seed_x);

    testing::internal::CaptureStdout();
    x += y;
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "WARNING: RHS is in name mode, LHS is not.\n";
    EXPECT_TRUE(output.compare(expected)==0);

    // other operations
    testing::internal::CaptureStdout();
    x -= y;
    output = testing::internal::GetCapturedStdout();
    expected = "WARNING: RHS is in name mode, LHS is not.\n";
    EXPECT_TRUE(output.compare(expected)==0);

    testing::internal::CaptureStdout();
    x *= y;
    output = testing::internal::GetCapturedStdout();
    expected = "WARNING: RHS is in name mode, LHS is not.\n";
    EXPECT_TRUE(output.compare(expected)==0);

    testing::internal::CaptureStdout();
    x /= y;
    output = testing::internal::GetCapturedStdout();
    expected = "WARNING: RHS is in name mode, LHS is not.\n";
    EXPECT_TRUE(output.compare(expected)==0);
}

TEST(TRANSFER,WARNING_COMPARE){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.5,seed_x,name_x);
    ADFunc y(3.0,seed_x);

    testing::internal::CaptureStdout();
    bool res = (x==y);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "WARNING: One of LHS and RHS is in name mode, the other is not!\n";
    EXPECT_TRUE(output.compare(expected)==0);
    EXPECT_TRUE(res==false);

    // other operations
    testing::internal::CaptureStdout();
    res = (x!=y);
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.compare(expected)==0);
    EXPECT_TRUE(res==true);

    testing::internal::CaptureStdout();
    res = (x<=y);
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.compare(expected)==0);
    EXPECT_TRUE(res==true);

    testing::internal::CaptureStdout();
    res = (x>=y);
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.compare(expected)==0);
    EXPECT_TRUE(res==false);

    testing::internal::CaptureStdout();
    res = (x>y);
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.compare(expected)==0);
    EXPECT_TRUE(res==false);

    testing::internal::CaptureStdout();
    res = (x<y);
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.compare(expected)==0);
    EXPECT_TRUE(res==true);
}

TEST(TRANSFER,RESULT_ONEARGUMENT){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.1,seed_x,name_x);

    ADFunc y = sin(x);

    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    // other operations
    y.clearName();
    y = cos(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = tan(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = cosh(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = sinh(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = tanh(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = log2(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = log10(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = log1p(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = log(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = asin(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = acos(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = atan(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = exp2(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = atanh(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    x.setVal(2.0);
    y.clearName();
    y = acosh(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = asinh(x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");
}

TEST(TRANSFER,ERROR){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.5,seed_x,name_x);
    ADFunc y(2.0,seed_x);

    try {
        ADFunc res = x + y;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("One of LHS and RHS is in name mode, the other is not!"));
    }
    try {
        ADFunc res = x - y;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("One of LHS and RHS is in name mode, the other is not!"));
    }
    try {
        ADFunc res = x * y;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("One of LHS and RHS is in name mode, the other is not!"));
    }
    try {
        ADFunc res = x / y;
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("One of LHS and RHS is in name mode, the other is not!"));
    }
    try {
        ADFunc res = pow(x,y);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("One of LHS and RHS is in name mode, the other is not!"));
    }
}

TEST(TRANSFER,RESULT_TWOARGUMENT_ONE){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.5,seed_x,name_x);

    ADFunc y = x + 3.0;

    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = 3.0 + x;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    // other operations
    y.clearName();
    y = x - 3.0;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = 3.0 - x;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = x * 3.0;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = 3.0 * x;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = x / 3.0;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = 3.0 / x;
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = pow(3.0 , x);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");

    y.clearName();
    y = pow(x , 3.0);
    EXPECT_TRUE(y.hasName());
    EXPECT_EQ(y.getName().at(0),"x");
    EXPECT_EQ(y.getName().at(1),"y");
    EXPECT_EQ(y.getName().at(2),"z");
}

TEST(TRANSFER,RESULT_TWOARGUMENT_BOTH){
    std::vector<double> seed_x;
    seed_x.push_back(1.0);
    seed_x.push_back(9.0);
    seed_x.push_back(13.0);
    std::vector<std::string> name_x;
    name_x.push_back("x");
    name_x.push_back("y");
    name_x.push_back("z");
    
    ADFunc x(0.5,seed_x,name_x);
    ADFunc y(3.8,seed_x,name_x);

    ADFunc res = x + y;
    EXPECT_TRUE(res.hasName());
    EXPECT_EQ(res.getName().at(0),"x");
    EXPECT_EQ(res.getName().at(1),"y");
    EXPECT_EQ(res.getName().at(2),"z");

    res.clearName();
    res = y - x;
    EXPECT_TRUE(res.hasName());
    EXPECT_EQ(res.getName().at(0),"x");
    EXPECT_EQ(res.getName().at(1),"y");
    EXPECT_EQ(res.getName().at(2),"z");

    res.clearName();
    res = y / x;
    EXPECT_TRUE(res.hasName());
    EXPECT_EQ(res.getName().at(0),"x");
    EXPECT_EQ(res.getName().at(1),"y");
    EXPECT_EQ(res.getName().at(2),"z");

    res.clearName();
    res = y * x;
    EXPECT_TRUE(res.hasName());
    EXPECT_EQ(res.getName().at(0),"x");
    EXPECT_EQ(res.getName().at(1),"y");
    EXPECT_EQ(res.getName().at(2),"z");

}