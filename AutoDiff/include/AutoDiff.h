#ifndef AD_H
#define AD_H

///////////////////////////////////////////////////////////////// CUSTOM AUTODIFF CLASS
class AutoDiff {

   /////////////////////////////////////////// CLASS DEF
   // private
   private:
      double val;
      double der;
      bool multivar;

   // public
   public:
      // constructor
      // seed is 1.0 (scales dvalueivative)
      AutoDiff(double a, double b = 1.0);


   /////////////////////////////////////////// OVERLOAD OPERATORS
   // overload autodiff + autodiff
   AutoDiff operator += ( const AutoDiff &obj );

   // overload autodiff + double
   AutoDiff operator += ( double obj );

   // overload autodiff - autodiff
   AutoDiff operator -= ( const AutoDiff &obj );

   // overload autodiff - double
   AutoDiff operator -= ( double obj );

   // overload autodiff * autodiff
   AutoDiff operator *= ( const AutoDiff &obj );

   // overload autodiff * double
   AutoDiff operator *= ( double obj );

   // overload autodiff / autodiff
   AutoDiff operator /= ( const AutoDiff &obj );

   // overload autodiff / double
   AutoDiff operator /= ( double obj );

   double getVal() const;
   double getDer() const;
   void setVal(double obj);
   void setDer(double obj);

   /////////////////////////////////////////// PRINT value AND dvalue
   void print();
}; // close AutoDiff class

AutoDiff operator + ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator + ( const AutoDiff &lhs, double rhs );
AutoDiff operator + ( double lhs, const AutoDiff &rhs);
AutoDiff operator - ( const AutoDiff &obj);
AutoDiff operator - ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator - ( const AutoDiff &lhs, double rhs );
AutoDiff operator - ( double lhs, const AutoDiff &rhs);
AutoDiff operator * ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator * ( const AutoDiff &lhs, double rhs );
AutoDiff operator * ( double lhs, const AutoDiff &rhs);
AutoDiff operator / ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff operator / ( const AutoDiff &lhs, double rhs );
AutoDiff operator / ( double lhs, const AutoDiff &rhs);

AutoDiff pow ( const AutoDiff &lhs, const AutoDiff &rhs );
AutoDiff pow ( const AutoDiff &lhs, double rhs );
AutoDiff pow ( double lhs, const AutoDiff &rhs);
AutoDiff exp ( const AutoDiff &obj );
AutoDiff sin(const AutoDiff &obj);
AutoDiff cos(const AutoDiff &obj);
AutoDiff tan(const AutoDiff &obj);
AutoDiff asin(const AutoDiff &obj);
AutoDiff acos(const AutoDiff &obj);
AutoDiff atan(const AutoDiff &obj);
AutoDiff log(const AutoDiff &obj);
AutoDiff sinh(const AutoDiff &obj);
AutoDiff cosh(const AutoDiff &obj);
AutoDiff tanh(const AutoDiff &obj);

#endif