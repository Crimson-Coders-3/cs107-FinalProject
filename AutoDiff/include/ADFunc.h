/** \defgroup AutoDiff_group AutoDiff
* \brief The AutoDiff module contains ADFunc class and ADFuncVector class with its 
* aim to make differentiating a function happens automatically
*/

/**
* \ingroup AutoDiff_group AutoDiff
* \file ADFunc.h
* \author team 3
*
*/

#ifndef ADFUNC_H
#define ADFUNC_H

#include <vector>
#include <iostream>
#include <unordered_map>

/**
* \ingroup AutoDiff_group AutoDiff
* \class ADFunc
* \brief 
* ADFunc represents a function that has automatic differentiation property. 
* A ADFunc object represents a multivariable function and enables you to evaluate 
* the function value and gradient at any time. A gradient is a vector of 
* all the first-order partial derivatives of the function, which means you can also
* get partial derivative of the function with respect to(wrt) a particular variable easily. 
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
         Initializes a ADFunc object with its initial value and its seed vector.
         A seed vector should have its size equal to the TOTAL number of variables
         that will be used in your program. A common way of creating a seed vector
         for a first-time created variable is to initialize a vecotr at size of total 
         number of variables and fill it with 0.00 except where this 
         variable locates with respect to(wrt) the seed vector. Usually, we use a unit vector for a seed
         vector of a first-time used variable. For example, for a multivariable function f(x,y,z):

         std::vector<double> seed_x = {0.0, 0.1, 0.0};
         
         std::vector<double> seed_y = {0.0, 1.0, 0.0};
         
         std::vector<double> seed_z = {0.0, 0.0, 1.0};

         However, a seed vector does not have to be a unit vector. You can set it whatever
         you want. The reason why it is also 1.0 is that d/dx (x) = 1.0. 
         \param seed a seed vector, like {0.0, 0.1, 0.0}
         \param val initial value
      */
      ADFunc(double val, std::vector<double> seed);
      
      //! A constructor.
      /*!
         Initializes a ADFunc object with its initial value, its seed vector, and a vector of all
         the variables names to be used. Each variables should all have a name and its name
         must be unique.

         For example, for a multivariable function f(x,y,z):

         std::vector<std::string> var_names = {"x", "y", "z"};

         and this var_names vector should be used in all the constructors of x,y,z variables to
         be consistent.
         
         ADFunc x(5.0,seed_x, var_names);

         ADFunc y(2.0,seed_y, var_names);

         ADFunc z(0.9,seed_z, var_names);

         A seed vector should have its size equal to the TOTAL number of variables
         that will be used in your program. A common way of creating a seed vector
         for a first-time created variable is to initialize a vecotr at size of total 
         number of variables and fill it with 0.00. except where this 
         variable should be with respect to(wrt) the seed vector. Usually, we use a unit vector for a seed
         vector of a first-time used variable. The reason why it is also 1.0 is that d/dx (x) = 1.0. 
         
         \param val initial value
         \param seed a seed vector, like {0.0, 0.1, 0.0}
         \param var_names a vector that contains all the variables' names, like {"x", "y", "z"}
      */
      ADFunc(double val, std::vector<double> seed, std::vector<std::string> var_names);

      //! A constructor.
      /*!
         Initializes a ADFunc object with its initial value, its own variable name, and a vector of all
         the variables names to be used. Each variables should all have a name and its name
         must be unique.

         For example, for a multivariable function f(x,y,z):

         std::vector<std::string> var_names = {"x", "y", "z"};

         and for variable x,
         
         ADFunc x(5.0,"x", var_names);

         When using this constructor, the variable's seed vector is set default to be a unit vector 
         (the derivative with respect to(wrt) itself is 1.0). You can change the seed vector afterwards 
         
         \sa set_seed(), set_seed_wrt()

         \param val initial value
         \param name variable name, like "x"
         \param var_names a vector that contains all the variables' names, like {"x", "y", "z"}
      */
      ADFunc(double val, std::string name, std::vector<std::string> var_names);

   //! Assignment operator.
   /*!
      Assign an ADFunc object to another ADFunc object by using copy by value

      \param obj
   */
   ADFunc operator = ( const ADFunc &obj );

   //! Overload ADFunc += ADFunc
   /*!
      It will throw std::invalid_argument error if LHS(left hand side) and RHS(right hand side)
      have different size of seed vectors.

      It will throw a warning if LHS ADFunc object is in name mode while RHS is not. 

      It will throw std::runtime_error if LHS and RHS have different names vectors.

      It will automatically assign RHS ADFunc object's name to LHS ADFunc object if RHS does not have names.
   
      \param obj ADFunc object at RHS
   */ 
   ADFunc operator += ( const ADFunc &obj );

   //! Overload ADFunc += a scalar number
   /*!
      It will change LHS ADFunc object's value but not its gradient.

      \param obj a scalar number
   */ 
   ADFunc operator += ( double obj );

   //! Overload ADFunc -= ADFunc
   /*!
      It will throw std::invalid_argument error if LHS(left hand side) and RHS(right hand side)
      have different size of seed vectors.

      It will throw a warning if LHS ADFunc object is in name mode while RHS is not. 

      It will throw std::runtime_error if LHS and RHS have different names vectors.

      It will automatically assign RHS ADFunc object's name to LHS ADFunc object if RHS does not have names.
   
      \param obj ADFunc object at RHS
   */ 
   ADFunc operator -= ( const ADFunc &obj );

   //! Overload ADFunc -= a scalar number
   /*!
      It will change LHS ADFunc object's value but not its gradient.

      \param obj a scalar number
   */ 
   ADFunc operator -= ( double obj );

   //! Overload ADFunc -= ADFunc
   /*!
      It will throw std::invalid_argument error if LHS(left hand side) and RHS(right hand side)
      have different size of seed vectors.

      It will throw a warning if LHS ADFunc object is in name mode while RHS is not. 

      It will throw std::runtime_error if LHS and RHS have different names vectors.

      It will automatically assign RHS ADFunc object's name to LHS ADFunc object if RHS does not have names.
   
      \param obj ADFunc object at RHS
   */ 
   ADFunc operator *= ( const ADFunc &obj );

   //! Overload ADFunc *= a scalar number
   /*!
      It will change LHS ADFunc object's value but not its gradient.

      \param obj a scalar number
   */ 
   ADFunc operator *= ( double obj );

   //! Overload ADFunc /= ADFunc
   /*!
      It will throw std::invalid_argument error if LHS(left hand side) and RHS(right hand side)
      have different size of seed vectors.

      It will throw a warning if LHS ADFunc object is in name mode while RHS is not. 

      It will throw std::runtime_error if LHS and RHS have different names vectors.

      It will automatically assign RHS ADFunc object's name to LHS ADFunc object if RHS does not have names.
   
      \param obj ADFunc object at RHS
   */ 
   ADFunc operator /= ( const ADFunc &obj );

   //! Overload ADFunc /= a scalar number
   /*!
      It will change LHS ADFunc object's value but not its gradient.

      \param obj a scalar number
   */ 
   ADFunc operator /= ( double obj );

   /////////////////////////////////////////// GETTER
   //! Get function value
   double val() const;

   //! Get dval (partial derivative) with respect to(wrt) a variable
   /*!
      It will throw a std::out_of_range error if index is out of range of the predefined seed vector.

      \param index index of the variable in the seed vector
   */ 
   double dval_wrt(int index) const;

   //! Get dval (partial derivative) with respect to(wrt) a variable
   /*!
      It will throw std::runtime_error if the input variable name not found.

      It will throw std::runtime_error if name mode is not set.

      \param name variable name, like "x"
   */
   double dval_wrt(std::string var_name) const;

   //! Get dvals with respect to(wrt) more than one variables
   /*!
      It will throw a std::out_of_range error if one index is out of range of the predefined seed vector.

      \param indexs indexs of variables in the seed vector
   */
   std::vector<double> dval_wrt(std::vector<int> indexs) const;

   //! Get dvals with respect to(wrt) more than one variables
   /*!
      It will throw std::runtime_error if one input variable name not found.

      It will throw std::runtime_error if name mode is not set.

      \param names names of variables
   */
   std::vector<double> dval_wrt(std::vector<std::string> names) const;

   //! Get gradient (dvals of all the variables)
   std::vector<double> gradient() const;

   //! Get total number of variables
   int countVar() const;

   //! Get true/false if variables have names
   bool hasName() const;

   //! Get names of all variables
   /*!

      It will throw std::runtime_error if name mode is not set.

      \param names names of variables
   */
   std::vector<std::string> getName() const;

   //! Get a variable name at index of name vector
   /*!
      It will throw std::runtime_error if one input variable name not found.

      It will throw a std::out_of_range error if index is out of range of the predefined seed vector.

      \param index index of the variable in the seed vector
   */
   std::string getName(int index) const;

   /////////////////////////////////////////// SETTER
   //! Set function value
   void setVal(double val);

   //! Set dval with respect to(wrt) a variable
   /*!
      It will throw a std::out_of_range error if index is out of range of the predefined seed vector.

      \param index index of the variable in the seed vector
      \param dval dval (partial derivative) to be set
   */
   void set_seed_wrt(int index, double dval);

   //! Set seed vector (dvals of all the variables)
   /*!
      It will throw std::range_error if the new seed vector's dimension not matched 
      with the name vector's dimension
      if the ADFunc object is currently in name mode. 
      If that is the case, please use \sa clearName() first!

      \param dvals gradient (vector of dvals) to be set
   */
   void set_seed(std::vector<double> dvals);

   //! Set name of a variable
   /*!
      It will throw a std::out_of_range error if index is out of range of the predefined seed vector.

      It will throw std::runtime_error if name mode is not set.

      It will throw std::runtime_error if input variable name is duplicated with the other names in name vector.

      \param index index of the variable in the seed vector
      \param var_name variable name to be set
   */
   void setName(int index, std::string var_name);

   //! Set name of all the variables
   /*!
      It will throw std::range_error if the new seed vector's dimension not matched 
      with previous name vector's dimension. If that is the case, please use \sa clearName() first!

      It will throw std::range_error if the new seed vector's dimension not matched 
      with the existed seed vector's dimension. If that is the case, you probably want to do
      \sa set_seed() first!

      It will throw std::runtime_error if input names are not unique.

      \param names all the variable names to be set
   */
   void setName(std::vector<std::string> names);

   //! Turn name mode on
   void setName();

   //! Turn name mode off
   void clearName();

};

