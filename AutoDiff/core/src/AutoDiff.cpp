#include "AutoDiff.h"
#include <math.h>
#include <vector>
#include <typeinfo>
#include <iterator>
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include <cmath>

/////////////////////////////////////////// CONSTRUCTOR
AutoDiff::AutoDiff(double val, std::vector<double> seed) {
  _val = val;
  _grad = seed;
  _num_vars = seed.size();
}

/////////////////////////////////////////// OVERLOAD OPERATORS

/////////////////////// +
// overload AutoDiff += AutoDiff
AutoDiff AutoDiff::operator += (const AutoDiff &obj) {
  _val += obj.val();
  
  if( obj.countVar()!= _num_vars ){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
  for(int i=0; i<_num_vars;i++){
    _grad[i] += obj.gradient().at(i);
  }
  return *this;
};

// overload AutoDiff += double
AutoDiff AutoDiff::operator += ( double obj ) {
  _val += obj;
  return *this;
};

// overload double + AutoDiff
AutoDiff operator + (double lhs, const AutoDiff &rhs) {
    return AutoDiff(lhs+rhs.val(),rhs.gradient());
}

// overload AutoDiff + AutoDiff
AutoDiff operator + ( const AutoDiff &lhs, const AutoDiff &rhs )
{   
    if(lhs.countVar()!=rhs.countVar()) {
      throw std::out_of_range("Seed vectors dimension not matched!");
    }
    std::vector<double> grad;
    for(int i=0;i<lhs.countVar();i++){
      grad.push_back(lhs.dval_wrt(i)+rhs.dval_wrt(i));
    }
    return AutoDiff(lhs.val()+rhs.val(),grad);
}

// overload AutoDiff + double
AutoDiff operator + ( const AutoDiff &lhs, double rhs )
{
    return AutoDiff(lhs.val()+rhs, lhs.gradient());
}

/////////////////////// NEGATION
// overload unary negation (- AutoDiff)
AutoDiff operator -(const AutoDiff &obj) {
  std::vector<double> grad;
  for(int i=0; i<obj.countVar();i++){
    grad.push_back(-obj.gradient()[i]);
  }
  return AutoDiff(-obj.val(),grad);
};

// overload AutoDiff -= double
AutoDiff AutoDiff::operator -= ( double obj ) {
  _val -= obj;
  return *this;
};

// overload AutoDiff -= AutoDiff
AutoDiff AutoDiff::operator -= (const AutoDiff &obj) {
  _val -= obj.val();
  
  if( obj.countVar()!= _num_vars ){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
  for(int i=0; i<_num_vars;i++){
    _grad[i] -= obj.gradient().at(i);
  }
  return *this;
}

/////////////////////// -
// overload AutoDiff - AutoDiff
AutoDiff operator - ( const AutoDiff &lhs, const AutoDiff &rhs ) {
  if(lhs.countVar()!=rhs.countVar()){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
    
    std::vector<double> grad;
    for(int i=0;i<lhs.countVar();i++){
      grad.push_back(lhs.dval_wrt(i)-rhs.dval_wrt(i));
    }
    return AutoDiff(lhs.val()-rhs.val(),grad);
};

// overload AutoDiff - double
AutoDiff operator - ( const AutoDiff &lhs, double rhs ) {
  return AutoDiff(lhs.val()-rhs,lhs.gradient());
};

// overload double - AutoDiff
AutoDiff operator - (double lhs, const AutoDiff &rhs) {
    return -rhs + lhs;
}

/////////////////////// *
// overload AutoDiff *= AutoDiff
AutoDiff AutoDiff::operator *= ( const AutoDiff &obj) {
  
  if(_num_vars!=obj.countVar()){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
  std::vector<double> grad;
  for(int i=0;i<obj.countVar();i++){
    _grad[i] = _grad[i] * obj.val() + obj.gradient()[i] * _val;
  }
  _val *= obj.val();

  return *this;
};

// overload AutoDiff *= double
AutoDiff AutoDiff::operator *= ( double obj ) {
  _val *= obj;
  for(int i=0;i<_num_vars;i++){
    _grad[i] *= obj;
  }
  return *this;
};

// overload AutoDiff * AutoDiff
AutoDiff operator * ( const AutoDiff &lhs, const AutoDiff &rhs ) {
  // (x+3y+z)*(2x+4y-z)
  // 2x^2 + 4xy-xz + 6xy + 2xz
  // dval with respect to x:4x+4y-z+6y+2z
  // dval with respect to x:(2x+4y-z) + 2(x+3y+z)
  double val = lhs.val() * rhs.val();
  if(lhs.countVar()!=rhs.countVar()){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
  std::vector<double> grad;
  for(int i=0;i<lhs.countVar();i++){
    grad.push_back(lhs.gradient()[i] * rhs.val() + rhs.gradient()[i] * lhs.val());
  }

  return AutoDiff(val, grad);
};

// overload AutoDiff * double
AutoDiff operator * (const AutoDiff &lhs, double rhs ) {
  double val = lhs.val() * rhs;
  std::vector<double> grad;
  for(int i=0;i<lhs.countVar();i++){
    grad.push_back(lhs.gradient()[i] * rhs);
  }
  return AutoDiff(lhs.val()*rhs,grad);
};

// overload double * AutoDiff
AutoDiff operator * (double lhs, const AutoDiff &rhs) {
    return rhs * lhs;
}


/////////////////////// /

// overload AutoDiff /= AutoDiff
AutoDiff AutoDiff::operator /= ( const AutoDiff &obj) {

  if(_num_vars!=obj.countVar()){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
  
  for(int i=0;i<obj.countVar();i++){
    _grad[i] = (_grad[i] * obj.val() - obj.gradient()[i] * _val)/(obj.val() * obj.val());
  }
  _val = _val / obj.val();

  return *this;
};

// overload AutoDiff /= double
AutoDiff AutoDiff::operator /= ( double obj ) {
  _val = _val / obj;
  for(int i=0;i<_num_vars;i++){
    _grad[i] /= obj;
  }

  return *this;
};

// overload AutoDiff / AutoDiff
AutoDiff operator / ( const AutoDiff &lhs, const AutoDiff &rhs) {
  double val = lhs.val()/rhs.val();
  if(lhs.countVar()!=rhs.countVar()){
    throw std::out_of_range("Seed vectors dimension not matched!");
  }
  std::vector<double> grad;
  for(int i=0;i<lhs.countVar();i++){
    grad.push_back( (lhs.gradient()[i]*rhs.val()-lhs.val()*rhs.gradient()[i])/(rhs.val()*rhs.val()));
  }
  return AutoDiff(val, grad);
};

// overload AutoDiff / double
AutoDiff operator / ( const AutoDiff &lhs, double rhs ) {
  std::vector<double> grad;
  for(int i=0;i<lhs.countVar();i++){
    grad.push_back(lhs.gradient()[i]/rhs);
  }
  return AutoDiff(lhs.val()/rhs, grad);
};

// overload double / AutoDiff
AutoDiff operator / (double lhs, const AutoDiff &rhs) {
    std::vector<double> grad;
    for(int i=0;i<rhs.countVar();i++){
      grad.push_back( (-rhs.gradient()[i])/(rhs.val()*rhs.val())*lhs );
    }
    return AutoDiff(lhs/rhs.val(), grad);
}

/*
/////////////////////// pow
// AutoDiff ^ AutoDiff
AutoDiff pow ( const AutoDiff &lhs, const AutoDiff &rhs ) {

  double val = std::pow(lhs.getVal(), rhs.getVal());
  double der = std::pow(lhs.getVal(), rhs.getVal()) * rhs.getDer() * log(lhs.getVal())\
    + std::pow(lhs.getVal(), rhs.getVal() - 1) * rhs.getVal() * lhs.getDer();

  return AutoDiff(val,der);
};

// AutoDiff ^ double
AutoDiff pow ( const AutoDiff &obj, double a ) {

  double val = std::pow(obj.getVal(), a);
  double der = a * std::pow(obj.getVal(), a - 1) * obj.getDer();

  return AutoDiff(val,der);
};

// double ^ AutoDiff
AutoDiff pow (double lhs, const AutoDiff &rhs) {
  
  double val = std::pow(2, rhs.getVal());
  double der = log(lhs) * rhs.getDer() * std::pow(2, rhs.getVal());

  return AutoDiff(val,der);
};


/////////////////////// exp
// e ^ AutoDiff
AutoDiff exp ( AutoDiff &a ) {
  return AutoDiff(  exp(a.getVal()),exp(a.getVal()) * a.getDer() );
};*/


/////////////////////////////////////////// SET VAL / DER VARS

// set val
void AutoDiff::setVal(double obj) {
  _val = obj;
}

// set dval with respect to a variable
void AutoDiff::set_dval_wrt(int index, double dval) {
  if(index>=_num_vars) throw std::out_of_range("Index out of range!");
  _grad[index] = dval;
}

// set dvals with all the variables
void AutoDiff::set_dval(std::vector<double> dvals){
  _grad = dvals; 
}

/////////////////////////////////////////// VIEW  VAL / DVAL VARS

// get total number of variables
int AutoDiff::countVar() const{
  return _num_vars;
}

// get val
double AutoDiff::val() const {
  return _val;
}

// get dval with respect to a variable
double AutoDiff::dval_wrt(int index) const {
  if(index>=_num_vars) throw std::out_of_range("Index out of range!");
  return _grad[index];
}

// get gradient (all the variables)
std::vector<double> AutoDiff::gradient() const {
  std::vector<double> grad_copy = _grad;
  return grad_copy;
}

/*
/////////////////////////////////////////// PRINT VAL AND DER

void AutoDiff::print() { 
  std::cout << "print function called --- val: " << val << " " << "der: " << der << std::endl; 
} 

AutoDiff sin(const AutoDiff &input)
{

    double val = sin( (input.getVal()));
    double dv = cos(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff cos(const AutoDiff &input)
{   
    
    double val = cos(input.getVal());
    double dv = -sin(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff tan(const AutoDiff &input)
{
    
    double val = tan(input.getVal());
    double dv = (1/pow(cos(input.getVal()), 2)) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff asin(const AutoDiff &input)
{
    
    double val = asin(input.getVal());
    double dv = (1/sqrt(1 - pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff acos(const AutoDiff &input)
{
    
    double val = acos(input.getVal());
    double dv = -(1/sqrt(1 - pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff atan(const AutoDiff &input)
{
    
    double val = atan(input.getVal());
    double dv = (1/(1+pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff log(const AutoDiff &input)
{
    
    double val = log(input.getVal());
    double dv = (1/input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff sinh(const AutoDiff &input)
{
    
    double val = sinh(input.getVal());
    double dv = cosh(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff cosh(const AutoDiff &input)
{
    
    double val = cosh(input.getVal());
    double dv = sinh(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff tanh(const AutoDiff &input)
{
    
    double val = tanh(input.getVal());
    double dv = (1/pow(cosh(input.getVal()), 2)) * input.getDer();
    return AutoDiff(val,dv);
}*/