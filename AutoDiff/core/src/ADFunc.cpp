#include "ADFunc.h"
#include <math.h>
#include <vector>
#include <typeinfo>
#include <iterator>
#include <bits/stdc++.h> 
#include <iostream>
#include <string>
#include <cmath>

/////////////////////////////////////////// CONSTRUCTOR
ADFunc::ADFunc(double val, std::vector<double> seed) {
  _val = val;
  _grad = seed;
  _num_vars = seed.size();
  _hasName = false;
}

ADFunc::ADFunc(double val, std::vector<double> seed, std::vector<std::string> var_names) {
  if(seed.size()!=var_names.size()){
    throw std::invalid_argument("Dimension of seed vector and name vector not matched!");
  }
  _val = val;
  _grad = seed;
  _num_vars = seed.size();
  _name_vec = var_names;
  _hasName = true;

  std::unordered_map<std::string,int>::const_iterator got;

  for(int i=0;i<_num_vars;i++){
    got = _name_map.find(var_names[i]);
    if( got!= _name_map.end() ){
      throw std::runtime_error("Name must be unique!");
    }
    _name_map.insert(std::make_pair<std::string, int>(var_names[i],i));
  }
}

ADFunc ADFunc::operator =(const ADFunc &obj) {
  _val = obj.val();
  _grad = obj.gradient();
  _num_vars = obj.countVar();
  if(obj.hasName()){
    _name_vec = obj.getName();
    _hasName = true;
    _name_map.clear();
    for(int i=0;i<_num_vars;i++){
      _name_map.insert(std::make_pair<std::string, int>(_name_vec[i],i));
    }
  } else {
    _hasName = false;
    _name_map.clear();
    _name_vec.clear();
  }
  return *this;
}

/////////////////////////////////////////// + OPERATORS

// overload ADFunc += ADFunc
ADFunc ADFunc::operator += (const ADFunc &obj) {
  _val += obj.val();
  
  if( obj.countVar()!= _num_vars ){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  for(int i = 0; i < _num_vars; i++){
    _grad[i] += obj.gradient().at(i);
  }
  return *this;
};

// overload ADFunc += double
ADFunc ADFunc::operator += ( double obj ) {
  _val += obj;
  return *this;
};

// overload double + ADFunc
ADFunc operator + (double lhs, const ADFunc &rhs) {
    return ADFunc(lhs+rhs.val(),rhs.gradient());
}

// overload ADFunc + ADFunc
ADFunc operator + ( const ADFunc &lhs, const ADFunc &rhs ){   
    if(lhs.countVar()!=rhs.countVar()) {
      throw std::invalid_argument("Seed vectors dimension not matched!");
    }
    checkName(lhs,rhs);
    std::vector<double> grad;
    for(int i = 0; i < lhs.countVar(); i++){
      grad.push_back(lhs.dval_wrt(i)+rhs.dval_wrt(i));
    }
    return ADFunc(lhs.val()+rhs.val(),grad);
}

// overload ADFunc + double
ADFunc operator + ( const ADFunc &lhs, double rhs ){
    return ADFunc(lhs.val()+rhs, lhs.gradient());
}

/////////////////////////////////////////// - OPERATORS

// overload unary negation (- ADFunc)
ADFunc operator -(const ADFunc &obj) {
  std::vector<double> grad;
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back(-obj.gradient()[i]);
  }
  return ADFunc(-obj.val(),grad);
};

// overload ADFunc -= double
ADFunc ADFunc::operator -= ( double obj ) {
  _val -= obj;
  return *this;
};

