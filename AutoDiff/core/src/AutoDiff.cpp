#include "AutoDiff.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

AutoDiff::AutoDiff(double a, double b) {
 std::cout << "constructor called and value set" << std::endl;
 std::cout << a << std::endl;

 std::cout << "constructor called and value set" << std::endl;
 std::cout << b << std::endl;
 
 val = a;
 der = b;
}

// overload +
AutoDiff AutoDiff::operator + ( AutoDiff &obj ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val + obj.val;
  c.der = der + obj.der;

  //std::cout << "first option" << std::endl;
  //this->print();
  //std::cout << "second option" << std::endl;
  //obj.print();

  return c;
}

AutoDiff AutoDiff::operator + ( double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val + a;
  c.der = der;

  return c;
}

// overload unary negation
AutoDiff AutoDiff::operator - () {
  AutoDiff a = AutoDiff(0.0);

  a.val = -val;
  a.der = -der;

  return a;
};

// overload -
AutoDiff AutoDiff::operator - ( AutoDiff &obj ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val - obj.val;
  c.der = der - obj.der;

  return c;
};

// overload *
AutoDiff AutoDiff::operator * ( AutoDiff &obj ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val * obj.val;
  c.der = der * obj.val + val * obj.der;

  return c;
};

// overload autodiff * constant
AutoDiff AutoDiff::operator * ( double con ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = con * val;
  c.der = con * der;

  return c;
}

// overload /
AutoDiff AutoDiff::operator / ( AutoDiff &obj ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val / obj.val;
  c.der = (der * obj.val - val * obj.der) / std::pow(obj.val, 2.0);

  return c;
};

// overload power (exponent)
AutoDiff AutoDiff::pow ( AutoDiff a, AutoDiff b ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(a.val, b.val);
  c.der = b.val * std::pow(a.val, b.val - 1) * a.der;

  return c;
};
/////////////////////////////////////////// VIEW PUBLIC VAL / DER VARS

// get val
double AutoDiff::getVal(){
  return val;
}

// get der
double AutoDiff::getDer(){
  return der;
}

/////////////////////////////////////////// PRINT VAL AND DER

void AutoDiff::print() { 
  std::cout << "print function called --- val: " << val << " " << "der: " << der << std::endl; 
} 

AutoDiff sin(AutoDiff input)
{
    
    double val = sin( (input.getVal()));
    double dv = cos(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff cos(AutoDiff input)
{   
    
    double val = cos(input.getVal());
    double dv = -sin(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff tan(AutoDiff input)
{
    
    double val = tan(input.getVal());
    double dv = (1/pow(cos(input.getVal()), 2)) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff arcsin(AutoDiff input)
{
    
    double val = asin(input.getVal());
    double dv = (1/sqrt(1 - pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff arccos(AutoDiff input)
{
    
    double val = acos(input.getVal());
    double dv = -(1/sqrt(1 - pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff arctan(AutoDiff input)
{
    
    double val = atan(input.getVal());
    double dv = (1/(1+pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff exp(AutoDiff input)
{
    
    double val = exp(input.getVal());
    double dv = exp(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff log(AutoDiff input)
{
    
    double val = log(input.getVal());
    double dv = (1/input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff pow(AutoDiff input, double exponent)
{
    
    double val = pow(input.getVal(), exponent);
    double dv = exponent * pow(input.getVal(), exponent - 1) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff sinh(AutoDiff input)
{
    
    double val = sinh(input.getVal());
    double dv = cosh(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff cosh(AutoDiff input)
{
    
    double val = cosh(input.getVal());
    double dv = sinh(input.getVal()) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff tanh(AutoDiff input)
{
    
    double val = tanh(input.getVal());
    double dv = (1/pow(cosh(input.getVal()), 2)) * input.getDer();
    return AutoDiff(val,dv);
}