/////////////////////////////////////////// PRINT

//! Print ADFunc Implementation
std::ostream& operator<<(std::ostream& os, const ADFunc& obj);

/////////////////////////////////////////// ARITHMETIC OPERATORS

//! Overload ADFunc + ADFunc
ADFunc operator + ( const ADFunc &lhs, const ADFunc &rhs ); 

//! Overload ADFunc + scalar number
ADFunc operator + ( const ADFunc &lhs, double rhs );

//! Overload scalar number + ADFunc
ADFunc operator + ( double lhs, const ADFunc &rhs);

//! Overload - ADFunc (Negation sign)
ADFunc operator - ( const ADFunc &obj);

//! Overload ADFunc + ADFunc
ADFunc operator - ( const ADFunc &lhs, const ADFunc &rhs );

//! Overload ADfunc - scalar number
ADFunc operator - ( const ADFunc &lhs, double rhs );

//! Overload scalar number - ADFunc
ADFunc operator - ( double lhs, const ADFunc &rhs);

//! Overload ADFunc * ADFunc
ADFunc operator * ( const ADFunc &lhs, const ADFunc &rhs );

//! Overload ADFunc * scalar number
ADFunc operator * ( const ADFunc &lhs, double rhs );

//! Overload scalar number * ADFunc
ADFunc operator * ( double lhs, const ADFunc &rhs);

