/* system header files */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>

/* googletest header files */
#include "gtest/gtest.h"

/* header files */
#include "Roots.h"
#include "Roots.cpp"
#include "test_vars.h"

void RootsLibrary_testcheck(){
    printf("Starting Roots Class tests...\n");
}

using namespace std;

vector<ADFunc> customFunct(Eigen::VectorXd vals){
    ADFunc x = ADFunc(vals[0], {1,0});
    ADFunc y = ADFunc(vals[1], {0,1});
    return {5*pow(x,2)+2*y, 3+y};
}

//////////////CONSTRUCTOR TESTS
TEST(CONSTRUCTOR,EQOPERATOR){    
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct;
    Equation eq = Equation(customFunct, 2);
    EXPECT_EQ(eq.num_vars, 2);
}

TEST(CONSTRUCTOR,DEFAULT){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct;
    Equation eq(customFunct, 2);
    EXPECT_EQ(eq.num_vars, 2);
}

//Test getting the values from the vector of ADFunc objects returned by function(values)
TEST(EVAL_F, FROM_EQUATION){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct;
    Equation eq(customFunct, 2);
    Eigen::VectorXd values(2);
    values << 2, 3;
    std::vector<ADFunc> F = eq.function(values);
    EXPECT_EQ(F[0].val(), 26);
    EXPECT_EQ(F[1].val(), 6);
}

//Test getting the values from the Eigen::VectorXd object from conversion via getF 
TEST(EVAL_F_EIGEN, FROM_EQUATION){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct;
    Equation eq(customFunct, 2);
    Eigen::VectorXd values(2);
    values << 2, 3;
    Eigen::VectorXd Fv = getF(eq.function(values));
    EXPECT_EQ(Fv(0), 26);
    EXPECT_EQ(Fv(1), 6);
}

//Test getting the Jacobian from an evaluated F object (i.e. after plugging in funct values)
TEST(GET_JACOBIAN, FROM_EQUATION){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct;
    Equation eq(customFunct, 2);
    Eigen::VectorXd values(2);
    values << 2, 3;
    std::vector<ADFunc> F = eq.function(values);
    Eigen::MatrixXd J = getJ(F, 2);
    EXPECT_EQ(J(0,0), 20); //df1/dx
    EXPECT_EQ(J(0,1), 2); //df1/dy
    EXPECT_EQ(J(1,0), 0); //df2/dx
    EXPECT_EQ(J(1,1), 1); //df2/dy
}

//Test getting the Jacobian "externally" (not using the Equation class)
TEST(GET_JACOBIAN, FROM_AUTOFUNC){
    ADFunc x = ADFunc(2, {1,0});
    ADFunc y = ADFunc(3, {0,1});
    std::vector<ADFunc> F = {5*pow(x,2)+2*y, 3+y};
    Eigen::MatrixXd J = getJ(F, 2);
    EXPECT_EQ(J(0,0), 20); //df1/dx
    EXPECT_EQ(J(0,1), 2); //df1/dy
    EXPECT_EQ(J(1,0), 0); //df2/dx
    EXPECT_EQ(J(1,1), 1); //df2/dy
}

TEST(ROOT_FIND, FROM_EQUATION){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct;
    Equation eq(customFunct, 2);
    Eigen::VectorXd guess(2);
    guess << 1, 1;
    double tol = 1e-4;
    Eigen::VectorXd roots = eq.getRoots(guess, tol);
    std::vector<ADFunc> F = eq.function(roots); //check that F(roots) near 0
    Eigen::VectorXd F_at_roots = getF(F);
    double l2_norm = F_at_roots.squaredNorm();
    EXPECT_NEAR(0.0, l2_norm, tol);
    std::cout << l2_norm << std::endl;
}