// overload ADFunc -= ADFunc
ADFunc ADFunc::operator -= (const ADFunc &obj) {
  _val -= obj.val();
  
  if( obj.countVar()!= _num_vars ){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  for(int i = 0; i < _num_vars; i++){
    _grad[i] -= obj.gradient().at(i);
  }
  return *this;
}

// overload ADFunc - ADFunc
ADFunc operator - ( const ADFunc &lhs, const ADFunc &rhs ) {
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
    checkName(lhs,rhs);
    std::vector<double> grad;
    for(int i = 0;i < lhs.countVar(); i++){
      grad.push_back(lhs.dval_wrt(i)-rhs.dval_wrt(i));
    }
    return ADFunc(lhs.val()-rhs.val(),grad);
};

// overload ADFunc - double
ADFunc operator - ( const ADFunc &lhs, double rhs ) {
  return ADFunc(lhs.val()-rhs,lhs.gradient());
};

// overload double - ADFunc
ADFunc operator - (double lhs, const ADFunc &rhs) {
    return -rhs + lhs;
}

/////////////////////////////////////////// * OPERATORS

// overload ADFunc *= ADFunc
ADFunc ADFunc::operator *= ( const ADFunc &obj) {
  
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

// overload ADFunc *= double
ADFunc ADFunc::operator *= ( double obj ) {
  _val *= obj;
  for(int i = 0;i < _num_vars; i++){
    _grad[i] *= obj;
  }
  return *this;
};

// overload ADFunc * ADFunc
ADFunc operator * ( const ADFunc &lhs, const ADFunc &rhs ) {
  // (x+3y+z)*(2x+4y-z)
  // 2x^2 + 4xy-xz + 6xy + 2xz
  // dval with respect to x:4x+4y-z+6y+2z
  // dval with respect to x:(2x+4y-z) + 2(x+3y+z)
  double val = lhs.val() * rhs.val();
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  checkName(lhs,rhs);
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back(lhs.gradient()[i] * rhs.val() + rhs.gradient()[i] * lhs.val());
  }

  return ADFunc(val, grad);
};

// overload ADFunc * double
ADFunc operator * (const ADFunc &lhs, double rhs ) {
  double val = lhs.val() * rhs;
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back(lhs.gradient()[i] * rhs);
  }
  return ADFunc(lhs.val()*rhs,grad);
};

// overload double * ADFunc
ADFunc operator * (double lhs, const ADFunc &rhs) {
    return rhs * lhs;
}


/////////////////////////////////////////// '/' OPERATORS

// overload ADFunc /= ADFunc
ADFunc ADFunc::operator /= ( const ADFunc &obj) {

  if(_num_vars!=obj.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  
  for(int i = 0;i < obj.countVar(); i++){
    _grad[i] = (_grad[i] * obj.val() - obj.gradient()[i] * _val)/(obj.val() * obj.val());
  }
  _val = _val / obj.val();

  return *this;
};

// overload ADFunc /= double
ADFunc ADFunc::operator /= ( double obj ) {
  _val = _val / obj;
  for(int i = 0;i < _num_vars; i++){
    _grad[i] /= obj;
  }

  return *this;
};

// overload ADFunc / ADFunc
ADFunc operator / ( const ADFunc &lhs, const ADFunc &rhs) {
  double val = lhs.val()/rhs.val();
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  checkName(lhs,rhs);
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back( (lhs.gradient()[i]*rhs.val()-lhs.val()*rhs.gradient()[i])/(rhs.val()*rhs.val()));
  }
  return ADFunc(val, grad);
};

// overload ADFunc / double
ADFunc operator / ( const ADFunc &lhs, double rhs ) {
  std::vector<double> grad;
  for(int i = 0;i < lhs.countVar(); i++){
    grad.push_back(lhs.gradient()[i]/rhs);
  }
  return ADFunc(lhs.val()/rhs, grad);
};

// overload double / ADFunc
ADFunc operator / (double lhs, const ADFunc &rhs) {
    std::vector<double> grad;
    for(int i = 0; i < rhs.countVar(); i++){
      grad.push_back( (-rhs.gradient()[i])/(rhs.val()*rhs.val())*lhs );
    }
    return ADFunc(lhs/rhs.val(), grad);
}

