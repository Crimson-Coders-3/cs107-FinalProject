#ifndef AD_H
#define AD_H

///////////////////////////////////////////////////////////////// CUSTOM AUTODIFF CLASS
class AutoDiff {

   /////////////////////////////////////////// CLASS DEF
   // private
   private:
      double val;
      double der;

   // public
   public:
      // constructor
      // seed is 1.0 (scales dvalueivative)
      AutoDiff(double a, double b = 1.0);


   /////////////////////////////////////////// OVERLOAD OPERATORS
   // overload autodiff + autodiff
   AutoDiff operator += ( const AutoDiff &obj );

   // overload autodiff + double
   AutoDiff operator += ( double a );

   // overload unary negation
   AutoDiff operator -= ();

   // overload autodiff - autodiff
   AutoDiff operator -= ( const AutoDiff &obj );

   // overload autodiff - double
   AutoDiff operator -= ( double a );

   // overload autodiff * autodiff
   AutoDiff operator *= ( const AutoDiff &obj );

   // overload autodiff * double
   AutoDiff operator *= ( double a );

   // overload autodiff / autodiff
   AutoDiff operator /= ( const AutoDiff &obj );

   // overload autodiff / double
   AutoDiff operator /= ( double a );

   double getVal() const;
   double getDer() const;

   /////////////////////////////////////////// PRINT value AND dvalue
   void print();
}; // close AutoDiff class

AutoDiff operator + ( const AutoDiff &obj );
AutoDiff operator + ( double a );
AutoDiff operator - ();
AutoDiff operator - ( const AutoDiff &obj );
AutoDiff operator - ( double a );
AutoDiff operator * ( const AutoDiff &obj );
AutoDiff operator * ( double a );
AutoDiff operator / ( const AutoDiff &obj );
AutoDiff operator / ( double a );
AutoDiff operator + (double lhs, const AutoDiff &rhs);
AutoDiff operator - (double lhs, const AutoDiff &rhs);
AutoDiff operator * (double lhs, const AutoDiff &rhs);
AutoDiff operator / (double lhs, const AutoDiff &rhs);
AutoDiff pow ( const AutoDiff &a, const AutoDiff &b );
AutoDiff pow ( const AutoDiff &obj, double a );
AutoDiff pow (double lhs, const AutoDiff &rhs);
AutoDiff exp ( const AutoDiff &a );
AutoDiff sin(const AutoDiff &input);
AutoDiff cos(const AutoDiff &input);
AutoDiff tan(const AutoDiff &input);
AutoDiff asin(const AutoDiff &input);
AutoDiff acos(const AutoDiff &input);
AutoDiff atan(const AutoDiff &input);
AutoDiff log(const AutoDiff &input);
AutoDiff sinh(const AutoDiff &input);
AutoDiff cosh(const AutoDiff &input);
AutoDiff tanh(const AutoDiff &input);

// overload AutoDiffToy * float
//AutoDiff operator * (float lhs, AutoDiff rhs);
#endif