#include "Dual.h"
#include <math.h>

#define PI 3.141592653589793238


Dual::Dual(){
    this->adReal = 0;
    this->adDual = 1;
}


Dual::Dual(double real){
    this->adReal = real;
    this->adDual = 1;
}


Dual::Dual(double real, double dual)
    : adReal(real)
    , adDual(dual)
{}


Dual::Dual(const Dual& rhs)
    : adReal(rhs.real())
    , adDual(rhs.dual())
{}


double Dual::real() const {
    return adReal;
}


double Dual::dual() const {
    return adDual;
}


Dual& Dual::operator=(double rhs){
    this->adReal = rhs; 
    this->adDual = 0; 
    return *this;
}


Dual& Dual::operator+=(double rhs){
    this->adReal += rhs; 
    return *this;
}


Dual& Dual::operator-=(double rhs){
    this->adReal -= rhs; 
    return *this;
} 


Dual& Dual::operator*=(double rhs){
    this->adReal *= rhs;
    this->adDual *= rhs;
    return *this;
} 


Dual& Dual::operator/=(double rhs){
    this->adReal /= rhs;
    this->adDual /= rhs;
    return *this;
}



Dual& Dual::operator=(const Dual& rhs){
    this->adReal = rhs.real(); 
    this->adDual = rhs.dual(); 
    return *this;
}



Dual& Dual::operator+=(const Dual& rhs){
    this->adReal += rhs.real(); 
    this->adDual += rhs.dual(); 
    return *this;
}  



Dual& Dual::operator-=(const Dual& rhs){
    this->adReal -= rhs.real(); 
    this->adDual -= rhs.dual(); 
    return *this;
}



Dual& Dual::operator*=(const Dual& rhs){
    this->adDual *= rhs.real();
    this->adDual += this->adReal * rhs.dual();
    this->adReal *= rhs.real(); 
    return *this;
}



Dual& Dual::operator/=(const Dual& rhs){
    this->adDual = (adDual*rhs.real()-adReal*rhs.dual())/(rhs.real()*rhs.real());
    this->adReal /= rhs.real(); 
    return *this;
}

// Non-member functions
ostream& operator<<(ostream& os, const Dual& rhs){
    os << rhs.real() << "+" << rhs.dual() << "e";
    return os;
}

 
bool operator!=(const Dual& b, double a){
    return a != b.real();
}

 
bool operator!=(double a, const Dual& b){
    return a != b.real();
}

bool operator!=(const Dual& a, const Dual& b){
    return a.real() != b.real();
}

 
bool operator==(const Dual& b, double a){
    return a == b.real();
}

 
bool operator==(double a, const Dual& b){
    return a == b.real();
}


bool operator==(const Dual& a, const Dual& b){
    return a.real() == b.real();
}

 
bool operator<(const Dual& a, double b){
    return a.real() < b;
}

 
bool operator<(double a, const Dual& b){
    return a < b.real();
}


bool operator<(const Dual& a, const Dual& b){
    return a.real() < b.real();
}

 
bool operator>(const Dual& a, double b){
    return a.real() > b;
}

 
bool operator>(double a, const Dual& b){
    return a > b.real();
}


bool operator>(const Dual& a, const Dual& b){
    return a.real() > b.real();
}

 
bool operator<=(const Dual& a, double b){
    return a.real() <= b;
}

 
bool operator<=(double a, const Dual& b){
    return a <= b.real();
}


bool operator<=(const Dual& a, const Dual& b){
    return a.real() <= b.real();
}

 
bool operator>=(const Dual& a, double b){
    return a.real() >= b;
}

 
bool operator>=(double a, const Dual& b){
    return a >= b.real();
}


bool operator>=(const Dual& a, const Dual& b){
    return a.real() >= b.real();
}

// negate sign
Dual operator-(const Dual& rhs){
    return Dual(-rhs.real(), -rhs.dual());
} 
    

Dual operator-(const Dual& lhs, double rhs){
    return Dual(lhs.real() - rhs, lhs.dual());
}


Dual operator-(double lhs, const Dual& rhs){
    return Dual(lhs - rhs.real(), -rhs.dual());
}


Dual operator-(const Dual& a, const Dual& b){
    return Dual(a.real() - b.real(), a.dual() - b.dual());
}


Dual operator+(const Dual& lhs, double rhs){
    return Dual(lhs.real() + rhs, lhs.dual());
}


Dual operator+(double lhs, const Dual& rhs){
    return Dual(lhs + rhs.real(), rhs.dual());
}


Dual operator+(const Dual& a, const Dual& b){
    return Dual(a.real() + b.real(), a.dual() + b.dual());
}


Dual operator*(const Dual& lhs, double rhs){
    return Dual(lhs.real() * rhs, lhs.dual() * rhs);
}


Dual operator*(double lhs, const Dual& rhs){
    return Dual(lhs * rhs.real(), lhs * rhs.dual());
}


Dual operator*(const Dual& a, const Dual& b){
    return Dual(a.real() * b.real(), a.dual() * b.real() + b.dual() * a.real());
}


Dual operator/(const Dual& lhs, double rhs){
    return Dual(lhs.real() / rhs, lhs.dual() / rhs);
}


Dual operator/(double lhs, const Dual& rhs){
    return Dual(lhs/rhs.real(), rhs.dual()*lhs*(-1)*(1/(rhs.real()*rhs.real())));
}


Dual operator/(const Dual& lhs, const Dual& rhs){
    return Dual(lhs.real()/rhs.real(), (lhs.dual()*rhs.real()-lhs.real()*rhs.dual())/(rhs.real()*rhs.real()) );
}

// math operator
    
Dual acos(const Dual& z){
    return Dual(acos(z.real()), -z.dual() / sqrt(1 - z.real() * z.real()));
}


    
Dual asin(const Dual& z){
    return Dual(asin(z.real()), z.dual() / sqrt(1 - z.real() * z.real()));
}

   
Dual atan(const Dual& z){
    return Dual(atan(z.real()), z.dual() / (1 + z.real() * z.real()));
}

     
Dual atan2(const Dual& y, const Dual& x){
    Dual z = y / x;
    return Dual(atan2(y.real(),x.real()), z.dual() / (1 + z.real() * z.real()));
}

 
Dual cos(const Dual& z){
    return Dual(cos(z.real()), -z.dual() * sin(z.real()));
}

   
Dual cosh(const Dual& z){
    return Dual(cosh(z.real()), z.dual() * sinh(z.real()));
}

    
Dual exp(const Dual& z){
    double x = exp(z.real());
    return Dual(x, z.dual() * x);
}

    
Dual log(const Dual& z){
    return Dual(log(z.real()), z.dual() / z.real());
}

    
Dual log10(const Dual& z){
    return log(z) / log(10);
}

    
Dual pow(const Dual& x, const Dual& y){
    return Dual(pow(x.real(),y.real()), y.real()*y.dual()*pow(x.real(),y.real()-1)*x.dual());
}

     
Dual sin(const Dual& z){
    return Dual(sin(z.real()), z.dual() * cos(z.real()));
}

     
Dual sinh(const Dual& z){
    return Dual(sinh(z.real()), z.dual() * cosh(z.real()));
}

     
Dual sqrt(const Dual& z){
    double x = sqrt(z.real());
    return Dual(x, z.dual() / (2 * x));
}

     
Dual tan(const Dual& z){
    double x = tan(z.real());
    return Dual(x, z.dual() / (cos(z.real()*cos(z.real()))) );
}

   
Dual tanh(const Dual& z){
    double x = tanh(z.real());
    return Dual(x, z.dual() * (1 - x * x));
}
