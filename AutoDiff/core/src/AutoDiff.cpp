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

AutoDiff AutoDiff::operator =(const AutoDiff &obj) {
  _val = obj.val();
  _grad = obj.gradient();
  _num_vars = obj.countVar();
  if(obj.hasName()){
    _names = obj.getNames();
    _hasName = true;
  } else {
    _hasName = false;
  }
  return *this;
}

/////////////////////////////////////////// + OPERATORS

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
AutoDiff operator + ( const AutoDiff &lhs, const AutoDiff &rhs ){   
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
AutoDiff operator + ( const AutoDiff &lhs, double rhs ){
    return AutoDiff(lhs.val()+rhs, lhs.gradient());
}

/////////////////////////////////////////// - OPERATORS

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

/////////////////////////////////////////// * OPERATORS

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


/////////////////////////////////////////// '/' OPERATORS

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

/////////////////////////////////////////// RELATIONAL OPERATORS
bool operator==(const AutoDiff& lhs, double rhs){
  return lhs.val() == rhs;
}
bool operator==(double lhs, const AutoDiff& rhs){
  return lhs == rhs.val();
}
bool operator==(const AutoDiff& lhs, const AutoDiff& rhs){
  if(lhs.val()!=rhs.val()){
    return false;
  }
  if(lhs.countVar()!=rhs.countVar()){
    return false;
  }
  for(int i=0;i<lhs.countVar();i++){
    if(lhs.gradient()[i]!=rhs.gradient()[i]){
      return false;
    }
  }
  return true;
}

bool operator!=(const AutoDiff& lhs, double rhs){
  return !(lhs==rhs);
}
bool operator!=(double lhs, const AutoDiff& rhs){
  return !(lhs==rhs);
}
bool operator!=(const AutoDiff& lhs, const AutoDiff& rhs){
  return !(lhs==rhs);
}

bool operator<(const AutoDiff& lhs, double rhs){
  return lhs.val()<rhs;
}
bool operator<(double lhs, const AutoDiff& rhs){
  return lhs<rhs.val();
}
bool operator<(const AutoDiff& lhs, const AutoDiff& rhs){
  return lhs.val()<rhs.val();
}

bool operator<=(const AutoDiff& lhs, double rhs){
  return lhs.val()<=rhs;
}
bool operator<=(double lhs, const AutoDiff& rhs){
  return lhs<=rhs.val();
}
bool operator<=(const AutoDiff& lhs, const AutoDiff& rhs){
  return lhs.val()<=rhs.val();
}

bool operator>(const AutoDiff& lhs, double rhs){
  return lhs.val()>rhs;
}
bool operator>(double lhs, const AutoDiff& rhs){
  return lhs>rhs.val();
}
bool operator>(const AutoDiff& lhs, const AutoDiff& rhs){
  return lhs.val()>rhs.val();
}

bool operator>=(const AutoDiff& lhs, double rhs){
  return lhs.val()>rhs;
}
bool operator>=(double lhs, const AutoDiff& rhs){
 return lhs>rhs.val();
}
bool operator>=(const AutoDiff& lhs, const AutoDiff& rhs){
 return lhs.val()>rhs.val();
}

/////////////////////////////////////////// POWER OPERATORS

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

/////////////////////////////////////////// EXPONENT OPERATORS

// e ^ AutoDiff
AutoDiff exp ( const AutoDiff &obj ) {
  
  std::vector<double> grad;
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( exp(obj.val()) * obj.gradient()[i] );
  }
  return AutoDiff(  exp(obj.val()), grad );
};

// 2 ^ AutoDiff
AutoDiff exp2 ( const AutoDiff &obj ){
  std::vector<double> grad;
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( std::pow(2.0, obj.val()) * obj.gradient()[i] * log(2.0) );
  }
  return AutoDiff(  pow(2.0,obj.val()), grad );
}

// e ^ AutoDiff - 1
AutoDiff expm1 ( const AutoDiff &obj ){
  return exp(obj) - 1;
}

