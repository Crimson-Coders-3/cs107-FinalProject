#ifndef ROOTS_H
#define ROOTS_H
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "ADFunc.h"
#include "ADFuncVector.h"

class Equation {
    public:
        std::function<std::vector<ADFunc> (Eigen::VectorXd)> function;
        int num_vars;
        Equation(std::function<std::vector<ADFunc> (Eigen::VectorXd)> function, int num_vars);

    //ASSIGNMENT OPERATORS
    Equation operator = (const Equation &obj);
    
    //get vector with roots of function, given a vector and tolerance (epsilon)
    Eigen::VectorXd getRoots(Eigen::VectorXd guess, double tol = 1e-4);
};

//convert from vector of ADFunc (evaluated at a) to a vector of type VectorXd of values
Eigen::VectorXd getF(std::vector<ADFunc> funct);

//convert from vector of ADFunc (evaluated at a) to a matrix of type MatrixXd of derivatives eval at a
Eigen::MatrixXd getJ(std::vector<ADFunc> funct, int num_vars);

//PRINT
std::ostream& operator<<(std::ostream& os, const Equation& obj);

#endif
