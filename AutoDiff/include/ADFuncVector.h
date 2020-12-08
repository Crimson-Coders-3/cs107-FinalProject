#ifndef ADFUNCVECTOR_H
#define ADFUNCVECTOR_H

#include <vector>
#include <iostream>
#include <ADFunc.h>

///////////////////////////////////////////////////////////////// CUSTOM ADFuncVector CLASS
class ADFuncVector {

   /////////////////////////////////////////// CLASS DEF
   // private
   private:
      // private variable
      int _size;
      std::vector<ADFunc> _funcVec;

   // public
   public:
      // constructor
      ADFuncVector(int size);
      ADFuncVector(int size, std::vector<ADFunc> funcVec);

   /////////////////////////////////////////// GETTER

   // get size of ADFunc Vector
   int size();

   // check if _funcVec.size() matches with _size
   bool checkValid();

   // get partial derivative of ADFunc Vector with respect to a variable 
   // given its variable index in seed vector
   // 1-d dval vector returned
   std::vector<double> dval_wrt(int index);

   // get partial derivative of ADFunc Vector with respect to a variable 
   // given its variable name
   // 1-d dval vector returned
   std::vector<double> dval_wrt(std::string var_name);

   // Given function index and corresponding variable index,
   // get partial derivative of ADFunc Vector with respect to more than one variables 
   // 1-d dval vector returned
   std::vector<double> dval_wrt(std::vector<std::pair<int, int> > fun_var);

   // Given function index and variable name, 
   // get partial derivative of ADFunc Vector with respect to more than one variables 
   // 1-d dval vector returned
   std::vector<double> dval_wrt(std::vector<std::pair<int, std::string> > fun_var);
   
   // Given function index and variable index, 
   // get partial derivative of ADFunc Vector with respect to more than one variables 
   // 2-d dval vector returned
   std::vector<std::vector<double> > dval_wrt(std::vector<std::vector<std::pair<int, int> > > fun_var);

   // Given function index and variable name, 
   // get partial derivative of ADFunc Vector with respect to more than one variables 
   // 2-d dval vector returned
   std::vector<std::vector<double> > dval_wrt(std::vector<std::vector<std::pair<int, std::string> > > fun_var);

   // get ith ADFunc from ADFuncVector. Return a pointer that enables user to modify ADFunc
   ADFunc* index(int i);

   /////////////////////////////////////////// SETTER

   void setSize(int size);

   void setFuncVec(std::vector<ADFunc> funcVec);

   void set(int size, std::vector<ADFunc> funcVec);
};

#endif