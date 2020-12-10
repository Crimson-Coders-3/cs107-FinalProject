#include "../AutoDiff/include/ADFunc.h"
#include "../AutoDiff/include/ADFuncVector.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    vector<double> seed_x;
    seed_x.push_back(2.0);
    ADFunc x(2.0,seed_x);
    cout << x.val() << endl;
    cout << x.dval_wrt(0) << endl;

    ADFunc y = (x +2.0+x)*3.0 /3.2 *x + 2.0 + x;
    cout << y.val() << endl;
    cout << y.dval_wrt(0) << endl;

    // Example of differentiating a vector-valued function f(a,b)
    std::vector<double> init_values = {1.0, 5.0};
    std::vector<ADFunc> multi_vars = multiVar(init_values);
    ADFunc a = multi_vars[0];
    ADFunc b = multi_vars[1];
    ADFunc f1 = sin(a)+cos(b);
    ADFunc f2 = 2*a+3*b;
    std::vector<ADFunc> F = {f1, f2};
    ADFuncVector Fvec(F);
    double df1_dx = f1.dval_wrt(0);
    cout << df1_dx << endl;

    vector<double> df_dx = Fvec.dval_wrt(0);
    cout << df_dx[0] << endl;
    cout << df_dx[1] << endl;
	return 0;
}
