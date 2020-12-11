#include "ADFunc.h"
#include "ADFuncVector.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    //vector<double> seed_x;
    //seed_x.push_back(2.0);
    //ADFunc x(2.0,seed_x);
    //cout << x.val() << endl;
    //cout << x.dval_wrt(0) << endl;

    //ADFunc y = (x +2.0+x)*3.0 /3.2 *x + 2.0 + x;
    //cout << y.val() << endl;
    //cout << y.dval_wrt(0) << endl;

    // Example of differentiating a vector-valued function f(a,b)
    //std::vector<double> init_values = {1.0, 5.0};
    //std::vector<ADFunc> multi_vars = multiVar(init_values);
    //ADFunc a = multi_vars[0];
    //ADFunc b = multi_vars[1];
    //ADFunc f1 = sin(a)+cos(b);

    /*
    ADFunc f2 = 2*a+3*b;
    std::vector<ADFunc> F = {f1, f2};
    ADFuncVector Fvec(F);
    double df1_dx = f1.dval_wrt(0);
    cout << df1_dx << endl;

    vector<double> df_dx = Fvec.dval_wrt(0);
    cout << df_dx[0] << endl;
    cout << df_dx[1] << endl;
    */

    // Example 1: scalar input, scalar function; f(x) = x^2 + 5exp(x) at x = 5
    ADFunc x1(5.0, {1.0});
    ADFunc f1 = pow(x1,2) + 5*exp(x1);
    cout << "df/dx: " << f1.dval_wrt(0) << endl;
    cout << "value: " << f1.val() << endl;

    // Example 2: f(x,y) = (y*x)^2 + 7*sin(log(x)) at x=5, y=3
    // should give for df/dx: 89.945
    // should give for df/dy: 150
    vector<double> init_values = {5.0, 3.0};
    vector<ADFunc> multi_vars = multiVar(init_values);
    ADFunc x2 = multi_vars[0];
    ADFunc y2 = multi_vars[1];
    ADFunc f2 = pow((y2*x2), 2) + 7*sin(log(x2));
    cout << "df/dx: " << f2.dval_wrt(0) << endl;
    cout << "df/dy: " << f2.dval_wrt(1) << endl;
    cout << "val for f2: " << f2.val() << endl;
    
    // Example 3: 2x^2 + 5*sin(y)*x
    vector<ADFunc> F = {2*pow(x,2) + 5*sin(y)*x};
    ADFuncVector Fvec(F);
    //[dval_wrt(0), dval_wrt()]

    // Example 4: 
    return 0;
}
