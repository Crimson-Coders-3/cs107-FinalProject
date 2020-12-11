#include "ADFunc.h"
#include "ADFuncVector.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    // Example 1: x is a single number, f(x) is a function with a single variable
    // f.dval is a single number representing df/dx
    ADFunc x(5.0, vector<double> {1.0});
    ADFunc f = pow(x,2) + 5*exp(x);
    cout << "df/dx: " << f.dval_wrt(0) << endl; //752.07
    cout << "f value: " << f.val() << "\n" << endl; //767.07

    // Example 2: (x1,...,xn) vector inputs with a single function f(x1,..., xn)
    // f.dval is a vector with two elements, [df/dx1, df/d2, ...]
    vector<double> init_values = {5.0, 3.0};
    vector<ADFunc> multi_vars = multiVar(init_values);
    x = multi_vars[0];
    ADFunc y = multi_vars[1];
    f = pow((y*x), 2) + 7*sin(log(x));

    vector<double> dvals = f.dval_wrt(vector<int> {0,1});
    cout << "df/dx: " << dvals[0] << endl; //89.9459
    cout << "df/dy: " << dvals[1] << endl; //150
    cout << "f2 val: " << f.val() << "\n" << endl; //231.995
    
    // Example 3: x is a single number with a vectorized function F(x)
    // F(x) = [f1(x), f2(x), ..., fm(x)], each f_i(x) is a function with a single variable
    // F.dval is s a vector size m*1 [df1/dx, df2/dx, ..., dfm/dx]
    vector<ADFunc> F = {2*pow(x,2), 5*sin(x)*x};
    ADFuncVector Fvec(F);
    std::vector<std::pair<int, int> > fun_var_indexs = { {0,0}, {1,0} };
    
    dvals = Fvec.dval_wrt(fun_var_indexs);
    cout << "df1/dx: " << dvals[0] << endl; // 20.0
    cout << "df2/dx: " << dvals[1] << endl; // 2.29693
    cout << "val for f1: " << Fvec.val(0) << endl; // 50.0
    cout << "val for f2: " << Fvec.val(0) << "\n" <<endl; // -23.97

    // Example 4: x is a vector [x1, x2, ..., xn], 
    // F(x) is a vector of functions [f1(x), f2(x), ..., fm(x)]
    // f.der is a matrix with self defined size
    init_values.push_back(0.3);
    multi_vars = multiVar(init_values);
    x = multi_vars[0];
    y = multi_vars[1];
    ADFunc z = multi_vars[2];
    F = {2*pow(x,z)/y, 5*sin(y)*x+z/sin(y)*sinh(y), 9*sinh(z)-exp(x*y)};
    Fvec = ADFuncVector(F);
    vector<vector<std::pair<int, int> > > fun_var_index_m = { {{0,0},{2,1},{0,2}},{{1,0},{1,1},{2,2}}};

    vector<vector<double> > dval_m = Fvec.dval_wrt(fun_var_index_m);
    cout << "df1/dx1: " << dval_m[0][0] << endl; //
    cout << "df1/dx2: " << dval_m[0][1] << endl; //
    cout << "df1/dx3: " << dval_m[0][2] << endl;
    cout << "df2/dx1: " << dval_m[1][0] << endl;
    cout << "df2/dx2: " << dval_m[1][1] << endl;
    cout << "df2/dx3: " << dval_m[1][2] << endl;
    cout << "val for f1 in F: " << Fvec.val(0) << endl;
    cout << "val for f2 in F: " << Fvec.val(1) << endl;
    cout << "val for f3 in F: " << Fvec.val(2) << endl;

    return 0;
}
