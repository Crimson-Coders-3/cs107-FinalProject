#include "Dual.h"
#include <math.h>

#define PI 3.141592653589793238


Dual<double>::Dual(){
    this->adReal = 0;
    this->adDual = 1;
}


Dual<double>::Dual(double real){
    this->adReal = real;
    this->adDual = 1;
}


Dual<double>::Dual(double real, double dual)
    : adReal(real)
    , adDual(dual)
{}


Dual<double>::Dual(const Dual<double>& rhs)
    : adReal(rhs.real())
    , adDual(rhs.dual())
{}


double Dual<double>::real() const {
    return adReal;
}


double Dual<double>::dual() const {
    return adDual;
}


Dual<double>& Dual<double>::operator=(double rhs){
    this->adReal = rhs; 
    this->adDual = 0; 
    return *this;
}


Dual<double>& Dual<double>::operator+=(double rhs){
    this->adReal += rhs; 
    return *this;
}


Dual<double>& Dual<double>::operator-=(double rhs){
    this->adReal -= rhs; 
    return *this;
} 


Dual<double>& Dual<double>::operator*=(double rhs){
    this->adReal *= rhs;
    this->adDual *= rhs;
    return *this;
} 


Dual<double>& Dual<double>::operator/=(double rhs){
    this->adReal /= rhs;
    this->adDual /= rhs;
    return *this;
}



Dual<double>& Dual<double>::operator=(const Dual<double>& rhs){
    this->adReal = rhs.real(); 
    this->adDual = rhs.dual(); 
    return *this;
}



Dual<double>& Dual<double>::operator+=(const Dual<double>& rhs){
    this->adReal += rhs.real(); 
    this->adDual += rhs.dual(); 
    return *this;
}  



Dual<double>& Dual<double>::operator-=(const Dual<double>& rhs){
    this->adReal -= rhs.real(); 
    this->adDual -= rhs.dual(); 
    return *this;
}



Dual<double>& Dual<double>::operator*=(const Dual<double>& rhs){
    this->adDual *= rhs.real();
    this->adDual += this->adReal * rhs.dual();
    this->adReal *= rhs.real(); 
    return *this;
}



Dual<double>& Dual<double>::operator/=(const Dual<double>& rhs){
    this->adDual = (this->adDual*rhs.real()-this.adReal()*rhs.dual())/(rhs.real()*rhs.real())
    this->adReal /= rhs.real(); 
    return *this;
}

// Non-member functions
ostream& operator<<(ostream& os, const Dual<double>& rhs){
    os << rhs.real() << "+" << rhs.dual() << "e";
    return os;
}

 
bool operator!=(const Dual<double>& b, double a){
    return a != b.real();
}

 
bool operator!=(double a, const Dual<double>& b){
    return a != b.real();
}

bool operator!=(const Dual<double>& a, const Dual<double>& b){
    return a.real() != b.real();
}

 
bool operator==(const Dual<double>& b, double a){
    return a == b.real();
}

 
bool operator==(double a, const Dual<double>& b){
    return a == b.real();
}


bool operator==(const Dual<double1>& a, const Dual<double2>& b){
    return a.real() == b.real();
}

 
bool operator<(const Dual<double>& a, double b){
    return a.real() < b;
}

 
bool operator<(double a, const Dual<double>& b){
    return a < b.real();
}


bool operator<(const Dual<double>& a, const Dual<double>& b){
    return a.real() < b.real();
}

 
bool operator>(const Dual<double>& a, double b){
    return a.real() > b;
}

 
bool operator>(double a, const Dual<double>& b){
    return a > b.real();
}


bool operator>(const Dual<double>& a, const Dual<double>& b){
    return a.real() > b.real();
}

 
bool operator<=(const Dual<double>& a, double b){
    return a.real() <= b;
}

 
bool operator<=(double a, const Dual<double>& b){
    return a <= b.real();
}


bool operator<=(const Dual<double>& a, const Dual<double>& b){
    return a.real() <= b.real();
}

 
bool operator>=(const Dual<double>& a, double b){
    return a.real() >= b;
}

 
bool operator>=(double a, const Dual<double>& b){
    return a >= b.real();
}


bool operator>=(const Dual<double>& a, const Dual<double>& b){
    return a.real() >= b.real();
}

// negate sign
Dual<double> operator-(const Dual<double>& rhs){
    return Dual<double>(-rhs.real(), -rhs.dual());
} 
    