//! Overload ADFunc / ADFunc
ADFunc operator / ( const ADFunc &lhs, const ADFunc &rhs );

//! Overload ADFunc / scalar number
ADFunc operator / ( const ADFunc &lhs, double rhs );

//! Overload  scarlar number / ADFunc
ADFunc operator / ( double lhs, const ADFunc &rhs);

/////////////////////////////////////////// RELATIONAL OPERATORS
//! Check LHS ADFunc's value == rhs
bool operator==(const ADFunc& lhs, double rhs);
//! Check RHS ADFunc's value == lhs
bool operator==(double lhs, const ADFunc& rhs);
//! Check LHS ADFunc's value == RHS ADFunc's value
bool operator==(const ADFunc& lhs, const ADFunc& rhs);

//! Check LHS ADFunc's value != RHS scalar number
bool operator!=(const ADFunc& lhs, double rhs);
//! Check RHS ADFunc's value != LHS scalar number
bool operator!=(double lhs, const ADFunc& rhs);
//! Check LHS ADFunc's value != RHS ADFunc's value
bool operator!=(const ADFunc& lhs, const ADFunc& rhs);

//! Check LHS ADFunc's value < RHS scalar number
bool operator<(const ADFunc& lhs, double rhs);
//! Check LHS scalar number < RHS ADFunc's value
bool operator<(double lhs, const ADFunc& rhs);
//! Check LHS ADFunc's value < RHS ADFunc's value
bool operator<(const ADFunc& lhs, const ADFunc& rhs);

//! Check LHS ADFunc's value <= RHS scalar number
bool operator<=(const ADFunc& lhs, double rhs);
//! Check LHS scarlar number <= RHS ADFunc's value
bool operator<=(double lhs, const ADFunc& rhs);
//! Check LHS ADFunc's value <= RHS ADFunc's value
bool operator<=(const ADFunc& lhs, const ADFunc& rhs);

//! Check LHS ADFunc's value > RHS scalar number
bool operator>(const ADFunc& lhs, double rhs);
//! Check LHS scalar number > RHS ADFunc's value
bool operator>(double lhs, const ADFunc& rhs);
//! Check LHS ADFunc's value <= RHS ADFunc's value
bool operator>(const ADFunc& lhs, const ADFunc& rhs);

