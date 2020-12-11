#include "Roots.h"
#include <math.h>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using namespace std;

///CONSTRUCTOR
Roots::Roots(function<vector<ADFunc> (VectorXd)> customFunc, int num_vars = 0){
    _function = customFunc;
    _num_vars = num_vars;
}

Roots Roots::operator =(const Roots &obj){
    _function = obj.function();
    _num_vars = obj.num_vars();
    return *this;
}

//PRINT ROOTS OBJECT
ostream& operator<<(ostream& os, const Roots& obj){
    os << "Information of Roots object: \n";
    os << "Function: " << obj.function();
    os << "Number of variables in function: " << obj.num_vars();
    return os;
}


// Get the matrix F(a)
VectorXd getF(vector<ADFunc> Function){
    int num_functions = Function.size();
    VectorXd F(num_functions);
    for(int m=0; m<num_functions; ++m){
        F(m) = Function[m].val();
    }
    return F;
}

// Evaluate the Jacobian of F
MatrixXd getJ(vector<ADFunc> Function, int num_vars){
    int num_functions = Function.size();
    MatrixXd J(num_functions, num_vars);
    for(int m=0; m<num_functions; ++m){
        for(int n=0; n<num_vars; ++n){
            J(m,n) = Function[m].dval_wrt(n);
        }
    }
    return J;
}

VectorXd Roots::getRoots(function<vector<ADFunc> (VectorXd)> customFunct, VectorXd guess, double tol = 1e-3){
    //Based on:
    //https://hplgit.github.io/Programming-for-Computations/pub/p4c/._p4c-solarized-Python031.html
    int num_iterations = 0;
    
    vector<ADFunc> F = customFunct(guess);
    VectorXd Fv = getF(F);
    double Fv_norm = Fv.squaredNorm();
    
    VectorXd delta(guess.size());
    
    MatrixXd J(F.size(), guess.size());
    
    while ((abs(Fv_norm) > tol) and (num_iterations < 100)){
        //For other decomposition methods and performance comparison, see:
        //https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html
        J = getJ(F, guess.size());
        delta = J.householderQr().solve(-Fv);
        guess = guess + delta;
        F = customFunct(guess);
        Fv = getF(F);
        Fv_norm = Fv.squaredNorm();
        cout << "Iter: " << num_iterations << " L2 norm: " << Fv_norm << endl;
        num_iterations++;
    }

    if (abs(Fv_norm) > tol) {
        cout << "Warning: Reached max iterations without solution" << endl;
    }
    return guess;
}
