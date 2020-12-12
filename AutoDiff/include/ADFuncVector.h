/**
 * \ingroup AutoDiff_group AutoDiff
 */

/**
* \file ADFuncVector.h
* \author team 3
*
*/

#ifndef ADFUNCVECTOR_H
#define ADFUNCVECTOR_H

#include <vector>
#include <iostream>
#include <ADFunc.h>

/**
* \class ADFuncVector
* \brief 
* ADFuncVector represents a vector of functions and performs automatic differentiation on this 
* vectorized functions as a whole. It is a wrapper class of std::vector<ADFunc> to make taking
* partial derivative from vectorized functions easier (we write the for-loops of .dval_wrt()
* for you so all you need to do is declaring a ADFuncVector and calling its member functions)!
* You have many options of taking partial derivatives of a ADFuncVector object, whether you want
* a scalar number, a 1-d vector, or a 2-D matrix. We also support a function of getting Jacobian matrix 
* for your convenience. 
*/

class ADFuncVector {

   private:
      /** Flag indicating whether the default or the initializer constructor was employed. */
      int _size;
      int _num_vars;
      std::vector<ADFunc> _funcVec;

   public:
      ADFuncVector();
      //! A constructor.
      /*!
         Initializes a ADFuncVector given the size of the vector of ADFunc.

         \param size the total number of functions
      */
      ADFuncVector(int size);
      //! A constructor.
      /*!
         Initializes a ADFuncVector given the size of the vector of ADFunc.

         All the input functions should have same have number of varibales. This means their
         seed vectors should be in the same size and represent variables in the same order for consistency. 
         
         \param funcVec vector of functions in std::vector<ADFunc>
      */
      ADFuncVector(std::vector<ADFunc> funcVec);

   /////////////////////////////////////////// GETTER

   //! Get val of a function
   /*!
      It will throw a std::out_of_range error if index is out of range of ADFuncVector.

      \param index function index
   */
   double val(int index);

   //! Get size of ADFuncVector
   /*!
      It will 0 if the vector of functions are not set yet.
   */
   int size();

   //! Check validity
   /*!
      It will return true/false the current ADFuncVector object is valid. If not valid, it 
      will throw clear error messages and suggested solutions.
   */
   bool checkValid();

   //! Check if ADFuncVector is empty
   bool empty();

   //! Get partial derivative
   /*! It will return 1-d vector of partial derivatives of ADFuncVector, the case that
       all the functions with respect to(wrt) a variable given this variable's index in seed vector. 
   */
   std::vector<double> dval_wrt(int index);

   //! Get partial derivative
   /*! It will return 1-d vector of partial derivatives of ADFuncVector, the case that 
      all the functions with respect to(wrt) a variable given its variable name.
   */
   std::vector<double> dval_wrt(std::string var_name);

   //! Get partial derivative 
   /*! It will return a single partial derivative of ADFuncVector, the case that 
       a particular function with respect to(wrt) a variable 
       given function index and variable index in seed vector.
   */
   double dval_wrt(int func_index, int var_index);

   //! Get partial derivative 
   /*! It will return a single partial derivative of ADFuncVector, the case that 
       a particular function with respect to(wrt) a variable 
       given function index and variable name.
   */
   double dval_wrt(int func_index, std::string var_name);

   //! Get partial derivative 
   /*! It will return 1-d vector of partial derivatives of ADFuncVector, when 
       each pair of function index and corresponding variable index is given.
   */
   std::vector<double> dval_wrt(std::vector<std::pair<int, int> > fun_var);

   //! Get partial derivative 
   /*! It will return 1-d vector of partial derivatives of ADFuncVector, when
      each pair of function index and corresponding variable name is given.
   */
   std::vector<double> dval_wrt(std::vector<std::pair<int, std::string> > fun_var);
   
   //! Get partial derivative 
   /*! It will return 2-d matrix (vector of vector) of partial derivatives of ADFuncVector, when 
       each pair of function index and corresponding variable index is given.
   */
   std::vector<std::vector<double> > dval_wrt(std::vector<std::vector<std::pair<int, int> > > fun_var);

   //! Get partial derivative 
   /*! It will return 2-d matrix (vector of vector) of partial derivatives of ADFuncVector, when 
       each pair of function index and corresponding variable name is given.
   */
   std::vector<std::vector<double> > dval_wrt(std::vector<std::vector<std::pair<int, std::string> > > fun_var);

   //! Get Jacobian matrix
   /*! It will return the jacobian matrix of ADFuncVector, using the order of functions when ADFuncVector 
       object is intialized and the order of variables of in the seed vector as coordinates of the 
       returned Jacobian matrix.
   */
   std::vector<std::vector<double> > jacobian();

   //! Get ith ADFunc
   /*! It will return a ADFunc pointer that enables modifying ADFunc
   */
   ADFunc* at(int i);

   //! Get the number of variables
   int countVar();

   /////////////////////////////////////////// SETTER

   //! Set size
   /*! Sets size of ADFunc vector (the number of functions).
       
       It will return a std::runtime_error if this input size mismatches with current funcVector! 
       If that is the case, please use clear() before set size.

       /param size size of ADFunc vector (the number of functions)
   */
   void setSize(int size);

   //! Set vector of functions
   /*! Set vector of functions.
      
      It will return a std::runtime_error if this input size mismatches with currently defined size! 
      If that is the case, please use clear() before setFuncVec.

      All the input functions should have same have number of varibales. This means their
      seed vectors should be in the same size and represent variables in the same order for consistency. 
      It will throw std::runtime_error if this requirement doesn't met.
   */
   void setFuncVec(std::vector<ADFunc> funcVec);

   //! Clear size and ADFunc vector
   void clear();

   //! Append a ADFunc
   /*!
      Appends a new ADFunc to the end of ADFuncVector.
   */
   void push_back(ADFunc func);
};

#endif
