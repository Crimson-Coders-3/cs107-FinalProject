#include "AutoDiff.h"
#include <math.h>
#

autodiff sin(autodiff input)
{
    autodiff output;
    output.val = sin(input.val);
    output.der = cos(input.val) * input.der
    return output;
}

autodiff cos(autodiff input)
{   
    autodiff output;
    output.val = cos(input.val);
    output.der = -sin(input.val) * input.der
    return output;
}

autodiff tan(autodiff input)
{
    autodiff output;
    output.val = tan(input.val);
    output.der = pow(1/cos(input.val), 2) * input.der;
    return output;
}

autodiff arcsin(autodiff input)
{
    autodiff output;
    output.val = asin(input.val);
    output.der = (1/sqrt(1 - pow(input.val, 2))) * input.der;
}
