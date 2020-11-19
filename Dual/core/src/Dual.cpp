#include "Dual.h"
#include <math.h>

#define PI 3.141592653589793238

template <typename Scalar>
Dual<Scalar>::Dual(){
    this->adReal = 0;
    this->adDual = 1;
}

template <typename Scalar>
Dual<Scalar>::Dual(Scalar real){
    this->adReal = real;
    this->adDual = 1;
}

template <typename Scalar>
Dual<Scalar>::Dual(Scalar real, Scalar dual)
    : adReal(real)
    , adDual(dual)
{}

template <typename Scalar>
template <typename Scalar2>
Dual<Scalar>::Dual(const Dual<Scalar2>& rhs)
    : adReal(rhs.real())
    , adDual(rhs.dual())
{}

template <typename Scalar>
Scalar Dual<Scalar>::real() const {
    return adReal;
}

template <typename Scalar>
Scalar Dual<Scalar>::dual() const {
    return adDual;
}

template <typename Scalar>
Dual<Scalar>& Dual<Scalar>::operator=(Scalar rhs){
    this->adReal = rhs; 
    this->adDual = 0; 
    return *this;
}

template <typename Scalar>
Dual<Scalar>& Dual<Scalar>::operator+=(Scalar rhs){
    this->adReal += rhs; 
    return *this;
}

template <typename Scalar>
Dual<Scalar>& Dual<Scalar>::operator-=(Scalar rhs){
    this->adReal -= rhs; 
    return *this;
} 

template <typename Scalar>
Dual<Scalar>& Dual<Scalar>::operator*=(Scalar rhs){
    this->adReal *= rhs;
    this->adDual *= rhs;
    return *this;
} 

template <typename Scalar>
Dual<Scalar>& Dual<Scalar>::operator/=(Scalar rhs){
    this->adReal /= rhs;
    this->adDual /= rhs;
    return *this;
}

template <typename Scalar>
template <typename Scalar2>
Dual<Scalar>& Dual<Scalar>::operator=(const Dual<Scalar2>& rhs){
    this->adReal = rhs.real(); 
    this->adDual = rhs.dual(); 
    return *this;
}

template <typename Scalar>
template <typename Scalar2>
Dual<Scalar>& Dual<Scalar>::operator+=(const Dual<Scalar2>& rhs){
    this->adReal += rhs.real(); 
    this->adDual += rhs.dual(); 
    return *this;
}  

template <typename Scalar>
template <typename Scalar2>
Dual<Scalar>& Dual<Scalar>::operator-=(const Dual<Scalar2>& rhs){
    this->adReal -= rhs.real(); 
    this->adDual -= rhs.dual(); 
    return *this;
}

template <typename Scalar>
template <typename Scalar2>
Dual<Scalar>& Dual<Scalar>::operator*=(const Dual<Scalar2>& rhs){
    this->adDual *= rhs.real();
    this->adDual += this->adReal * rhs.dual();
    this->adReal *= rhs.real(); 
    return *this;
}

template <typename Scalar>
template <typename Scalar2>
Dual<Scalar>& Dual<Scalar>::operator/=(const Dual<Scalar2>& rhs){
    this->adReal /= rhs.real(); 
    this->adDual -= this->adReal * rhs.dual();
    this->adDual /= rhs.real();
    return *this;
}

// Non-member functions
template <typename Scalar> 
ostream& operator<<(ostream& os, const Dual<Scalar>& rhs){
    os << rhs.real() << "+" << rhs.dual() << "e";
    return os;
}

template <typename Scalar> 
bool operator!=(const Dual<Scalar>& b, Scalar a){
    return a != b.real();
}

template <typename Scalar> 
bool operator!=(Scalar a, const Dual<Scalar>& b){
    return a != b.real();
}

template <typename Scalar1, typename Scalar2> 
bool operator!=(const Dual<Scalar1>& a, const Dual<Scalar2>& b){
    return a.real() != b.real();
}

template <typename Scalar> 
bool operator==(const Dual<Scalar>& b, Scalar a){
    return a == b.real();
}

