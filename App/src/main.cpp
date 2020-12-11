#include "ADFunc.h"
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace std;

int main(){
    cout << "testing......." << endl;
	//MatrixXd m(2,2);
    //m(0,0) = 3;
    //m(1,0) = 2.5;
    //m(0,1) = -1;
    //m(1,1) = m(1,0) + m(0,1);
    //cout << m << endl;

    vector<double> seed_x;
	seed_x.push_back(2.0);
    ADFunc x(2.0,seed_x);

    cout << x.val() << endl;
    cout << x.dval_wrt(0) << endl;

    ADFunc y = (x +2.0+x)*3.0 /3.2 *x + 2.0 + x;
    cout << y.val() << endl;
    cout << y.dval_wrt(0) << endl;

    return 0;
}