// square root
AutoDiff sqrt ( const AutoDiff &obj){
  if(obj.val()<0){
    throw std::domain_error("Value less than 0! NaN occurs!");
  }
  return pow(obj,0.5);
}

// cubic root
AutoDiff cbrt ( const AutoDiff &obj){
  return pow(obj,1.0/3);
}

// the hypotenuse of a right-angled triangle whose legs are lhs and rhs
AutoDiff hypot ( const AutoDiff &lhs, const AutoDiff &rhs) {
  return sqrt(pow(lhs,2.0)+pow(rhs,2.0));
}

/////////////////////////////////////////// LOG OPERATORS

// natural log, log_e(x)
AutoDiff log(const AutoDiff &obj){ 
    if(obj.val()<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(obj.val()==0){
      throw std::range_error("Value equals 0! NaN occurs!");
    }
    double val = log(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

// log_10(x)
AutoDiff log10(const AutoDiff &obj) {
    
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

// log_2(x)
AutoDiff log2(const AutoDiff &obj){
    if(obj.val()<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(obj.val()==0){
      throw std::range_error("Value equals 0! NaN occurs!");
    }
    double val = log(obj.val())/log(2);
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/obj.val()) * obj.gradient()[i] /log(2) );
    }
    return AutoDiff(val,grad);
}

// log_e(1+x)
AutoDiff log1p(const AutoDiff &obj){
    if(obj.val()+1<0){
      throw std::domain_error("Value less than 0! NaN occurs!");
    }
    if(obj.val()+1==0){
      throw std::range_error("Value equals 0! NaN occurs!");
    }
    double val = log(obj.val()+1);
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/(obj.val()+1) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

/////////////////////////////////////////// SETTERS

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

/////////////////////////////////////////// GETTERS

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

// get names of all variables
std::vector<std::string> AutoDiff::getNames() const {
  std::vector<std::string> names = _names;
  return names;
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

/////////////////////////////////////////// TRIGONOMETRIC FUNCTIONS

AutoDiff sin(const AutoDiff &obj){

    double val = sin( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( cos(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff cos(const AutoDiff &obj){   
    
    double val = cos( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( -sin(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff tan(const AutoDiff &obj){
    
    double val = tan( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/pow(cos(obj.val()),2) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff asin(const AutoDiff &obj){
    
    double val = asin(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/sqrt(1 - pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff acos(const AutoDiff &obj){
    
    double val = acos(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( -1/sqrt(1 - pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff atan(const AutoDiff &obj){
    
    double val = atan(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/(1 + pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

/////////////////////////////////////////// HYPERBOLIC FUNCTIONS

AutoDiff sinh(const AutoDiff &obj){
    
    double val = sinh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( cosh(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff cosh(const AutoDiff &obj){
    
    double val = cosh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( sinh(obj.val()) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff tanh(const AutoDiff &obj){
    
    double val = tanh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/pow(cosh(obj.val()), 2)) * obj.gradient()[i] );
    }
    return AutoDiff(val,grad);
}

AutoDiff asinh(const AutoDiff &obj){
  double val = asinh(obj.val());
  std::vector<double> grad;

  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( 1/sqrt(obj.val()*obj.val()+1) * obj.gradient()[i] );
  }
  return AutoDiff(val,grad);
}

AutoDiff acosh(const AutoDiff &obj){
  double val = acosh(obj.val());
  std::vector<double> grad;

  if (obj.val()*obj.val()-1 < 0) {
    throw std::domain_error("Sqrt of value less than 0! NaN occurs!");
  }
  if (obj.val()*obj.val()-1 == 0) {
    throw std::range_error("Denominator equals 0!");
  }
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( 1/sqrt(obj.val()*obj.val()-1) * obj.gradient()[i] );
  }
  return AutoDiff(val,grad);
}

AutoDiff atanh(const AutoDiff &obj){
  double val = atanh(obj.val());
  std::vector<double> grad;
  
  if (1-obj.val()*obj.val() == 0) {
    throw std::range_error("Denominator equals 0!");
  }
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( 1/(1-obj.val()*obj.val()) * obj.gradient()[i] );
  }
  return AutoDiff(val,grad);
}