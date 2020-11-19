#include "Dual.h"

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