Dual<double> operator-(const Dual<double>& lhs, double rhs){
    return Dual<double>(lhs.real() - rhs, lhs.dual());
}


Dual<double> operator-(double lhs, const Dual<double>& rhs){
    return Dual<double>(lhs - rhs.real(), -rhs.dual());
}


Dual<double> operator-(const Dual<double>& a, const Dual<double>& b){
    return Dual<double>(a.real() - b.real(), a.dual() - b.dual());
}


Dual<double> operator+(const Dual<double>& lhs, double rhs){
    return Dual<double>(lhs.real() + rhs, lhs.dual());
}


Dual<double> operator+(double lhs, const Dual<double>& rhs){
    return Dual<double>(lhs + rhs.real(), rhs.dual());
}


Dual<double> operator+(const Dual<double>& a, const Dual<double>& b){
    return Dual<double>(a.real() + b.real(), a.dual() + b.dual());
}


Dual<double> operator*(const Dual<double>& lhs, double rhs){
    return Dual<double>(lhs.real() * rhs, lhs.dual() * rhs);
}


Dual<double> operator*(double lhs, const Dual<double>& rhs){
    return Dual<double>(lhs * rhs.real(), lhs * rhs.dual());
}


Dual<double> operator*(const Dual<double>& a, const Dual<double>& b){
    return Dual<double>(a.real() * b.real(), a.dual() * b.real() + b.dual() * a.real());
}


Dual<double> operator/(const Dual<double>& lhs, double rhs){
    return Dual<double>(lhs.real() / rhs, lhs.dual() / rhs);
}


Dual<double> operator/(double lhs, const Dual<double>& rhs){
    return Dual<double>(lhs/rhs.real(), (rhs.real()-lhs * rhs.dual()) / (rhs.real()*rhs.real()));
}


Dual<double> operator/(const Dual<double>& lhs, const Dual<double>& rhs){
    return Dual<double>(lhs.real()/rhs.real(), (lhs.dual()*rhs.real()-lhs.real()*rhs.dual())/(rhs.real()*rhs.real()) );
}

// math operator
    
Dual<double> acos(const Dual<double>& z){
    return Dual<double>(acos(z.real()), -z.dual() / sqrt(1 - z.real() * z.real()));
}


    
Dual<double> asin(const Dual<double>& z){
    return Dual<double>(asin(z.real()), z.dual() / sqrt(1 - z.real() * z.real()));
}

   
Dual<double> atan(const Dual<double>& z){
    return Dual<double>(atan(z.real()), z.dual() / (1 + z.real() * z.real()));
}

     
Dual<double> atan2(const Dual<double>& y, const Dual<double>& x){
    Dual<double> z = y / x;
    return Dual<double>(atan2(y.real(),x.real()), z.dual() / (1 + z.real() * z.real()));
}

 
Dual<double> cos(const Dual<double>& z){
    return Dual<double>(cos(z.real()), -z.dual() * sin(z.real()));
}

   
Dual<double> cosh(const Dual<double>& z){
    return Dual<double>(cosh(z.real()), z.dual() * sinh(z.real()));
}

    
Dual<double> exp(const Dual<double>& z){
    double x = exp(z.real());
    return Dual<double>(x, z.dual() * x);
}

    
Dual<double> log(const Dual<double>& z){
    return Dual<double>(log(z.real()), z.dual() / z.real());
}

    
Dual<double> log10(const Dual<double>& z){
    return log(z) / log(10);
}

    
Dual<double> pow(const Dual<double>& x, const Dual<double>& y){
    return Dual<double>(pow(x.real(),y.real()), y.real()*y.dual()*pow(x.real(),y.real()-1)*x.dual());
}

     
Dual<double> sin(const Dual<double>& z){
    return Dual<double>(sin(z.real()), z.dual() * cos(z.real()));
}

     
Dual<double> sinh(const Dual<double>& z){
    return Dual<double>(sinh(z.real()), z.dual() * cosh(z.real()));
}

     
Dual<double> sqrt(const Dual<double>& z){
    double x = sqrt(z.real());
    return Dual<double>(x, z.dual() / (2 * x));
}

     
Dual<double> tan(const Dual<double>& z){
    double x = tan(z.real());
    return Dual<double>(x, z.dual() / (cos(z.real()*cos(z.real()))) );
}

   
Dual<double> tanh(const Dual<double>& z){
    double x = tanh(z.real());
    return Dual<double>(x, z.dual() * (1 - x * x));
}