template <typename Scalar> 
bool operator==(Scalar a, const Dual<Scalar>& b){
    return a == b.real();
}

template <typename Scalar1, typename Scalar2> 
bool operator==(const Dual<Scalar1>& a, const Dual<Scalar2>& b){
    return a.real() == b.real();
}

template <typename Scalar> 
bool operator<(const Dual<Scalar>& a, Scalar b){
    return a.real() < b;
}

template <typename Scalar> 
bool operator<(Scalar a, const Dual<Scalar>& b){
    return a < b.real();
}

template <typename Scalar1, typename Scalar2> 
bool operator<(const Dual<Scalar1>& a, const Dual<Scalar2>& b){
    return a.real() < b.real();
}

template <typename Scalar> 
bool operator>(const Dual<Scalar>& a, Scalar b){
    return a.real() > b;
}

template <typename Scalar> 
bool operator>(Scalar a, const Dual<Scalar>& b){
    return a > b.real();
}

template <typename Scalar1, typename Scalar2> 
bool operator>(const Dual<Scalar1>& a, const Dual<Scalar2>& b){
    return a.real() > b.real();
}

template <typename Scalar> 
bool operator<=(const Dual<Scalar>& a, Scalar b){
    return a.real() <= b;
}

template <typename Scalar> 
bool operator<=(Scalar a, const Dual<Scalar>& b){
    return a <= b.real();
}

template <typename Scalar1, typename Scalar2> 
bool operator<=(const Dual<Scalar1>& a, const Dual<Scalar2>& b){
    return a.real() <= b.real();
}

template <typename Scalar> 
bool operator>=(const Dual<Scalar>& a, Scalar b){
    return a.real() >= b;
}

template <typename Scalar> 
bool operator>=(Scalar a, const Dual<Scalar>& b){
    return a >= b.real();
}

template <typename Scalar1, typename Scalar2> 
bool operator>=(const Dual<Scalar1>& a, const Dual<Scalar2>& b){
    return a.real() >= b.real();
}

template <typename Scalar>
Dual<Scalar> operator-(const Dual<Scalar>& rhs){
    return Dual<Scalar>(-rhs.real(), -rhs.dual());
} 
    
template <typename Scalar>
Dual<Scalar> operator-(const Dual<Scalar>& lhs, Scalar rhs){
    return Dual<Scalar>(lhs.real() - rhs, lhs.dual());
}

template <typename Scalar>
Dual<Scalar> operator-(Scalar lhs, const Dual<Scalar>& rhs){
    return Dual<Scalar>(lhs - rhs.real(), -rhs.dual());
}

template <typename Scalar>
Dual<Scalar> operator-(const Dual<Scalar>& a, const Dual<Scalar>& b){
    return Dual<Scalar>(a.real() - b.real(), a.dual() - b.dual());
}

template <typename Scalar>
Dual<Scalar> operator+(const Dual<Scalar>& lhs, Scalar rhs){
    return Dual<Scalar>(lhs.real() + rhs, lhs.dual());
}

template <typename Scalar>
Dual<Scalar> operator+(Scalar lhs, const Dual<Scalar>& rhs){
    return Dual<Scalar>(lhs + rhs.real(), rhs.dual());
}

template <typename Scalar>
Dual<Scalar> operator+(const Dual<Scalar>& a, const Dual<Scalar>& b){
    return Dual<Scalar>(a.real() + b.real(), a.dual() + b.dual());
}

template <typename Scalar>
Dual<Scalar> operator*(const Dual<Scalar>& lhs, Scalar rhs){
    return Dual<Scalar>(lhs.real() * rhs, lhs.dual() * rhs);
}

template <typename Scalar>
Dual<Scalar> operator*(Scalar lhs, const Dual<Scalar>& rhs){
    return Dual<Scalar>(lhs * rhs.real(), lhs * rhs.dual());
}

template <typename Scalar>
Dual<Scalar> operator*(const Dual<Scalar>& a, const Dual<Scalar>& b){
    return Dual<Scalar>(a.real() * b.real(), a.dual() * b.real() + b.dual() * a.real());
}

