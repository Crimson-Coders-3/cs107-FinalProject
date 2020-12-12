#include "Roots.h"
#include <math.h>

///CONSTRUCTOR
Equation::Equation(std::function<std::vector<ADFunc> (Eigen::VectorXd)> customFunc,\
int customNumVars){
    function = customFunc;
    num_vars = customNumVars;
}

Equation Equation::operator =(const Equation &obj){
    function = obj.function;
    num_vars = obj.num_vars;
    return *this;
}

//PRINT ROOTS OBJECT
std::ostream& operator<<(std::ostream& os, const Equation& obj){
    os << "Information of Equation object: \n";
    os << "Function with " << obj.num_vars << " variables";
    return os;
}


// Get the vector F(a)
Eigen::VectorXd getF(std::vector<ADFunc> Function){
    int num_functions = Function.size();
    Eigen::VectorXd F(num_functions);
    for(int m=0; m<num_functions; ++m){
        F(m) = Function[m].val();
    }
    return F;
}

// Evaluate the Jacobian of F
Eigen::MatrixXd getJ(std::vector<ADFunc> Function, int num_vars){
    int num_functions = Function.size();
    Eigen::MatrixXd J(num_functions, num_vars);
    for(int m=0; m<num_functions; ++m){
        for(int n=0; n<num_vars; ++n){
            J(m,n) = Function[m].dval_wrt(n);
        }
    }
    return J;
}

Eigen::VectorXd Equation::getRoots(Eigen::VectorXd guess, double tol){
    //Based on:
    //https://hplgit.github.io/Programming-for-Computations/pub/p4c/._p4c-solarized-Python031.html
    int num_iterations = 0;
    
    std::vector<ADFunc> F = function(guess);
    Eigen::VectorXd Fv = getF(F);
    double Fv_norm = Fv.squaredNorm();
    
    Eigen::VectorXd delta(guess.size());
    Eigen::MatrixXd J(F.size(), guess.size());
    
    while ((abs(Fv_norm) > tol) and (num_iterations < 100)){
        //For other decomposition methods and performance comparison, see:
        //https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html
        J = getJ(F, guess.size());
        delta = J.householderQr().solve(-Fv);
        guess = guess + delta;
        F = function(guess);
        Fv = getF(F);
        Fv_norm = Fv.squaredNorm();
        //std::cout << "Iter: " << num_iterations << " L2 norm: " << Fv_norm << std::endl;
        num_iterations++;
    }

    if (abs(Fv_norm) > tol) {
        std::cout << "Warning: Reached max iterations without solution" << std::endl;
    }
    return guess;
}
