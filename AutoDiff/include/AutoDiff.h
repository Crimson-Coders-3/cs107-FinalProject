#ifndef AD_H
#define AD_H

///////////////////////////////////////////////////////////////// CUSTOM AUTODIFF CLASS
class AutoDiff {

   /////////////////////////////////////////// CLASS DEF
   // public
   public:
      double val;
      double der;
      // constructor
      // seed is 1.0 (scales derivative)
      AutoDiff(double a, double b = 1.0);


   /////////////////////////////////////////// OVERLOAD OPERATORS
   // overload +
   AutoDiff operator + ( AutoDiff &obj );

   // overload autodiff + constant
   AutoDiff operator + ( double a );

   // overload unary negation
   AutoDiff operator - ();

   // overload -
   AutoDiff operator - ( AutoDiff &obj );

   // overload *
   AutoDiff operator * ( AutoDiff &obj );
  
   // overload autodiff * constant
   AutoDiff operator * ( double con );

   // overload /
   AutoDiff operator / ( AutoDiff &obj );

   // overload power (exponent)
   AutoDiff pow ( AutoDiff a, AutoDiff b );

   double getVal();
   double getDer();

   /////////////////////////////////////////// PRINT VAL AND DER
   void print();

}; // close AutoDiff class


AutoDiff sin(AutoDiff input);
AutoDiff cos(AutoDiff input);
AutoDiff tan(AutoDiff input);
AutoDiff arcsin(AutoDiff input);
AutoDiff arccos(AutoDiff input);
AutoDiff arctan(AutoDiff input);
AutoDiff exp(AutoDiff input);
AutoDiff log(AutoDiff input);
AutoDiff pow(AutoDiff input, double exponent);
AutoDiff sinh(AutoDiff input);
AutoDiff cosh(AutoDiff input);
AutoDiff tanh(AutoDiff input);

// overload AutoDiffToy * float
//AutoDiff operator * (float lhs, AutoDiff rhs);
#endif
