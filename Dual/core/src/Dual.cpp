#include "Dual.h"

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
    mReal = rhs; 
    mDual = Scalar(); 
    return *this;
}
