#include <math.h>
#include <string>
#include <cmath>
#include "Roots.h"

using namespace std;

vector<ADFunc> customFunct2(Eigen::VectorXd vals){
     ADFunc x = ADFunc(vals[0], {1,0,0});
     ADFunc y = ADFunc(vals[1], {0,1,0});
     ADFunc z = ADFunc(vals[2], {0,0,1});
     return {5*sin(x), 3*y/2, z+2};
}


int main(){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct2;
    Equation eq(customFunct2, 3);
    Eigen::VectorXd guess(3);
    guess << 1, 1, 1;
    double tol = 1e-4;
    Eigen::VectorXd roots = eq.getRoots(guess, tol);
    cout << "Roots found: \n" << roots << endl;

    //Example of getting the Jacobian (as a MatrixXd object)
    ADFunc x = ADFunc(7, {1,0});
    ADFunc y = ADFunc(3, {0,1});
    vector<ADFunc> F2 = {2*pow(x,2), 5*sin(y)*x};
    Eigen::MatrixXd J = getJ(F2, 2);
    cout << "Jacobian of F: \n" << J << endl;
    return 0;
}