/////////////////////////////////////////// RELATIONAL OPERATORS
bool operator==(const ADFunc& lhs, double rhs){
  return lhs.val() == rhs;
}
bool operator==(double lhs, const ADFunc& rhs){
  return lhs == rhs.val();
}
bool operator==(const ADFunc& lhs, const ADFunc& rhs){
  checkName(lhs,rhs);
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

bool operator!=(const ADFunc& lhs, double rhs){
  return !(lhs==rhs);
}
bool operator!=(double lhs, const ADFunc& rhs){
  return !(lhs==rhs);
}
bool operator!=(const ADFunc& lhs, const ADFunc& rhs){
  checkName(lhs,rhs);
  return !(lhs==rhs);
}

bool operator<(const ADFunc& lhs, double rhs){
  return lhs.val()<rhs;
}
bool operator<(double lhs, const ADFunc& rhs){
  return lhs<rhs.val();
}
bool operator<(const ADFunc& lhs, const ADFunc& rhs){
  return lhs.val()<rhs.val();
}

bool operator<=(const ADFunc& lhs, double rhs){
  return lhs.val()<=rhs;
}
bool operator<=(double lhs, const ADFunc& rhs){
  return lhs<=rhs.val();
}
bool operator<=(const ADFunc& lhs, const ADFunc& rhs){
  return lhs.val()<=rhs.val();
}

bool operator>(const ADFunc& lhs, double rhs){
  return lhs.val()>rhs;
}
bool operator>(double lhs, const ADFunc& rhs){
  return lhs>rhs.val();
}
bool operator>(const ADFunc& lhs, const ADFunc& rhs){
  return lhs.val()>rhs.val();
}

bool operator>=(const ADFunc& lhs, double rhs){
  return lhs.val()>rhs;
}
bool operator>=(double lhs, const ADFunc& rhs){
 return lhs>rhs.val();
}
bool operator>=(const ADFunc& lhs, const ADFunc& rhs){
 return lhs.val()>rhs.val();
}

/////////////////////////////////////////// POWER OPERATORS

// ADFunc ^ ADFunc
ADFunc pow ( const ADFunc &lhs, const ADFunc &rhs ) {
  if(lhs.countVar()!=rhs.countVar()){
    throw std::invalid_argument("Seed vectors dimension not matched!");
  }
  checkName(lhs,rhs);
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

  return ADFunc(val,grad);
};

// ADFunc ^ double
ADFunc pow ( const ADFunc &lhs, double rhs) {

  double val = std::pow(lhs.val(), rhs);
  std::vector<double> grad;
  for(int i = 0; i < lhs.countVar(); i++){
    grad.push_back(rhs * std::pow(lhs.val(),rhs-1) * lhs.gradient()[i]);
  }

  return ADFunc(val,grad);
};

// double ^ ADFunc
ADFunc pow (double lhs, const ADFunc &rhs) {
  
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

  return ADFunc(val,grad);
};

/////////////////////////////////////////// EXPONENT OPERATORS

// e ^ ADFunc
ADFunc exp ( const ADFunc &obj ) {
  
  std::vector<double> grad;
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( exp(obj.val()) * obj.gradient()[i] );
  }
  return ADFunc(  exp(obj.val()), grad );
};

// 2 ^ ADFunc
ADFunc exp2 ( const ADFunc &obj ){
  std::vector<double> grad;
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( std::pow(2.0, obj.val()) * obj.gradient()[i] * log(2.0) );
  }
  return ADFunc(  pow(2.0,obj.val()), grad );
}

// e ^ ADFunc - 1
ADFunc expm1 ( const ADFunc &obj ){
  return exp(obj) - 1;
}

// square root
ADFunc sqrt ( const ADFunc &obj){
  if(obj.val()<0){
    throw std::domain_error("Value less than 0! NaN occurs!");
  }
  return pow(obj,0.5);
}

// cubic root
ADFunc cbrt ( const ADFunc &obj){
  return pow(obj,1.0/3);
}

// the hypotenuse of a right-angled triangle whose legs are lhs and rhs
ADFunc hypot ( const ADFunc &lhs, const ADFunc &rhs) {
  checkName(lhs,rhs);
  return sqrt(pow(lhs,2.0)+pow(rhs,2.0));
}

