#ifndef DUAL_H
#define DUAL_H

/* system header files */
#include <iostream>
#ifndef DOXYGEN_IGNORE
#  include <stdio.h>
#endif

using namespace std;

class Dual{

    public:
        
        /* constructors */
        Dual();
        Dual(double real);
        Dual(double real, double dual);
        Dual(const Dual& rhs);
        
        /* getters */
        double real() const;
        double dual() const;
  
        Dual& operator=(double rhs);
        Dual& operator+=(double rhs); 
        Dual& operator-=(double rhs);  
        Dual& operator*=(double rhs); 
        Dual& operator/=(double rhs);
        
        Dual& operator=(const Dual& rhs);
        Dual& operator+=(const Dual& rhs);
        Dual& operator-=(const Dual& rhs); 
        Dual& operator*=(const Dual& rhs);
        Dual& operator/=(const Dual& rhs);

    private:
        double adReal;
        double adDual;
    };

    
    ostream& operator<<(ostream& os, const Dual& rhs);
    
    bool operator==(const Dual& a, double b);
    bool operator==(double a, const Dual& b);
    bool operator==(const Dual& a, const Dual& b);

    bool operator!=(const Dual& a, double b);
    bool operator!=(double a, const Dual& b);
    bool operator!=(const Dual& a, const Dual& b);
  
    bool operator<(const Dual& a, double b);
    bool operator<(double a, const Dual& b);
    bool operator<(const Dual& a, const Dual& b);

    bool operator<=(const Dual& a, double b);
    bool operator<=(double a, const Dual& b);
    bool operator<=(const Dual& a, const Dual& b);

    bool operator>(const Dual& a, double b);
    bool operator>(double a, const Dual& b);
    bool operator>(const Dual& a, const Dual& b);

    bool operator>=(const Dual& a, double b);
    bool operator>=(double a, const Dual& b);
    bool operator>=(const Dual& a, const Dual& b);
  
    // negate sign
    Dual operator-(const Dual& rhs);
    
    Dual operator+(const Dual& lhs, double rhs);
    Dual operator-(const Dual& lhs, double rhs);
    Dual operator*(const Dual& lhs, double rhs);
    Dual operator/(const Dual& lhs, double rhs);

    Dual operator-(double lhs, const Dual& rhs);
    Dual operator+(double lhs, const Dual& rhs);
    Dual operator*(double lhs, const Dual& rhs);
    Dual operator/(double lhs, const Dual& rhs);

    // can only allow Dual<int> + Dual<int>, Dual<float> + Dual<float>, Dual + Dual
    // to do: Dual<int> + Dual ...
    Dual operator-(const Dual& a, const Dual& b);
    Dual operator+(const Dual& a, const Dual& b);
    Dual operator*(const Dual& a, const Dual& b);
    Dual operator/(const Dual& a, const Dual& b);

    // math operators
    Dual acos(const Dual& z);
    Dual asin(const Dual& z);
    Dual atan(const Dual& z);
    Dual cos(const Dual& z);
    Dual cosh(const Dual& z);
    Dual exp(const Dual& z);
    Dual log(const Dual& z);
    Dual log10(const Dual& z);
    Dual pow(const Dual& x, const Dual& y);
    Dual sin(const Dual& z);
    Dual sinh(const Dual& z);
    Dual sqrt(const Dual& z);
    Dual tan(const Dual& z);
    Dual tanh(const Dual& z);
    
#endif