template <typename Scalar>
Dual<Scalar> operator/(const Dual<Scalar>& lhs, Scalar rhs){
    return Dual<Scalar>(lhs.real() / rhs, lhs.dual() / rhs);
}

template <typename Scalar>
Dual<Scalar> operator/(Scalar lhs, const Dual<Scalar>& rhs){
    lhs /= rhs.real(); 
    return Dual<Scalar>(lhs, -lhs * rhs.dual() / rhs.real());
}

template <typename Scalar>
Dual<Scalar> operator/(const Dual<Scalar>& lhs, const Dual<Scalar>& rhs){
    return Dual<Scalar>(lhs.real()/rhs.real(), (lhs.dual()*rhs.real()-lhs.real()*rhs.dual())/(rhs.real()*rhs.real()) );
}

// math operator
template <typename Scalar>    
Dual<Scalar> acos(const Dual<Scalar>& z){
    return Dual<Scalar>(acos(z.real()), -z.dual() / sqrt(1 - z.real() * z.real()));
}


template <typename Scalar>    
Dual<Scalar> asin(const Dual<Scalar>& z){
    return Dual<Scalar>(asin(z.real()), z.dual() / sqrt(1 - z.real() * z.real()));
}

template <typename Scalar>   
Dual<Scalar> atan(const Dual<Scalar>& z){
    return Dual<Scalar>(atan(z.real()), z.dual() / (1 + z.real() * z.real()));
}

template <typename Scalar>     
Dual<Scalar> atan2(const Dual<Scalar>& y, const Dual<Scalar>& x){
    Dual<Scalar> z = y / x;
    Scalar quadrant = x.real()<0 ? (y.real()<0 ? -PI : PI) : 0; 
    return Dual<Scalar>(atan(z.real()) + quadrant, z.dual() / (1 + z.real() * z.real()));
}

template <typename Scalar> 
Dual<Scalar> cos(const Dual<Scalar>& z){
    return Dual<Scalar>(cos(z.real()), -z.dual() * sin(z.real()));
}

template <typename Scalar>   
Dual<Scalar> cosh(const Dual<Scalar>& z){
    return Dual<Scalar>(cosh(z.real()), z.dual() * sinh(z.real()));
}

template <typename Scalar>    
Dual<Scalar> exp(const Dual<Scalar>& z){
    Scalar x = exp(z.real());
    return Dual<Scalar>(x, z.dual() * x);
}

template <typename Scalar>    
Dual<Scalar> log(const Dual<Scalar>& z){
    return Dual<Scalar>(log(z.real()), z.dual() / z.real());
}

template <typename Scalar>    
Dual<Scalar> log10(const Dual<Scalar>& z){
    return log(z) / log(10);
}

template <typename Scalar> 
Dual<Scalar> pow(const Dual<Scalar>& x, Scalar y){
    return Dual<Scalar>(pow(x.real(),y),x.dual()*y*pow(x.real(),y-1));
}

template <typename Scalar>     
Dual<Scalar> sin(const Dual<Scalar>& z){
    return Dual<Scalar>(sin(z.real()), z.dual() * cos(z.real()));
}

template <typename Scalar>     
Dual<Scalar> sinh(const Dual<Scalar>& z){
    return Dual<Scalar>(sinh(z.real()), z.dual() * cosh(z.real()));
}

template <typename Scalar>     
Dual<Scalar> sqrt(const Dual<Scalar>& z){
    Scalar x = sqrt(z.real());
    return Dual<Scalar>(x, z.dual() / (2 * x));
}

template <typename Scalar>     
Dual<Scalar> tan(const Dual<Scalar>& z){
    Scalar x = tan(z.real());
    return Dual<Scalar>(x, z.dual() / (cos(z.real())*cos(z.real())) );
}

template <typename Scalar>   
Dual<Scalar> tanh(const Dual<Scalar>& z){
    Scalar x = tanh(z.real());
    return Dual<Scalar>(x, z.dual() * (1 - x * x));
}