/////////////////////////////////////////// LOG OPERATORS

// natural log, log_e(x)
ADFunc log(const ADFunc &obj){ 
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
    return ADFunc(val,grad);
}

// log_10(x)
ADFunc log10(const ADFunc &obj) {
    
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
    return ADFunc(val,grad);
}

// log_2(x)
ADFunc log2(const ADFunc &obj){
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
    return ADFunc(val,grad);
}

// log_e(1+x)
ADFunc log1p(const ADFunc &obj){
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
    return ADFunc(val,grad);
}

/////////////////////////////////////////// SETTERS

// set val
void ADFunc::setVal(double obj) {
  _val = obj;
}

// set dval with respect to a variable
void ADFunc::set_dval_wrt(int index, double dval) {
  if(index>=_num_vars) throw std::out_of_range("Index out of range!");
  _grad[index] = dval;
}

// set dvals with all the variables
void ADFunc::set_dval(std::vector<double> dvals){
  _grad = dvals; 
}

// set name of a variable
void ADFunc::setName(int index, std::string name){
  if(!_hasName) throw std::runtime_error("Name mode not initialized!");
  if(index>=_num_vars) throw std::out_of_range("Index out of range!");

  for(int i=0;i<_num_vars;i++){
    if(i!=index && _name_vec[i]==name){
      throw std::runtime_error("Name must be unique!");
    }
  }
  _name_vec[index] = name;

  std::unordered_map<std::string,int>::const_iterator got = _name_map.find(name);

  if ( got != _name_map.end() )
     _name_map.erase(name);

  _name_map.insert(std::make_pair(name,index));
}

// set name of all the variables
void ADFunc::setName(std::vector<std::string> var_names){
  if(_hasName && _name_vec.size()!=var_names.size()){
    throw std::range_error("Name vector dimension incompatible!");
  }
  // we allow not intialize name mode in this case, just
  // turn name mode to be ture and assign names to _name_vec and _name_map
  if(var_names.size()!=_num_vars){
    throw std::range_error("Name vector dimension incompatible!");
  }
  _name_vec = var_names;
  _hasName = true;
  _name_map.clear();

  std::unordered_map<std::string,int>::const_iterator got;

  for(int i=0;i<_num_vars;i++){
    got = _name_map.find(var_names[i]);
    if( got!= _name_map.end() ){
      throw std::runtime_error("Name must be unique!");
    }
    _name_map.insert(std::make_pair(var_names[i],i));
  }
}

// turn name mode on
void ADFunc::setName(){
  _hasName = true;
}

// turn name mode off
void ADFunc::clearName(){
  _hasName = false;
  _name_vec.clear();
  _name_map.clear();
}

/////////////////////////////////////////// GETTERS

// get total number of variables
int ADFunc::countVar() const{
  return _num_vars;
}

// get val
double ADFunc::val() const {
  return _val;
}

// get dval with respect to a variable
double ADFunc::dval_wrt(int index) const {
  if(index>=_num_vars) throw std::out_of_range("Index out of range!");
  return _grad[index];
}

// get dval with respect to a variable
double ADFunc::dval_wrt(std::string name) const {
  if(!_hasName) throw std::runtime_error("Name mode not initialized!");
  std::unordered_map<std::string,int>::const_iterator got = _name_map.find(name);
  if(got == _name_map.end()) throw std::runtime_error("Input variable name not found!");

  return _grad[got->second];
}

// get gradient (all the variables)
std::vector<double> ADFunc::gradient() const {
  std::vector<double> grad_copy = _grad;
  return grad_copy;
}

// get if variables have names, 
// e.g. represented by std::vector<std::string> {"x", "y","z"}
bool ADFunc::hasName() const {
  return _hasName;
}

// get names of all variables
std::vector<std::string> ADFunc::getName() const {
  std::vector<std::string> names = _name_vec;
  return names;
}

