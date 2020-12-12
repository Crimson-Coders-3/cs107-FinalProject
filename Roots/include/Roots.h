/**
* \defgroup Roots_group Roots
* Enables root-finding for multivariate and vector-valued functions
*/

/**
* \file  Roots.h
* \author team 3
*
*/

#ifndef ROOTS_H
#define ROOTS_H

/* system header files */
#include <iostream>
#include <vector>
#include <string>
#include <functional>

/* 3PL dependencies */
#include <Eigen/Dense>
#include <Eigen/QR>

/* ADFunc header files */
#include "ADFunc.h"
#include "ADFuncVector.h"

/**
* \class Equation
* \brief
* Equation represents a function that accepts as input a vector of type VectorXd (from the Eigen library) and returns a standard vector of ADFunc objects evaluated at the inputted vector. The purpose of the Equation class is to 'remember' the function F of interest (by storing it in an Equation object) to facilitate repeatedly finding F(x) and its Jacobian evaluted at x, J(x). The Equation class also enables root finding by utilizing the ADFunc library to compute J(x) and derivatives.
*/

class Equation {
    public:
        //! A constructor.
        /*!
            Initialize an Equation using two arguments: a std::function (which accepts an Eigen::VectorXd vector of values and returns a standard vector of ADFunc objects) and the number of variables in the function. The typical workflow is to first define a custom function as follows:

            vector<ADFunc> customFunct(Eigen::VectorXd vals){
                ADFunc x = ADFunc(vals[0], {1,0});
                ADFunc y = ADFunc(vals[1], {0,1});
                return {5*sin(x)-cos(y)/2, 3*x/y, z+2};
            }

            This function can then be used to initialize an Equation object:

            Equation eq = Equation(customFunct, 2);
        */
        Equation(std::function<std::vector<ADFunc> (Eigen::VectorXd)> function, int num_vars);
        
        //! A user-defined function
        /*! Accepts a vector "a" of inputs (e.g. x,y,z) and returns F(a), a vector of ADFunc objects
        */
        std::function<std::vector<ADFunc> (Eigen::VectorXd)> function;
        //! Number of variables in the user-defined function
        /*! Used for determining dimensions of the Jacobian to be returned
        */    
        int num_vars;

    //ASSIGNMENT OPERATORS

    //! Assignment operator
    /*!
        Assign an Equation object to another Equation object by copying by value
    */
    Equation operator = (const Equation &obj);
    
    //! Get the roots of the function
    /*! Returns a vector with roots of function, given an initial guess and tolerance
    */
    Eigen::VectorXd getRoots(Eigen::VectorXd guess, double tol = 1e-4);
};

/*! \fn Eigen::VectorXd getF(std::vector<ADFunc> funct)
    \brief Converts from std::vector<ADFunc> to Eigen::VectorXd type

    Converts the inputted vector of ADFunc objects (representing the function F evaluated at x=a) to a vector of type Eigen::VectorXd of values for use in linear algebra operations using the Eigen library
*/
Eigen::VectorXd getF(std::vector<ADFunc> funct);

/*! \fn Eigen::MatrixXd getJ(std::vector<ADFunc> funct, int num_vars)
    \brief Returns the Jacobian matrix of funct (evaluated at x=a, the initial values used when creating funct)

    Note that the inputted function of type std::vector<ADFunc> has already been evaluated at a certain x=a since ADFunc objects are initialized with values, and store a value and a derivative computed via AD forward mode. Therefore this is primarily a utility function to get the derivatives of the inputted function as an Eigen::MatrixXd type to enable linear algebra computations
*/
Eigen::MatrixXd getJ(std::vector<ADFunc> funct, int num_vars);

/*! \fn std::ostream& operator<<(std::ostream& os, const Equation& obj)
    \brief Prints the number of variables in the Equation object
*/
std::ostream& operator<<(std::ostream& os, const Equation& obj);

#endif
