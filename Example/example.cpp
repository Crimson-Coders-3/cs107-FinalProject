#include "../AutoDiff/include/AutoDiff.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
    // exp(sin(x))
    AutoDiff x1(2.0);
    AutoDiff x2 = sin(x1);
    AutoDiff x3 = exp(x2);

    // cos(x^0.5)
    AutoDiff x4 = pow(x1, 0.5);
    AutoDiff x5 = cos(x4);

    // sin((cos(x)^2 + x^2)^0.5)
    AutoDiff x6 = cos(x1);
    AutoDiff x7 = pow(x6, 2);
    AutoDiff x8 = pow(x1, 2);
    AutoDiff x9 = x7 + x8;
    AutoDiff x10 = pow(x9, 0.5);
    AutoDiff x11 = sin(x10);
    
    // cos(x^0.5) * sin((cos(x)^2 + x^2)^0.5)
    AutoDiff x12 = x5 * x11;

    AutoDiff out = x3 - x12; 
    cout << "Value: " << out.getVal() << endl;
    cout << "Derivative: " << out.getDer() << endl;

	return 0;
}
