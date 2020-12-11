#include "ADFunc.h"
#include "ADFuncVector.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    // Example 1: x is a single number, f(x) is a single function
    // f.dval is a single number representing df/dx
    ADFunc x(5.0, vector<double> {1.0});
    ADFunc f1 = pow(x,2) + 5*exp(x);
    cout << "df/dx: " << f1.dval_wrt(0) << endl;
    cout << "value: " << f1.val() << endl;

    // Example 2: (x1,...,xn) vector inputs with a single function f(x1,..., xn)
    // f.dval is a vector with two elements, [df/dx1, df/d2, ...]
    vector<double> init_values = {5.0, 3.0};
    vector<ADFunc> multi_vars = multiVar(init_values);
    x = multi_vars[0];
    ADFunc y = multi_vars[1];
    ADFunc f2 = pow((y*x), 2) + 7*sin(log(x));

    vector<double> dvals = f2.dval_wrt(vector<int> {0,1});
    cout << "df/dx: " << dvals[0] << endl; //89.945
    cout << "df/dy: " << dvals[1] << endl; //150
    cout << "val for f2: " << f2.val() << endl; //
    
    // Example 3: x is a scalar input with a vector function
    // x is a single number, F(x) is a vector of functions [f1(x), f2(x), ..., fm(x)]
    // F.dval is s a vector with m elements [df1/dx, df2/dx, ..., dfm/dx]
    vector<ADFunc> F = {2*pow(x,2), 5*sin(x)*x};
    ADFuncVector Fvec(F);
    std::vector<std::pair<int, int> > fun_var_indexs = { {0,0}, {1,0} };
    
    dvals = Fvec.dval_wrt(fun_var_indexs);
    cout << "df1/dx: " << dvals[0] << endl;
    cout << "df2/dy: " << dvals[1] << endl;
    cout << "val for F: " << Fvec.val(0) << endl;

    // Example 4: x is a vector [x1, x2, ..., xn], 
    // F(x) is a vector of functions [f1(x), f2(x), ..., fm(x)]
    // f.der is a matrix
    init_values.push_back(0.3);
    multi_vars = multiVar(init_values);
    x = multi_vars[0];
    y = multi_vars[1];
    ADFunc z = multi_vars[2];
    F = {2*pow(x,2), 5*sin(y)*x+z/sin(y), 9*sinh(z)-exp(x*y)};
    Fvec = ADFuncVector(F);
    vector<vector<std::pair<int, int> > > fun_var_index_m = { {{0,0},{0,1},{0,2}},{{1,0},{1,1},{1,2}},{{2,0},{2,1},{2,2}}};

    vector<vector<double> > dval_m = Fvec.dval_wrt(fun_var_index_m);
    cout << "df1/dx1: " << dval_m[0][0] << endl;
    cout << "df1/dx2: " << dval_m[0][1] << endl;
    cout << "df1/dx3: " << dval_m[0][2] << endl;
    cout << "df2/dx1: " << dval_m[1][0] << endl;
    cout << "df2/dx2: " << dval_m[1][1] << endl;
    cout << "df2/dx3: " << dval_m[1][2] << endl;
    cout << "df3/dx1: " << dval_m[2][0] << endl;
    cout << "df3/dx2: " << dval_m[2][1] << endl;
    cout << "df3/dx3: " << dval_m[2][2] << endl;
    cout << "val for f1 in F: " << Fvec.val(0) << endl;
    cout << "val for f2 in F: " << Fvec.val(1) << endl;
    cout << "val for f3 in F: " << Fvec.val(2) << endl;

    return 0;
}
