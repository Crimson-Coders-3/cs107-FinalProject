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
  _hasName = false;
}

AutoDiff::AutoDiff(double val, std::vector<double> seed, std::vector<std::string> var_names) {
  _val = val;
  _grad = seed;
  _num_vars = seed.size();
  _names = var_names;
  _hasName = true;
}

/////////////////////////////////////////// OVERLOAD OPERATORS

/////////////////////// +
// overload AutoDiff += AutoDiff
AutoDiff AutoDiff::operator += (const AutoDiff &obj) {
  _val += obj.val();
  
  if( obj.countVar()!= _num_vars ){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  for(int i = 0; i < _num_vars; i++){
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
      throw std::invalid_argument("Seed vectors dimension not matched!");
    }
    std::vector<double> grad;
    for(int i = 0; i < lhs.countVar(); i++){
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
  for(int i = 0; i < obj.countVar(); i++){
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
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  for(int i = 0; i < _num_vars; i++){
    _grad[i] -= obj.gradient().at(i);
  }
  return *this;
}

/////////////////////// -
// overload AutoDiff - AutoDiff
AutoDiff operator - ( const AutoDiff &lhs, const AutoDiff &rhs ) {
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
    
    std::vector<double> grad;
    for(int i = 0;i < lhs.countVar(); i++){
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
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  std::vector<double> grad;
  for(int i = 0;i < obj.countVar(); i++){
    _grad[i] = _grad[i] * obj.val() + obj.gradient()[i] * _val;
  }
  _val *= obj.val();

  return *this;
};

// overload AutoDiff *= double
AutoDiff AutoDiff::operator *= ( double obj ) {
  _val *= obj;
  for(int i = 0;i < _num_vars; i++){
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
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back(lhs.gradient()[i] * rhs.val() + rhs.gradient()[i] * lhs.val());
  }

  return AutoDiff(val, grad);
};

// overload AutoDiff * double
AutoDiff operator * (const AutoDiff &lhs, double rhs ) {
  double val = lhs.val() * rhs;
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
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
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  
  for(int i = 0;i < obj.countVar(); i++){
    _grad[i] = (_grad[i] * obj.val() - obj.gradient()[i] * _val)/(obj.val() * obj.val());
  }
  _val = _val / obj.val();

  return *this;
};

// overload AutoDiff /= double
AutoDiff AutoDiff::operator /= ( double obj ) {
  _val = _val / obj;
  for(int i = 0;i < _num_vars; i++){
    _grad[i] /= obj;
  }

  return *this;
};

// overload AutoDiff / AutoDiff
AutoDiff operator / ( const AutoDiff &lhs, const AutoDiff &rhs) {
  double val = lhs.val()/rhs.val();
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back( (lhs.gradient()[i]*rhs.val()-lhs.val()*rhs.gradient()[i])/(rhs.val()*rhs.val()));
  }
  return AutoDiff(val, grad);
};

// overload AutoDiff / double
AutoDiff operator / ( const AutoDiff &lhs, double rhs ) {
  std::vector<double> grad;
  for(int i = 0;i < lhs.countVar(); i++){
    grad.push_back(lhs.gradient()[i]/rhs);
  }
  return AutoDiff(lhs.val()/rhs, grad);
};

// overload double / AutoDiff
AutoDiff operator / (double lhs, const AutoDiff &rhs) {
    std::vector<double> grad;
    for(int i = 0; i < rhs.countVar(); i++){
      grad.push_back( (-rhs.gradient()[i])/(rhs.val()*rhs.val())*lhs );
    }
    return AutoDiff(lhs/rhs.val(), grad);
}


/////////////////////// pow
// AutoDiff ^ AutoDiff
AutoDiff pow ( const AutoDiff &lhs, const AutoDiff &rhs ) {
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  double val = std::pow(lhs.val(), rhs.val());
  std::vector<double> grad;
  for (int i = 0; i < rhs.countVar(); ++i) {
    // log(lhs.val()) so lhs.val() must > 0
    if(lhs.val()<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(lhs.val()==0){
      throw std::range_error("Value equals 0!");
    }
    grad.push_back( std::pow(lhs.val(), rhs.val()) * rhs.gradient()[i] * log(lhs.val())\
                  +std::pow(lhs.val(), rhs.val() - 1) * rhs.val() * lhs.gradient()[i]);
  }

  return AutoDiff(val,grad);
};

// AutoDiff ^ double
AutoDiff pow ( const AutoDiff &lhs, double rhs) {

  double val = std::pow(lhs.val(), rhs);
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back(rhs * std::pow(lhs.val(),rhs-1) * lhs.gradient()[i]);
  }

  return AutoDiff(val,grad);
};

// double ^ AutoDiff
AutoDiff pow (double lhs, const AutoDiff &rhs) {
  
  double val = std::pow(lhs, rhs.val());
  std::vector<double> grad;
  for(int i = 0; i < rhs.countVar(); i++){
    // log(lhs) so lhs must > 0
    if(lhs<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(lhs==0){
      throw std::range_error("Value equals 0!");
    }
    grad.push_back( log(lhs) * std::pow(lhs,rhs.val()) * rhs.gradient()[i] );
  }

  return AutoDiff(val,grad);
};

/////////////////////// exp
// e ^ AutoDiff
AutoDiff exp ( AutoDiff &obj ) {
  
  std::vector<double> grad;
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( exp(obj.val()) * obj.gradient()[i] );
  }
  return AutoDiff(  exp(obj.val()), grad );
};

/////////////////////// log
AutoDiff log(const AutoDiff &obj)
{ 
    if(obj.val()<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(obj.val()==0){
      throw std::range_error("Value equals 0!");
    }
    double val = log(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

/////////////////////// log
AutoDiff log10(const AutoDiff &obj)
{
    
    if(obj.val()<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(obj.val()==0){
      throw std::range_error("Value equals 0! NaN occurs!");
    }
    double val = log(obj.val())/log(10);
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/obj.val()) * obj.gradient()[i] /log(10) );
    }
    return AutoDiff(val,grad);
}

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

// get if variables have names, 
// e.g. represented by std::vector<std::string> {"x", "y","z"}
bool AutoDiff::hasName() const {
  return _hasName;
}

/////////////////////////////////////////// PRINT VAL AND DER

std::ostream& operator<<(std::ostream& os, const AutoDiff& obj){
    os << "Information of AutoDiff object: \n";
    os << "Value at " << obj.val() << ". ";
    os << obj.countVar() << " variable(s) in total.\n";

    for(int i = 0; i < obj.countVar() ; i++){
      os << "   " << i << "th variable: dval = " << obj.gradient()[i] << std::endl;
    } 
    return os;
}

AutoDiff sin(const AutoDiff &obj)
{

    double val = sin( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( cos(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff cos(const AutoDiff &obj)
{   
    
    double val = cos( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( -sin(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff tan(const AutoDiff &obj)
{
    
    double val = tan( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/pow(cos(obj.val()),2) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff asin(const AutoDiff &obj)
{
    
    double val = asin(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/sqrt(1 - pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff acos(const AutoDiff &obj)
{
    
    double val = acos(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( -1/sqrt(1 - pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff atan(const AutoDiff &obj)
{
    
    double val = atan(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/(1 + pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff sinh(const AutoDiff &obj)
{
    
    double val = sinh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( cosh(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff cosh(const AutoDiff &obj)
{
    
    double val = cosh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( sinh(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff tanh(const AutoDiff &obj)
{
    
    double val = tanh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/pow(cosh(obj.val()), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}