#include "ADFuncVector.h"
#include "ADFunc.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/QR>
#include <functional>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using namespace std;

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

VectorXd getRoots(function<vector<ADFunc> (VectorXd)> customFunct, VectorXd guess, double tol = 1e-3){
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

// Custom defined function (our function of interest)
vector<ADFunc> customFunct(VectorXd vals){
    ADFunc x = ADFunc(vals[0], {1,0});
    ADFunc y = ADFunc(vals[1], {0,1});
    return {2*pow(x,2), 5*sin(y)*x};
}

int main(){
    /* -- Example of getting the Jacobian (as a MatrixXd object) --
    ADFunc x = ADFunc(7, {1,0});
    ADFunc y = ADFunc(3, {0,1});
    vector<ADFunc> Func = {2*pow(x,2), 5*sin(y)*x};
    MatrixXd J = getJ(Func, 2);
    cout << J << endl;

    MatrixXd F = getF(Func);
    cout << F << endl;
    */

    function<vector<ADFunc>(VectorXd)> Func = customFunct;
    VectorXd initial_guess(2);
    initial_guess << 1, 1;
    VectorXd roots = getRoots(customFunct, initial_guess, 0.000001);
    cout << "------------ROOT:-----------" << endl;
    cout << roots << endl;
    return 0;
}
