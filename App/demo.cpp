/* system header files */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

/* header files */
#include "AutoDiff.h"

int main(int argc, char **argv){

    AutoDiff x1(1.0);
    AutoDiff x2(2.0);
    
    /* add operator */
    AutoDiff c = x1 + x2;

    std::cout << "     v, dv\n";
    std::cout << "  x1[" << x1.getVal() << ", " << x1.getDer() << "]\n"
              << "+ x2[" << x2.getVal() << ", " << x2.getDer() << "]\n"
              << "  ==========\n";
             // << "   c[" <<  c.getVal() << ", " <<  c.getDer() << "]\n";

    return 0;
}