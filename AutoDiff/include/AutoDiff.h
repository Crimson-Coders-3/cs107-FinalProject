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
   // overload autodiff + autodiff
   AutoDiff operator + ( AutoDiff obj );

   // overload autodiff + double
   AutoDiff operator + ( double a );

   // overload unary negation
   AutoDiff operator - ();

   // overload autodiff - autodiff
   AutoDiff operator - ( AutoDiff obj );

   // overload autodiff - double
   AutoDiff operator - ( double a );

   // overload autodiff * autodiff
   AutoDiff operator * ( AutoDiff obj );

   // overload autodiff * double
   AutoDiff operator * ( double a );

   // overload autodiff / autodiff
   AutoDiff operator / ( AutoDiff obj );

   // overload autodiff / double
   AutoDiff operator / ( double a );

   double getVal();
   double getDer();

   /////////////////////////////////////////// PRINT VAL AND DER
   void print();

}; // close AutoDiff class

AutoDiff operator + (double lhs, AutoDiff rhs);
AutoDiff operator - (double lhs, AutoDiff rhs);
AutoDiff operator * (double lhs, AutoDiff rhs);
AutoDiff operator / (double lhs, AutoDiff rhs);
AutoDiff pow ( AutoDiff a, AutoDiff b );
AutoDiff pow ( AutoDiff obj, double a );
AutoDiff pow (double lhs, AutoDiff rhs);
AutoDiff exp ( AutoDiff a );
AutoDiff sin(AutoDiff input);
AutoDiff cos(AutoDiff input);
AutoDiff tan(AutoDiff input);
AutoDiff asin(AutoDiff input);
AutoDiff acos(AutoDiff input);
AutoDiff atan(AutoDiff input);
AutoDiff log(AutoDiff input);
AutoDiff sinh(AutoDiff input);
AutoDiff cosh(AutoDiff input);
AutoDiff tanh(AutoDiff input);

// overload AutoDiffToy * float
//AutoDiff operator * (float lhs, AutoDiff rhs);
#endif
