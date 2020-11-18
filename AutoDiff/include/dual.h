#ifndef DUAL_H
#define DUAL_H

/* system header files */
#include <ostream>

/* namespace */
using namespace std;

namespace mt
{
    template <typename Scalar>
    class Dual{

    public:
        
        Dual(Scalar real = Scalar(), Scalar dual = Scalar());
        template <typename Scalar2> Dual(const Dual<Scalar2>& rhs);
        
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
        Scalar mReal;
        Scalar mDual;
    };
#endif