#ifndef ROOTS_H
#define ROOTS_H
#include <iostream>
#include <vector>
#include <functional>
#include <Eigen/Dense>
#include <Eigen/QR>
#include "ADFunc.h"
#include "ADFuncVector.h"

class Roots {
    public:
        function<std::vector<ADFunc (VectorXd)> _function;
        int _num_vars;

    //ASSIGNMENT OPERATORS
    Roots operator = (const Roots &obj);
    
    //get vector with roots of function, given a vector and tolerance (epsilon)
    Eigen::VectorXd getRoots(Eigen::VectorXd guess, double tol = 1e-4);
}

//convert from vector of ADFunc (evaluated at a) to a vector of type VectorXd of values
Eigen::VectorXd getF(std::vector<ADFunc> function);

//convert from vector of ADFunc (evaluated at a) to a matrix of type MatrixXd of derivatives eval at a
Eigen::MatrixXd getJ(std::vector<ADFunc> function, int num_vars);

//PRINT
std::ostream& operator<<(std::ostream& os, const Roots& obj);

#endif