//! Check LHS ADFunc's value >= RHS scalar number
bool operator>=(const ADFunc& lhs, double rhs);
//! Check LHS scalar number >= RHS ADFunc's value
bool operator>=(double lhs, const ADFunc& rhs);
//! Check LHS ADFunc's value >= RHS ADFunc's value
bool operator>=(const ADFunc& lhs, const ADFunc& rhs);

/////////////////////////////////////////// MATH LIB FUNCTIONS

/* 
* It wil throw std::invalid_argument error if LHS and RHS seed vectors' dimension not matched!
* 
* If it is in name mode and lhs and rhs objects' names are the same, 
* it will automatically convert lhs and rhs objects'names to the result.
* 
* It will throw std::invalid_argument error if one of LHS and RHS is in name mode, the other is not!
* 
* It will throw std::run_time error if LHS and RHS both in name mode but have different names!
* 
* It will throw std::domain_error if rhs value less than 0 because derivative NaN occurs!
* 
* It will throw std::range_error if rhs value equals 0 because derivative NaN occurs!
*/
ADFunc pow ( const ADFunc &lhs, const ADFunc &rhs );


ADFunc pow ( const ADFunc &lhs, double rhs );

/*! 
* It will throw std::domain_error if rhs value less than 0 because derivative NaN occurs!
* 
* It will throw std::range_error if rhs value equals 0 because derivative NaN occurs!
*/
ADFunc pow ( double lhs, const ADFunc &rhs);

//! cubic root
/*!
* It would throw std::domain_error if input value less than 0 as NaN occurs!
*/
ADFunc sqrt ( const ADFunc &obj);

ADFunc cbrt ( const ADFunc &obj);

//! the hypotenuse of a right-angled triangle whose legs are lhs and rhs
/*!
* It will throw std::invalid_argument if one of LHS and RHS is in name mode, the other is not!
*/
ADFunc hypot ( const ADFunc &obj);

//! natrual log
/*! It will throw std::domain_error if value less than 0! NaN occurs!
* 
* It will throw std::range_error if balue equals 0! NaN occurs!
*/
ADFunc log(const ADFunc &obj);

//! log at base 10
/*! It will throw std::domain_error if value less than 0! NaN occurs!
* 
* It will throw std::range_error if balue equals 0! NaN occurs!
*/
ADFunc log10(const ADFunc &obj);

//! log at base 2
/*! It will throw std::domain_error if value less than 0! NaN occurs!
* 
* It will throw std::range_error if balue equals 0! NaN occurs!
*/
ADFunc log2(const ADFunc &obj);  

//! log_e(1+x)
/*! It will throw std::domain_error if value less than 0! NaN occurs!
* 
* It will throw std::range_error if balue equals 0! NaN occurs!
*/
ADFunc log1p(const ADFunc &obj); 

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc exp ( const ADFunc &obj );

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc exp2 ( const ADFunc &obj );

//! e ^ ADFunc - 1
/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc expm1 ( const ADFunc &obj );

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc sin(const ADFunc &obj);

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc cos(const ADFunc &obj);

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc tan(const ADFunc &obj);

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc asin(const ADFunc &obj);

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc acos(const ADFunc &obj);

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc atan(const ADFunc &obj);

/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc sinh(const ADFunc &obj);
/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc cosh(const ADFunc &obj);
/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc tanh(const ADFunc &obj);
/*! If input obj is in name mode, it will convert name vectors to output!
*/
ADFunc asinh(const ADFunc &obj);
/*! If input obj is in name mode, it will convert name vectors to output!
* 
* It will throw std::domain_error if obj.val()*obj.val()-1 < 0 because NaN occurs!
* 
* It will throw std::range_error if obj.val()*obj.val()==0 because denominator equals 0! 
*/
ADFunc acosh(const ADFunc &obj);
/*! If input obj is in name mode, it will convert name vectors to output!
* 
* It will throw std::range_error if obj.val()*obj.val()==0 because denominator equals 0! 
*/
ADFunc atanh(const ADFunc &obj);


/////////////////////////////////////////// NAME MODE
//! check LHS and RHS ADFunc objects have comptabile name
/*! It will return true when
 *
 * case 1: lhs and rhs both not in name mode
 *
 * case 2: lhs and rhs both in name mode, and their variables'names are the same
 * 
 * It will raise an error when 
 * lhs and rhs both in name mode, but have different names for some variables
 *
 * It will return false it only one of LHS and RHS is in name mode but not an error.
*/
bool checkName(const ADFunc &lhs, const ADFunc & rhs);

////////////////////////////////////////// VECTOR INPUT

//! Create Vectorized ADFunc variables
/*! Create multiple functions/variables given multiple intial values. 
* By default intilaize seed vectors as unit vectors automatically for you
*/ 
std::vector<ADFunc> multiVar(std::vector<double> values);

//! Set seed vectors back to default (unit vectors)
/* Set all the seeds vectors of input ADFunc back to unit vectors
*/
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