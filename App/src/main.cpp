# include "AutoDiff.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(){
        AutoDiff x(2.0,2.0);
        cout << x.getVal() << endl;
        cout << x.getDer() << endl;

        AutoDiff y = (x +2.0+x)*3.0 /3.2 *x + 2.0 + x;
        cout << y.getVal() << endl;
        cout << y.getDer() << endl;
}