/**
* \defgroup ADFunc_group ADFunc
* \brief The ADFunc module makes differentiating a function happens automatically
*/

/**
* \file ADFunc.h
* \author team 3
*
*/

#ifndef ADFUNC_H
#define ADFUNC_H

/* system header files */
#include <vector>
#include <iostream>
#include <unordered_map>

/**
* \class ADFunc
* \brief 
* ADFunc represents a function that has automatic differentiation property. 
* A ADFunc object represents a multivariable function and enables you to evaluate 
* the function value and gradient at any time. A gradient is a vector of 
* all the first-order partial derivatives of the function, which means you can also
* get partial derivative of the function with respect to a particular variable easily. 
* To get started, you need to firstly declare variables as ADFunc objects, and then
* uses these variables to compose the function (also a ADFunc object) you want to study.
*/

class ADFunc {

   private:

      // function example: f(x,y) = 2xy + y^2 = 5, x=2, y=1

      // _val: function value, 5
      double _val; 
      // _grad: function gradient, (2y,2x+2y) = (2,6)
      std::vector<double> _grad; 
      // _name_vec: a vector of variables' names, ("x", "y")
      std::vector<std::string> _name_vec; 
      // _name_map: map name (string) to index (int) in _name_vec
      //            _name_vec ("x","y") -> _name_map {"x":0, "y":1}
      std::unordered_map<std::string,int> _name_map;
      // _hasName: when it equals true, variables'names are set
      bool _hasName;
      // _num_vars: number of variables, 2
      int _num_vars;

   public:
      //! A constructor.
      /*!
         Initialize a variable with its initial value and its seed vector.
         A seed vector should have its size equal to the TOTAL number of variables
         that will be used in your program. A common way of creating a seed vector
         for a first-time created variable is to initialize a vecotr at size of total 
         number of variables and fill it with 0.00. except where this 
         variable should be with respect to the seed vector. Usually, we use a unit vector for a seed
         vector of a first-time used variable

         x = {1.0,0.0,0.0}
         y = {0.0,1.0,0.0},
         z = {0.0, 0.0, 1.0} 

         if the multivariable function f(x,y,z) is consists of x, y, z. 
         However, a seed vector does not have to be a unit vector. You can set it whatever
         you want. The reason why it is also 1.0 is that d/dx (x) = 1.0. 
         \param seed
         \param val
      */
      ADFunc(double val, std::vector<double> seed);
      
      // in var_names, every name must be unique
      ADFunc(double val, std::string name, std::vector<std::string> var_names);
      //! A constructor.
      /*!
         Initialize a variable with its initial value, its seed vector, and a vector of all
         the variables names to be used. Example of var_names
         A seed vector should have its size equal to the TOTAL number of variables
         that will be used in your program. A common way of creating a seed vector
         for a first-time created variable is to initialize a vecotr at size of total 
         number of variables and fill it with 0.00. except where this 
         variable should be with respect to the seed vector. Usually, we use a unit vector for a seed
         vector of a first-time used variable, like seed vector of x = {1.0,0.0,0.0}, y = {0.0,1.0,0.0},
         z = {0.0, 0.0, 1.0} if the multivariable function f(x,y,z) is consists of x, y, z. 
         However, a seed vector does not have to be a unit vector. You can set it whatever
         you want. The reason why it is also 1.0 is that d/dx (x) = 1.0. 
         \param val
         \param seed
         \param var
      */
      ADFunc(double val, std::vector<double> seed, std::vector<std::string> var_names);

   /////////////////////////////////////////// ASSIGNMENT & COMPOUND ASSIGNMENT OPERATORS
   ADFunc operator = ( const ADFunc &obj );

   // overload ADFunc + ADFunc
   ADFunc operator += ( const ADFunc &obj );

   // overload ADFunc + double
   ADFunc operator += ( double obj );

   // overload ADFunc - ADFunc
   ADFunc operator -= ( const ADFunc &obj );

   // overload ADFunc - double
   ADFunc operator -= ( double obj );

   // overload ADFunc * ADFunc
   ADFunc operator *= ( const ADFunc &obj );

   // overload ADFunc * double
   ADFunc operator *= ( double obj );

   // overload ADFunc / ADFunc
   ADFunc operator /= ( const ADFunc &obj );

   // overload ADFunc / double
   ADFunc operator /= ( double obj );

   /////////////////////////////////////////// GETTER
   // get value
   double val() const;

   // get dval with respect to a variable
   double dval_wrt(int index) const;

   // get dval with respect to a variable
   double dval_wrt(std::string var_name) const;

   // get dvals with respect to more than one variables
   std::vector<double> dval_wrt(std::vector<int> indexs) const;

   // get dvals with respect to more than one variables
   std::vector<double> dval_wrt(std::vector<std::string> names) const;

   // get gradient (all the variables)
   std::vector<double> gradient() const;

   // get total number of variables
   int countVar() const;

   // get if variables have names, 
   // e.g. represented by std::vector<std::string> {"x", "y","z"}
   bool hasName() const;

   // get names of all variables
   std::vector<std::string> getName() const;

   // get names of a variable at index of name vector
   std::string getName(int index) const;

   /////////////////////////////////////////// SETTER
   // set value
   void setVal(double val);

   // set dval with respect to a variable
   void set_seed_wrt(int index, double dval);

   // set dvals of all the variables
   void set_seed(std::vector<double> dvals);

   // set name of a variable
   void setName(int index, std::string var_name);

   // set name of all the variables
   void setName(std::vector<std::string> names);

   // turn name mode on
   void setName();

   // turn name mode off
   void clearName();

}; // close ADFunc class

