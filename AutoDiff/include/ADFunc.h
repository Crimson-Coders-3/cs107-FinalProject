#ifndef ADFUNC_H
#define ADFUNC_H

#include <vector>
#include <iostream>
#include <unordered_map>

///////////////////////////////////////////////////////////////// CUSTOM ADFunc CLASS
class ADFunc {

   /////////////////////////////////////////// CLASS DEF
   // private
   private:
      // function example: f(x,y) = 2xy + y^2 = 5, x=2, y=1
      // _val: function value, 5
      double _val;
      // _grad: function gradient, (2y,2x+2y) = (2,6)
      std::vector<double> _grad;
      // _name_vec: variables names, ("x", "y")
      std::vector<std::string> _name_vec;
      // _name: map name (string) to index (int) int _name_vec
      //        e.g ("x","y") -> {"x":0, "y":1}
      std::unordered_map<std::string,int> _name_map;
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
      ADFunc(double val, std::vector<double> seed);
      // constructor
      // seed vector example: for x in f(x,y), seed = [1, 0], var_names = ["x","y"]
      //                      for y in f(x,y), seed = [0, 1], var_names = ["x","y"]
      // in var_names, every name must be unique
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
   double dval_wrt(std::string name) const;

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
   void set_dval_wrt(int index, double dval);

   // set dvals of all the variables
   void set_dval(std::vector<double> dvals);

   // set name of a variable
   void setName(int index, std::string name);

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
bool operator==(const ADFunc& a, double b);
bool operator==(double a, const ADFunc& b);
bool operator==(const ADFunc& a, const ADFunc& b);

bool operator!=(const ADFunc& a, double b);
bool operator!=(double a, const ADFunc& b);
bool operator!=(const ADFunc& a, const ADFunc& b);

bool operator<(const ADFunc& a, double b);
bool operator<(double a, const ADFunc& b);
bool operator<(const ADFunc& a, const ADFunc& b);

bool operator<=(const ADFunc& a, double b);
bool operator<=(double a, const ADFunc& b);
bool operator<=(const ADFunc& a, const ADFunc& b);

bool operator>(const ADFunc& a, double b);
bool operator>(double a, const ADFunc& b);
bool operator>(const ADFunc& a, const ADFunc& b);

bool operator>=(const ADFunc& a, double b);
bool operator>=(double a, const ADFunc& b);
bool operator>=(const ADFunc& a, const ADFunc& b);

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