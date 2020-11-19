#ifndef DUAL_H
#define DUAL_H

/* system header files */
#include <iostream>
#ifndef DOXYGEN_IGNORE
#  include <stdio.h>
#endif

using namespace std;

template <typename Scalar>
class Dual{

    public:
        
        /* constructors */
        Dual();
        Dual(Scalar real);
        Dual(Scalar real, Scalar dual);
        template <typename Scalar2> Dual(const Dual<Scalar2>& rhs);
        
        /* getters */
        Scalar real() const;
        Scalar dual() const;
  
        Dual<Scalar>& operator=(Scalar rhs);
        Dual<Scalar>& operator+=(Scalar rhs); 
        Dual<Scalar>& operator-=(Scalar rhs);  
        Dual<Scalar>& operator*=(Scalar rhs); 
        Dual<Scalar>& operator/=(Scalar rhs);
        
        template <typename Scalar2> Dual<Scalar>& operator=(const Dual<Scalar2>& rhs);
        template <typename Scalar2> Dual<Scalar>& operator+=(const Dual<Scalar2>& rhs);
        template <typename Scalar2> Dual<Scalar>& operator-=(const Dual<Scalar2>& rhs); 
        template <typename Scalar2> Dual<Scalar>& operator*=(const Dual<Scalar2>& rhs);
        template <typename Scalar2> Dual<Scalar>& operator/=(const Dual<Scalar2>& rhs);

    private:
        Scalar adReal;
        Scalar adDual;
    };

    template <typename Scalar> 
    ostream& operator<<(ostream& os, const Dual<Scalar>& rhs);
    
    template <typename Scalar> bool operator==(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator==(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator==(const Dual<Scalar1>& a, const Dual<Scalar2>& b);

    template <typename Scalar> bool operator!=(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator!=(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator!=(const Dual<Scalar1>& a, const Dual<Scalar2>& b);
  
    template <typename Scalar> bool operator<(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator<(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator<(const Dual<Scalar1>& a, const Dual<Scalar2>& b);

    template <typename Scalar> bool operator<=(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator<=(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator<=(const Dual<Scalar1>& a, const Dual<Scalar2>& b);

    template <typename Scalar> bool operator>(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator>(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator>(const Dual<Scalar1>& a, const Dual<Scalar2>& b);

    template <typename Scalar> bool operator>=(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator>=(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator>=(const Dual<Scalar1>& a, const Dual<Scalar2>& b);
  
    // negative sign
    template <typename Scalar> Dual<Scalar> operator-(const Dual<Scalar>& rhs);
    
    template <typename Scalar> Dual<Scalar> operator+(const Dual<Scalar>& lhs, Scalar rhs);
    template <typename Scalar> Dual<Scalar> operator-(const Dual<Scalar>& lhs, Scalar rhs);
    template <typename Scalar> Dual<Scalar> operator*(const Dual<Scalar>& lhs, Scalar rhs);
    template <typename Scalar> Dual<Scalar> operator/(const Dual<Scalar>& lhs, Scalar rhs);

    template <typename Scalar> Dual<Scalar> operator-(Scalar lhs, const Dual<Scalar>& rhs);
    template <typename Scalar> Dual<Scalar> operator+(Scalar lhs, const Dual<Scalar>& rhs);
    template <typename Scalar> Dual<Scalar> operator*(Scalar lhs, const Dual<Scalar>& rhs);
    template <typename Scalar> Dual<Scalar> operator/(Scalar lhs, const Dual<Scalar>& rhs);

    // can only allow Dual<int> + Dual<int>, Dual<float> + Dual<float>, Dual<double> + Dual<double>
    // to do: Dual<int> + Dual<double> ...
    template <typename Scalar> Dual<Scalar> operator-(const Dual<Scalar>& a, const Dual<Scalar>& b);
    template <typename Scalar> Dual<Scalar> operator+(const Dual<Scalar>& a, const Dual<Scalar>& b);
    template <typename Scalar> Dual<Scalar> operator*(const Dual<Scalar>& a, const Dual<Scalar>& b);
    template <typename Scalar> Dual<Scalar> operator/(const Dual<Scalar>& a, const Dual<Scalar>& b);

    // math operators
    template <typename Scalar> Dual<Scalar> acos(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> asin(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> atan(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> atan2(const Dual<Scalar>& y, const Dual<Scalar>& x);
    template <typename Scalar> Dual<Scalar> cos(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> cosh(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> exp(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> log(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> log10(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> pow(const Dual<Scalar>& x, Scalar y);
    template <typename Scalar> Dual<Scalar> sin(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> sinh(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> sqrt(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> tan(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> tanh(const Dual<Scalar>& z);
    
#endif