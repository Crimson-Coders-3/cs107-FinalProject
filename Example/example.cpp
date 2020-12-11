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

    // Example 1: x is a single number, f(x) is a single function
    // f.dval is a single number representing df/dx
    ADFunc x1(5.0, vector<double> {1.0});
    ADFunc f1 = pow(x1,2) + 5*exp(x1);
    cout << "df/dx: " << f1.dval_wrt(0) << endl;
    cout << "value: " << f1.val() << endl;

    // Example 2: (x,y) vector inputs with a single function f(x,y)
    // f.dval is a vector with two elements, [df/dx, df/dy]

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
    
    // Example 3: x is a scalar input with a vector function
    // x is a single number, F(x) is a vector of functions [f1(x), f2(x), ..., fm(x)]
    // F.dval is s a vector with m elements [df1/dx, df2/dx, ..., dfm/dx]
    vector<ADFunc> F = {2*pow(x2,2), 5*sin(x2)*x2};
    ADFuncVector Fvec(F);
    std::vector<std::pair<int, int> > fun_var_indexs = { {0,0}, {1,0} };
    vector<double> dvals = Fvec.dval_wrt(fun_var_indexs);
    cout << "df1/dx: " << dvals[0] << endl;
    cout << "df2/dx: " << dvals[1] << endl;
    cout << "val for F: " << Fvec.val(0) << endl;

    // Example 4: x is a vector [x1, x2, ..., xn], 
    // F(x) is a vector of functions [f1(x), f2(x), ..., fm(x)]
    // f.der is a matrix
    init_values.push_back(0.3);
    multi_vars = multiVar(init_values);
    ADFunc x4 = multi_vars[0];
    ADFunc y4 = multi_vars[1];
    ADFunc z4 = multi_vars[2];
    F = {2*pow(x4,2), 5*sin(y4)*x4+z4/sin(y4), 9*sinh(z4)-exp(x4*y4)};
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
