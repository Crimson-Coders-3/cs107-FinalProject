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
// overload autodiff + autodiff
AutoDiff AutoDiff::operator += (const AutoDiff &obj) {
  val += obj.getVal();
  der += obj.getDer();
  return *this;
};

// overload autodiff + double
AutoDiff AutoDiff::operator += ( double a ) {
  val += a;
  return *this;
};

// overload double + AutoDiff
AutoDiff operator + (double lhs, const AutoDiff &rhs) {
    return AutoDiff(lhs+rhs.getVal(),rhs.getDer());
}


/////////////////////// NEGATION
// overload unary negation (- autodiff)
AutoDiff AutoDiff::operator - () {
  AutoDiff a = AutoDiff(0.0);

  a.val = -val;
  a.der = -der;

  return a;
};


/////////////////////// -
// overload autodiff - autodiff
AutoDiff AutoDiff::operator - ( const AutoDiff &obj) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val - obj.getVal();
  c.der = der - obj.getDer();

  return c;
};

// overload autodiff - double
AutoDiff AutoDiff::operator - ( double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val - a;
  c.der = der;

  return c;
};

// overload double - AutoDiff
AutoDiff operator - (double lhs, const AutoDiff &rhs) {
    return - rhs + lhs;
}


/////////////////////// *
// overload autodiff * autodiff
AutoDiff AutoDiff::operator * ( const AutoDiff &obj) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val * obj.val;
  c.der = der * obj.val + val * obj.der;

  return c;
};

// overload autodiff * double
AutoDiff AutoDiff::operator * ( double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val * a;
  c.der = der * a;

  return c;
};

// overload double * AutoDiff
AutoDiff operator * (double lhs, const AutoDiff &rhs) {
    return rhs * lhs;
}


/////////////////////// /
// overload autodiff / autodiff
AutoDiff AutoDiff::operator / ( const AutoDiff &obj) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val / obj.val;
  c.der = (der * obj.val - val * obj.der) / std::pow(obj.val, 2.0);

  return c;
};

// overload autodiff / double
AutoDiff AutoDiff::operator / ( double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val / a;
  c.der = der / a;

  return c;
};

// overload double / AutoDiff
AutoDiff operator / (double lhs, const AutoDiff &rhs) {
    return pow(rhs, -1.0) * lhs;
}


/////////////////////// pow
// autodiff ^ autodiff
AutoDiff pow ( AutoDiff &a, const AutoDiff &b ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(a.val, b.val);
  c.der = std::pow(a.val, b.val) * b.der * log(a.val) + std::pow(a.val, b.val - 1) * b.val * a.der;

  return c;
};

// autodiff ^ double
AutoDiff pow ( AutoDiff &obj, double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(obj.val, a);
  c.der = a * std::pow(obj.val, a - 1) * obj.der;

  return c;
};

// double ^ autodiff
AutoDiff pow (double lhs, const AutoDiff &rhs) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(2, rhs.val);
  c.der = log(lhs) * rhs.der * std::pow(2, rhs.val);

  return c;
};


/////////////////////// exp
// e ^ autodiff
AutoDiff exp ( AutoDiff &a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = exp(a.val);
  c.der = exp(a.val) * a.der;

  return c;
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