// get names of a variable at index of name vector
std::string ADFunc::getName(int index) const{
  if(index>=_num_vars) throw std::out_of_range("Index out of range!");
  if(!_hasName || _name_vec.size()==0) throw std::runtime_error("Name mode not initialized!");
  if(index>=_name_vec.size()) throw std::out_of_range("Index out of range!");
  return _name_vec[index];
}

/////////////////////////////////////////// PRINT VAL AND DER

std::ostream& operator<<(std::ostream& os, const ADFunc& obj){
    os << "Information of ADFunc object: \n";
    os << "Value at " << obj.val() << ". ";
    os << obj.countVar() << " variable(s) in total.\n";

    if(obj.hasName()){
      for(int i = 0; i < obj.countVar() ; i++){
        os << "   " << obj.getName(i) << "\'s dval = " << obj.gradient()[i] << std::endl;
      }
    } else {
      for(int i = 0; i < obj.countVar() ; i++){
        os << "   " << i << "th variable: dval = " << obj.gradient()[i] << std::endl;
      }
    }
     
    return os;
}

/////////////////////////////////////////// TRIGONOMETRIC FUNCTIONS

ADFunc sin(const ADFunc &obj){

    double val = sin( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( cos(obj.val()) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc cos(const ADFunc &obj){   
    
    double val = cos( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( -sin(obj.val()) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc tan(const ADFunc &obj){
    
    double val = tan( obj.val() );
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/pow(cos(obj.val()),2) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc asin(const ADFunc &obj){
    
    double val = asin(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/sqrt(1 - pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc acos(const ADFunc &obj){
    
    double val = acos(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( -1/sqrt(1 - pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc atan(const ADFunc &obj){
    
    double val = atan(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( 1/(1 + pow(obj.val(), 2)) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

/////////////////////////////////////////// HYPERBOLIC FUNCTIONS

ADFunc sinh(const ADFunc &obj){
    
    double val = sinh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( cosh(obj.val()) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc cosh(const ADFunc &obj){
    
    double val = cosh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( sinh(obj.val()) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc tanh(const ADFunc &obj){
    
    double val = tanh(obj.val());
    std::vector<double> grad;
    for(int i = 0; i < obj.countVar(); i++){
      grad.push_back( (1/pow(cosh(obj.val()), 2)) * obj.gradient()[i] );
    }
    return ADFunc(val,grad);
}

ADFunc asinh(const ADFunc &obj){
  double val = asinh(obj.val());
  std::vector<double> grad;

  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( 1/sqrt(obj.val()*obj.val()+1) * obj.gradient()[i] );
  }
  return ADFunc(val,grad);
}

ADFunc acosh(const ADFunc &obj){
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
  return ADFunc(val,grad);
}

ADFunc atanh(const ADFunc &obj){
  double val = atanh(obj.val());
  std::vector<double> grad;
  
  if (1-obj.val()*obj.val() == 0) {
    throw std::range_error("Denominator equals 0!");
  }
  for(int i = 0; i < obj.countVar(); i++){
    grad.push_back( 1/(1-obj.val()*obj.val()) * obj.gradient()[i] );
  }
  return ADFunc(val,grad);
}

// return true when
// case 1: lhs and rhs both not in name mode
// case 2: lhs and rhs both in name mode, and their variables'names are the same
// raise an error when 
//         lhs and rhs both in name mode, but have different names for some variables
bool checkName(const ADFunc &lhs, const ADFunc & rhs){
  std::string error_msg = "LHS and RHS objects'names not comptabile! Are you sure to use them together?";
  if(!lhs.hasName() && !rhs.hasName()) 
    return true;
  if(!lhs.hasName() || !rhs.hasName()) {
    std::cout << error_msg << std::endl;
    return false;
  }
  for(int i=0;i<lhs.countVar();i++){
    if(lhs.getName().at(i)!=rhs.getName().at(i)){
      throw std::runtime_error("LHS and RHS objects have different names!");
    }
  }
  return true;
}