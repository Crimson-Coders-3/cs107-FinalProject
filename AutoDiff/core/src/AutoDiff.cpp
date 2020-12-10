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
AutoDiff AutoDiff::operator + ( AutoDiff obj ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val + obj.val;
  c.der = der + obj.der;

  return c;
};

// overload autodiff + double
AutoDiff AutoDiff::operator + ( double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val + a;
  c.der = der;

  return c;
};

// overload double + AutoDiff
AutoDiff operator + (double lhs, AutoDiff rhs) {
    return rhs + lhs;
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
AutoDiff AutoDiff::operator - ( AutoDiff obj ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = val - obj.val;
  c.der = der - obj.der;

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
AutoDiff operator - (double lhs, AutoDiff rhs) {
    return - rhs + lhs;
}


/////////////////////// *
// overload autodiff * autodiff
AutoDiff AutoDiff::operator * ( AutoDiff obj ) {
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
AutoDiff operator * (double lhs, AutoDiff rhs) {
    return rhs * lhs;
}


/////////////////////// /
// overload autodiff / autodiff
AutoDiff AutoDiff::operator / ( AutoDiff obj ) {
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
AutoDiff operator / (double lhs, AutoDiff rhs) {
    return pow(rhs, -1.0) * lhs;
}


/////////////////////// pow
// autodiff ^ autodiff
AutoDiff pow ( AutoDiff a, AutoDiff b ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(a.val, b.val);
  c.der = std::pow(a.val, b.val) * b.der * log(a.val) + std::pow(a.val, b.val - 1) * b.val * a.der;

  return c;
};

// autodiff ^ double
AutoDiff pow ( AutoDiff obj, double a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(obj.val, a);
  c.der = a * std::pow(obj.val, a - 1) * obj.der;

  return c;
};

// double ^ autodiff
AutoDiff pow (double lhs, AutoDiff rhs) {
  AutoDiff c = AutoDiff(0.0);

  c.val = std::pow(2, rhs.val);
  c.der = log(lhs) * rhs.der * std::pow(2, rhs.val);

  return c;
};


/////////////////////// exp
// e ^ autodiff
AutoDiff exp ( AutoDiff a ) {
  AutoDiff c = AutoDiff(0.0);

  c.val = exp(a.val);
  c.der = exp(a.val) * a.der;

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

AutoDiff asin(AutoDiff input)
{
    
    double val = asin(input.getVal());
    double dv = (1/sqrt(1 - pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff acos(AutoDiff input)
{
    
    double val = acos(input.getVal());
    double dv = -(1/sqrt(1 - pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff atan(AutoDiff input)
{
    
    double val = atan(input.getVal());
    double dv = (1/(1+pow(input.getVal(), 2))) * input.getDer();
    return AutoDiff(val,dv);
}

AutoDiff log(AutoDiff input)
{
    
    double val = log(input.getVal());
    double dv = (1/input.getVal()) * input.getDer();
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

int main() {

  /*
  AutoDiff test = AutoDiff(2.0);
  AutoDiff output = pow(test, 3.0);
  output.print();

  AutoDiff test2 = AutoDiff(2.0);
  AutoDiff output2 = sin(output);
  output2.print();

  AutoDiff test3 = AutoDiff(2.0);
  AutoDiff output3 = exp(output);
  output2.print();

  // each of these is a "variable"
  AutoDiff a1 = AutoDiff(2.0); 
  AutoDiff a2 = AutoDiff(0.5);

  std::cout << "a1" << std::endl;
  a1.print();
  std::cout << "a2" << std::endl;
  a2.print();

  AutoDiff a5 = a1.operator+(a2);

  AutoDiff a3 = a1 + a2;

  std::cout << "a3" << std::endl;
  a3.print();

  std::cout << typeid(a3).name() << std::endl;

  AutoDiff a4 = sin(a3);
  std::cout << "a4" << std::endl;
  a4.print();

  AutoDiff a6 = a4 + 2.0;

  //std::cout << "a4" << std::endl;
  //a4.print();*/

  return 0;
}
