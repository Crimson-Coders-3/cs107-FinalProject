#include "AutoDiff.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

/////////////////////////////////////////// CONSTRUCTOR
AutoDiff::AutoDiff(double a, double b) {

  //std::cout << "constructor called and value set" << std::endl;
  //std::cout << a << std::endl;

  //std::cout << "constructor called and value set" << std::endl;
  //std::cout << b << std::endl;
  val = a;
  der = b;
}

/////////////////////////////////////////// OVERLOAD OPERATORS

/////////////////////// +
// overload AutoDiff += AutoDiff
AutoDiff AutoDiff::operator += (const AutoDiff &obj) {
  val += obj.getVal();
  der += obj.getDer();
  return *this;
};

// overload AutoDiff += double
AutoDiff AutoDiff::operator += ( double obj ) {
  val += obj;
  return *this;
};

// overload double + AutoDiff
AutoDiff operator + (double lhs, const AutoDiff &rhs) {
    return AutoDiff(lhs+rhs.getVal(),rhs.getDer());
}

// overload AutoDiff + AutoDiff
AutoDiff operator + ( const AutoDiff &a, const AutoDiff &b )
{
    return AutoDiff(a.getVal()+b.getVal(),a.getDer()+b.getDer());
}

// overload AutoDiff + double
AutoDiff operator + ( const AutoDiff &lhs, double rhs )
{
    return AutoDiff(lhs.getVal()+rhs, lhs.getDer());
}

/////////////////////// NEGATION
// overload unary negation (- AutoDiff)
AutoDiff operator -(const AutoDiff &obj) {
  return AutoDiff(-obj.getVal(),-obj.getDer());
};

// overload AutoDiff -= double
AutoDiff AutoDiff::operator -= ( double obj ) {
  val -= obj;
  return *this;
};

// overload AutoDiff -= AutoDiff
AutoDiff AutoDiff::operator -= (const AutoDiff &obj) {
  val -= obj.getVal();
  der -= obj.getDer();
    return *this;
}

/////////////////////// -
// overload AutoDiff - AutoDiff
AutoDiff operator - ( const AutoDiff &lhs, const AutoDiff &rhs ) {
  return AutoDiff(lhs.getVal()-rhs.getVal(),lhs.getDer()-rhs.getDer());
};

// overload AutoDiff - double
AutoDiff operator - ( const AutoDiff &lhs, double rhs ) {
  return AutoDiff(lhs.getVal()-rhs,lhs.getDer());
};

// overload double - AutoDiff
AutoDiff operator - (double lhs, const AutoDiff &rhs) {
    return - rhs + lhs;
}


/////////////////////// *
// overload AutoDiff *= AutoDiff
AutoDiff AutoDiff::operator *= ( const AutoDiff &obj) {

  double val = val * obj.getVal();
  double der = der * obj.getVal() + val * obj.getDer();
  val = val;
  der = der;

  return *this;
};

// overload AutoDiff *= double
AutoDiff AutoDiff::operator *= ( double obj ) {
  val *= obj;
  der *= obj;
  return *this;
};

// overload AutoDiff * AutoDiff
AutoDiff operator * ( const AutoDiff &lhs, const AutoDiff &rhs ) {

  double val = lhs.getVal() * rhs.getVal();
  double der = lhs.getDer() * rhs.getVal() + lhs.getVal() * rhs.getDer();

  return AutoDiff(val, der);
};

// overload AutoDiff * double
AutoDiff operator * (const AutoDiff &lhs, double rhs ) {
  return AutoDiff(lhs.getVal()*rhs,lhs.getDer()*rhs);
};

// overload double * AutoDiff
AutoDiff operator * (double lhs, const AutoDiff &rhs) {
    return rhs * lhs;
}


/////////////////////// /

// overload AutoDiff /= AutoDiff
AutoDiff AutoDiff::operator /= ( const AutoDiff &obj) {

  val = val / obj.getVal();
  der = (der * obj.getVal() - val * obj.getDer()) / (val*val);

  return *this;
};

// overload AutoDiff /= double
AutoDiff AutoDiff::operator /= ( double obj ) {
  val = val / obj;

  return *this;
};

// overload AutoDiff / AutoDiff
AutoDiff operator / ( const AutoDiff &lhs, const AutoDiff &rhs) {
  return AutoDiff(lhs.getVal()/rhs.getVal(), (lhs.getDer()*rhs.getVal()-\
    lhs.getVal()*rhs.getDer())/(rhs.getVal()*rhs.getVal()) );
};

// overload AutoDiff / double
AutoDiff operator / ( const AutoDiff &lhs, double rhs ) {
  return AutoDiff(lhs.getVal()/rhs, lhs.getDer()/rhs);
};

// overload double / AutoDiff
AutoDiff operator / (double lhs, const AutoDiff &rhs) {
    return AutoDiff(lhs/rhs.getVal(), (-1)*(1/(rhs.getVal()*rhs.getVal()))*lhs*rhs.getDer());
}


/////////////////////// pow
// AutoDiff ^ AutoDiff
AutoDiff pow ( const AutoDiff &lhs, const AutoDiff &rhs ) {

  double val = std::pow(lhs.getVal(), rhs.getVal());
  double der = std::pow(lhs.getVal(), rhs.getVal()) * rhs.getDer() * log(lhs.getVal())\
    + std::pow(lhs.getVal(), rhs.getVal() - 1) * rhs.getVal() * lhs.getDer();

  return AutoDiff(val,der);
};

// AutoDiff ^ double
AutoDiff pow ( AutoDiff &obj, double a ) {

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
};



/////////////////////////////////////////// VIEW PUBLIC VAL / DER VARS

// get val
double AutoDiff::getVal() const {
  return val;
}

// get der
double AutoDiff::getDer() const {
  return der;
}



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
}