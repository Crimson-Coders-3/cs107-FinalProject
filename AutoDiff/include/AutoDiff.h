#ifndef AD_H
#define AD_H

#include <vector>
#include <iostream>

///////////////////////////////////////////////////////////////// CUSTOM AUTODIFF CLASS
class AutoDiff {

   /////////////////////////////////////////// CLASS DEF
   // private
   private:
      // function example: f(x,y) = 2xy + y^2 = 5, x=2, y=1
      // _val: function value, 5
      double _val;
      // _grad: function gradient, (2y,2x+2y) = (2,6)
      std::vector<double> _grad;
      // _name: variable names, ("x","y")
      std::vector<std::string> _names;
      // _hasName equals true is variables'names are set
      bool _hasName;
      // _num_vars: number of variables, 2
      int _num_vars;


   // public
   public:
      // constructor
      // seed vector example: for x in f(x,y), seed = [1, 0]
      //                      for y in f(x,y), seed = [0, 1]
      // seed vector does not need to be unit vector
      AutoDiff(double val, std::vector<double> seed);
      // constructor
      // seed vector example: for x in f(x,y), seed = [1, 0], var_names = ["x","y"]
      //                      for y in f(x,y), seed = [0, 1], var_names = ["x","y"]
      // in var_names, every name must be unique
      AutoDiff(double val, std::vector<double> seed, std::vector<std::string> var_names);

   /////////////////////////////////////////// ASSIGNMENT & COMPOUND ASSIGNMENT OPERATORS
   AutoDiff operator = ( const AutoDiff &obj );

   // overload autodiff + autodiff
   AutoDiff operator += ( const AutoDiff &obj );

   // overload autodiff + double
   AutoDiff operator += ( double obj );

   // overload autodiff - autodiff
   AutoDiff operator -= ( const AutoDiff &obj );

   // overload autodiff - double
   AutoDiff operator -= ( double obj );

   // overload autodiff * autodiff
   AutoDiff operator *= ( const AutoDiff &obj );

   // overload autodiff * double
   AutoDiff operator *= ( double obj );

   // overload autodiff / autodiff
   AutoDiff operator /= ( const AutoDiff &obj );

   // overload autodiff / double
   AutoDiff operator /= ( double obj );

   /////////////////////////////////////////// GETTER
   // get value
   double val() const;

   // get dval with respect to a variable
   double dval_wrt(int index) const;

   // get gradient (all the variables)
   std::vector<double> gradient() const;

   // get total number of variables
   int countVar() const;

   // get if variables have names, 
   // e.g. represented by std::vector<std::string> {"x", "y","z"}
   bool hasName() const;

   /////////////////////////////////////////// SETTER
   // set value
   void setVal(double val);

   // set dval with respect to a variable
   void set_dval_wrt(int index, double dval);

   // set dvals of all the variables
   void set_dval(std::vector<double> dvals);

   // set name of a variable
   void set_name(int index, std::string name);

   // set name of all the variables
   void set_name(std::vector<std::string> names);

}; // close AutoDiff class

/////////////////////////////////////////// PRINT
std::ostream& operator<<(std::ostream& os, const AutoDiff& obj);

/////////////////////////////////////////// ARITHMETIC OPERATORS
AutoDiff operator + ( const AutoDiff &lhs, const AutoDiff &rhs );  // to do
AutoDiff operator + ( const AutoDiff &lhs, double rhs );
AutoDiff operator + ( double lhs, const AutoDiff &rhs);
AutoDiff operator - ( const AutoDiff &obj);
AutoDiff operator - ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator - ( const AutoDiff &lhs, double rhs );
AutoDiff operator - ( double lhs, const AutoDiff &rhs);
AutoDiff operator * ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator * ( const AutoDiff &lhs, double rhs );
AutoDiff operator * ( double lhs, const AutoDiff &rhs);
AutoDiff operator / ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator / ( const AutoDiff &lhs, double rhs );
AutoDiff operator / ( double lhs, const AutoDiff &rhs);


/////////////////////////////////////////// RELATIONAL OPERATORS
bool operator==(const AutoDiff& a, double b);
bool operator==(double a, const AutoDiff& b);
bool operator==(const AutoDiff& a, const AutoDiff& b);

bool operator!=(const AutoDiff& a, double b);
bool operator!=(double a, const AutoDiff& b);
bool operator!=(const AutoDiff& a, const AutoDiff& b);

bool operator<(const AutoDiff& a, double b);
bool operator<(double a, const AutoDiff& b);
bool operator<(const AutoDiff& a, const AutoDiff& b);

bool operator<=(const AutoDiff& a, double b);
bool operator<=(double a, const AutoDiff& b);
bool operator<=(const AutoDiff& a, const AutoDiff& b);

bool operator>(const AutoDiff& a, double b);
bool operator>(double a, const AutoDiff& b);
bool operator>(const AutoDiff& a, const AutoDiff& b);

bool operator>=(const AutoDiff& a, double b);
bool operator>=(double a, const AutoDiff& b);
bool operator>=(const AutoDiff& a, const AutoDiff& b);

/////////////////////////////////////////// MATH LIB FUNCTIONS
AutoDiff pow ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff pow ( const AutoDiff &lhs, double rhs );
AutoDiff pow ( double lhs, const AutoDiff &rhs);
AutoDiff pow ( const AutoDiff &obj); // to do
AutoDiff cbrt ( const AutoDiff &obj); // to do
AutoDiff hypot ( const AutoDiff &obj); // to do
AutoDiff log(const AutoDiff &obj);
AutoDiff log10(const AutoDiff &obj);
AutoDiff log2(const AutoDiff &obj);  // to do
AutoDiff log1p(const AutoDiff &obj); // to do
AutoDiff exp ( const AutoDiff &obj );
AutoDiff exp2 ( const AutoDiff &obj ); // to do
AutoDiff expm1 ( const AutoDiff &obj ); // to do
AutoDiff sin(const AutoDiff &obj);
AutoDiff cos(const AutoDiff &obj);
AutoDiff tan(const AutoDiff &obj);
AutoDiff asin(const AutoDiff &obj);
AutoDiff acos(const AutoDiff &obj);
AutoDiff atan(const AutoDiff &obj);
AutoDiff atan2(const AutoDiff &lhs, const AutoDiff &rhs);
AutoDiff atan2(double lhs, const AutoDiff &rhs);
AutoDiff atan2(const AutoDiff &lhs, double rhs);
AutoDiff sinh(const AutoDiff &obj);
AutoDiff cosh(const AutoDiff &obj);
AutoDiff tanh(const AutoDiff &obj);
AutoDiff asinh(const AutoDiff &obj);
AutoDiff acosh(const AutoDiff &obj);
AutoDiff atanh(const AutoDiff &obj);


///////////////////////////////////////////////////////////////////
/////   Operators NOT Supported in AutoDiff Class      ////////////
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