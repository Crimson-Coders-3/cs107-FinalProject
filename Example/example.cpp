#include "../AutoDiff/include/AutoDiff.h"
#include <math.h>
#include <cmath>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

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
    return {y*sin(x) + exp(x)*cos(y), 2*x + 3*y, (y*sin(x) + exp(x)*cos(y))*(2*x+3*y)};
}

vector<AutoDiff> F2(vector<AutoDiff> vars){
    AutoDiff x = vars[0];
    return {sin(pow(x,3))};
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
    cout << "Derivative of f3: " << dF[2] << endl;


    AutoDiff x1(2,0);
    vector<AutoDiff> vars2 = {x1};
    function<vector<AutoDiff>(vector<AutoDiff>)> myFunction2 = F2;
    vector<double> dF2 = der(myFunction2, vars2, wrt=0);
    cout << "Derivative of f1: " << dF2[0] << endl;
    
    return 0;
}
