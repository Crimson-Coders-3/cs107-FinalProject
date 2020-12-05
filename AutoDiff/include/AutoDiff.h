#ifndef AD_H
#define AD_H

#include <vector>
#include <iostream>

///////////////////////////////////////////////////////////////// CUSTOM AUTODIFF CLASS
class AutoDiff {

   /////////////////////////////////////////// CLASS DEF
   // private
   private:
      double _val;
      std::vector<double> _grad;
      int _num_vars;

   // public
   public:
      // constructor
      // seed vector example: for x in f(x,y), seed = [1, 0]
      //                      for y in f(x,y), seed = [0, 1]
      // seed vector does not need to be unit vector
      AutoDiff(double val, std::vector<double> seed);


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

   // get value
   double val() const;

   // get dval with respect to a variable
   double dval_wrt(int index) const;

   // get gradient (all the variables)
   std::vector<double> gradient() const;

   // get total number of variables
   int countVar() const;

   // set value
   void setVal(double val);

   // set dval with respect to a variable
   void set_dval_wrt(int index, double dval);

   // set dvals of all the variables
   void set_dval(std::vector<double> dvals);

}; // close AutoDiff class

/////////////////////////////////////////// PRINT value AND dvalue
std::ostream& operator<<(std::ostream& os, const AutoDiff& obj);

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
AutoDiff log(const AutoDiff &obj);
AutoDiff log10(const AutoDiff &obj);
AutoDiff exp ( const AutoDiff &obj );
AutoDiff sin(const AutoDiff &obj);
AutoDiff cos(const AutoDiff &obj);
AutoDiff tan(const AutoDiff &obj);
AutoDiff asin(const AutoDiff &obj);
AutoDiff acos(const AutoDiff &obj);
AutoDiff atan(const AutoDiff &obj);
AutoDiff sinh(const AutoDiff &obj);
AutoDiff cosh(const AutoDiff &obj);
AutoDiff tanh(const AutoDiff &obj);

#endif