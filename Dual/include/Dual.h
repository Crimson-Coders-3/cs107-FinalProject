#ifndef DUAL_H
#define DUAL_H

/* system header files */
#include <iostream>
#ifndef DOXYGEN_IGNORE
#  include <stdio.h>
#endif

using namespace std;

template <typename double>
class Dual{

    public:
        
        /* constructors */
        Dual();
        Dual(double real);
        Dual(double real, double dual);
        Dual(const Dual<double>& rhs);
        
        /* getters */
        double real() const;
        double dual() const;
  
        Dual<double>& operator=(double rhs);
        Dual<double>& operator+=(double rhs); 
        Dual<double>& operator-=(double rhs);  
        Dual<double>& operator*=(double rhs); 
        Dual<double>& operator/=(double rhs);
        
        Dual<double>& operator=(const Dual<double>& rhs);
        Dual<double>& operator+=(const Dual<double>& rhs);
        Dual<double>& operator-=(const Dual<double>& rhs); 
        Dual<double>& operator*=(const Dual<double>& rhs);
        Dual<double>& operator/=(const Dual<double>& rhs);

    private:
        double adReal;
        double adDual;
    };

    
    ostream& operator<<(ostream& os, const Dual<double>& rhs);
    
    bool operator==(const Dual<double>& a, double b);
    bool operator==(double a, const Dual<double>& b);
    bool operator==(const Dual<double>& a, const Dual<double>& b);

    bool operator!=(const Dual<double>& a, double b);
    bool operator!=(double a, const Dual<double>& b);
    bool operator!=(const Dual<double>& a, const Dual<double>& b);
  
    bool operator<(const Dual<double>& a, double b);
    bool operator<(double a, const Dual<double>& b);
    bool operator<(const Dual<double>& a, const Dual<double>& b);

    bool operator<=(const Dual<double>& a, double b);
    bool operator<=(double a, const Dual<double>& b);
    bool operator<=(const Dual<double>& a, const Dual<double>& b);

    bool operator>(const Dual<double>& a, double b);
    bool operator>(double a, const Dual<double>& b);
    bool operator>(const Dual<double>& a, const Dual<double>& b);

    bool operator>=(const Dual<double>& a, double b);
    bool operator>=(double a, const Dual<double>& b);
    bool operator>=(const Dual<double>& a, const Dual<double>& b);
  
    // negate sign
    Dual<double> operator-(const Dual<double>& rhs);
    
    Dual<double> operator+(const Dual<double>& lhs, double rhs);
    Dual<double> operator-(const Dual<double>& lhs, double rhs);
    Dual<double> operator*(const Dual<double>& lhs, double rhs);
    Dual<double> operator/(const Dual<double>& lhs, double rhs);

    Dual<double> operator-(double lhs, const Dual<double>& rhs);
    Dual<double> operator+(double lhs, const Dual<double>& rhs);
    Dual<double> operator*(double lhs, const Dual<double>& rhs);
    Dual<double> operator/(double lhs, const Dual<double>& rhs);

    // can only allow Dual<int> + Dual<int>, Dual<float> + Dual<float>, Dual<double> + Dual<double>
    // to do: Dual<int> + Dual<double> ...
    Dual<double> operator-(const Dual<double>& a, const Dual<double>& b);
    Dual<double> operator+(const Dual<double>& a, const Dual<double>& b);
    Dual<double> operator*(const Dual<double>& a, const Dual<double>& b);
    Dual<double> operator/(const Dual<double>& a, const Dual<double>& b);

    // math operators
    Dual<double> acos(const Dual<double>& z);
    Dual<double> asin(const Dual<double>& z);
    Dual<double> atan(const Dual<double>& z);
    Dual<double> atan2(const Dual<double>& y, const Dual<double>& x);
    Dual<double> cos(const Dual<double>& z);
    Dual<double> cosh(const Dual<double>& z);
    Dual<double> exp(const Dual<double>& z);
    Dual<double> log(const Dual<double>& z);
    Dual<double> log10(const Dual<double>& z);
    Dual<double> pow(const Dual<double>& x, const Dual<double>& y);
    Dual<double> sin(const Dual<double>& z);
    Dual<double> sinh(const Dual<double>& z);
    Dual<double> sqrt(const Dual<double>& z);
    Dual<double> tan(const Dual<double>& z);
    Dual<double> tanh(const Dual<double>& z);
    
#endif