#include "../AutoDiff/include/AutoDiff.h"
#include <math.h>
#include <cmath>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

AutoDiff choose_order(int order, double val = 0){
    AutoDiff w = AutoDiff(val);
    for(int r=0; r<order-1; r++){
        w = AutoDiff(w);
    }
    return w;
}

vector<double> der(function<vector<AutoDiff> (vector<AutoDiff>)> func, vector<AutoDiff> &vars, int wrt=0){
    vars[wrt].der = 1;
    vector<AutoDiff> F = func(vars);
    vector<double> dF(F.size(), 0);
    for(vector<double>::size_type i = 0; i<dF.size(); i++){
        dF[i] = F[i].der;
    }
    return dF;
}

vector<AutoDiff> F(vector<AutoDiff> vars){
    AutoDiff x = vars[0];
    AutoDiff y = vars[1];
    return {y*sin(x) + exp(x)*cos(y), 2*x + 3*y};
}

int main(){
    AutoDiff x(2,0);
    AutoDiff y(5,0);
    vector<AutoDiff> vars = {x,y};
    int wrt = 0;

    function<vector<AutoDiff>(vector<AutoDiff>)> myFunction = F;
    vector<double> dF = der(myFunction, vars, wrt = 0);
    cout << "Derivative of f1: " << dF[0] << endl;
    cout << "Derivative of f2: " << dF[1] << endl;

    AutoDiff w = choose_order(2);
    cout << w.val << endl;
    return 0;
}
