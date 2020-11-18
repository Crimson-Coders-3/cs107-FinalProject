#include "../include/dual.h"

template <typename Scalar>
FORCEINLINE
Dual<Scalar>::Dual(Scalar real, Scalar dual)
    : mReal(real)
    , mDual(dual)
{}

template <typename Scalar>
template <typename Scalar2>
FORCEINLINE
Dual<Scalar>::Dual(const Dual<Scalar2>& rhs)
    : mReal(rhs.real())
    , mDual(rhs.dual())
{}

template <typename Scalar>
FORCEINLINE
Scalar Dual<Scalar>::real() const
{
    return mReal;
}

template <typename Scalar>
FORCEINLINE
Scalar Dual<Scalar>::dual() const
{
    return mDual;
}