/////////////////////////////////////////// PRINT
std::ostream& operator<<(std::ostream& os, const ADFunc& obj);

/////////////////////////////////////////// ARITHMETIC OPERATORS
ADFunc operator + ( const ADFunc &lhs, const ADFunc &rhs );  // to do
ADFunc operator + ( const ADFunc &lhs, double rhs );
ADFunc operator + ( double lhs, const ADFunc &rhs);
ADFunc operator - ( const ADFunc &obj);
ADFunc operator - ( const ADFunc &lhs, const ADFunc &rhs );
ADFunc operator - ( const ADFunc &lhs, double rhs );
ADFunc operator - ( double lhs, const ADFunc &rhs);
ADFunc operator * ( const ADFunc &lhs, const ADFunc &rhs );
ADFunc operator * ( const ADFunc &lhs, double rhs );
ADFunc operator * ( double lhs, const ADFunc &rhs);
ADFunc operator / ( const ADFunc &lhs, const ADFunc &rhs );
ADFunc operator / ( const ADFunc &lhs, double rhs );
ADFunc operator / ( double lhs, const ADFunc &rhs);

/////////////////////////////////////////// RELATIONAL OPERATORS
bool operator==(const ADFunc& lhs, double rhs);
bool operator==(double lhs, const ADFunc& rhs);
bool operator==(const ADFunc& lhs, const ADFunc& rhs);

bool operator!=(const ADFunc& lhs, double rhs);
bool operator!=(double lhs, const ADFunc& rhs);
bool operator!=(const ADFunc& lhs, const ADFunc& rhs);

bool operator<(const ADFunc& lhs, double rhs);
bool operator<(double lhs, const ADFunc& rhs);
bool operator<(const ADFunc& lhs, const ADFunc& rhs);

bool operator<=(const ADFunc& lhs, double rhs);
bool operator<=(double lhs, const ADFunc& rhs);
bool operator<=(const ADFunc& lhs, const ADFunc& rhs);

bool operator>(const ADFunc& lhs, double rhs);
bool operator>(double lhs, const ADFunc& rhs);
bool operator>(const ADFunc& lhs, const ADFunc& rhs);

bool operator>=(const ADFunc& lhs, double rhs);
bool operator>=(double lhs, const ADFunc& rhs);
bool operator>=(const ADFunc& lhs, const ADFunc& rhs);

/////////////////////////////////////////// MATH LIB FUNCTIONS
ADFunc pow ( const ADFunc &lhs, const ADFunc &rhs );
ADFunc pow ( const ADFunc &lhs, double rhs );
ADFunc pow ( double lhs, const ADFunc &rhs);
ADFunc sqrt ( const ADFunc &obj);
ADFunc cbrt ( const ADFunc &obj);
ADFunc hypot ( const ADFunc &obj);
ADFunc log(const ADFunc &obj);
ADFunc log10(const ADFunc &obj);
ADFunc log2(const ADFunc &obj);  
ADFunc log1p(const ADFunc &obj); 
ADFunc exp ( const ADFunc &obj );
ADFunc exp2 ( const ADFunc &obj );
ADFunc expm1 ( const ADFunc &obj );
ADFunc sin(const ADFunc &obj);
ADFunc cos(const ADFunc &obj);
ADFunc tan(const ADFunc &obj);
ADFunc asin(const ADFunc &obj);
ADFunc acos(const ADFunc &obj);
ADFunc atan(const ADFunc &obj);
ADFunc sinh(const ADFunc &obj);
ADFunc cosh(const ADFunc &obj);
ADFunc tanh(const ADFunc &obj);
ADFunc asinh(const ADFunc &obj);
ADFunc acosh(const ADFunc &obj);
ADFunc atanh(const ADFunc &obj);


/////////////////////////////////////////// NAME MODE
bool checkName(const ADFunc &lhs, const ADFunc & rhs);

////////////////////////////////////////// VECTOR INPUT

// Create multiple functions/variables and intilaize seed vectors as unit vectors
// automatically for you
std::vector<ADFunc> multiVar(std::vector<double> values);

// set all the seeds of vectorized input back to unit vectors
void setSeedDefault(std::vector<ADFunc> vars);

///////////////////////////////////////////////////////////////////
/////   Operators NOT Supported in ADFunc Class      ////////////
/////                                                  ////////////
///// Arithmetic: %                                    ////////////
///// Increment & Decrement: ++, --                    ////////////
///// Compound Assignment: %=, >>=, <<=, &=, ^=, |=    ////////////
///// Logical: !, &&, ||                               ////////////
///// Conditional ternary: ?                           ////////////
/////                                                  ////////////
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
/////      Math Library Function NOT Supported         ////////////
/////                                                  ////////////
///// Exponential & Logarithmic: frexp, ldexp, modf,   //////////// 
/////                            ilogb, logb, scalbn,  //////////// 
/////                            scalbln               ////////////
///// Trigonometric: atan2                             ////////////
///// Error & Gamma functions: erf, erfc, tgamma,      ////////////
/////                          lgamma                  ////////////
///// Rounding & Remainder: ceil, floor, fmod, trunc,  ////////////
/////                      round, lround,llround,rint, ////////////
/////                      lrint, nearbyint, remainder ////////////
/////                      llrint, remquo              ////////////
///// Floating-point manipulation: copysign, nan,      ////////////
/////                           nextafter, nexttoward  ////////////
///// Min, Max, Difference: fdim, fmax, fmin           ////////////
///// Others: fabs, abs, fma                           ////////////
/////                                                  ////////////
///////////////////////////////////////////////////////////////////

#endif