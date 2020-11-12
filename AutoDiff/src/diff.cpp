#include "AutoDiff.h"
#include <math.h>

autodiff sin(autodiff input)
{
    autodiff output;
    output.val = sin(input.val);
    output.dv = cos(input.val) * input.dv
    return output;
}

autodiff cos(autodiff input)
{   
    autodiff output;
    output.val = cos(input.val);
    output.dv = -sin(input.val) * input.dv
    return output;
}

autodiff tan(autodiff input)
{
    autodiff output;
    output.val = tan(input.val);
    output.dv = (1/pow(cos(input.val), 2)) * input.dv;
    return output;
}

autodiff arcsin(autodiff input)
{
    autodiff output;
    output.val = asin(input.val);
    output.dv = (1/sqrt(1 - pow(input.val, 2))) * input.dv;
    return output;
}

autodiff arccos(autodiff input)
{
    autodiff output;
    output.val = acos(input.val);
    output.dv = -(1/sqrt(1 - pow(input.val, 2))) * input.dv;
    return output;
}

autodiff arctan(autodiff input)
{
    autodiff output;
    output.val = atan(input.val);
    output.dv = (1/(1+pow(input.val, 2))) * input.dv;
    return output;
}

autodiff exp(autodiff input)
{
    autodiff output;
    output.val = exp(input.val);
    output.dv = exp(input.val) * input.dv;
    return output;
}

autodiff log(autodiff input)
{
    autodiff output;
    output.val = log(input.val);
    output.dv = (1/input.val) * input.dv;
    return output;
}

autodiff pow(autodiff input, double exponent)
{
    autodiff output;
    output.val = pow(input.val, exponent);
    output.dv = exponent * pow(input.val, exponent - 1) * input.dv;
    return output;
}

autodiff sinh(autodiff input)
{
    autodiff output;
    output.val = sinh(input.val);
    output.dv = cosh(input.val) * input.dv;
    return output;
}

autodiff cosh(autodiff input)
{
    autodiff output;
    output.val = cosh(input.val);
    output.dv = sinh(input.va) * input.dv;
    return output;
}

autodiff tanh(autodiff input)
{
    autodiff output;
    output.val = tanh(input.val);
    output.dv = (1/pow(cosh(input.val), 2)) * input.dv;
    return output;
}
