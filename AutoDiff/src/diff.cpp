#include "AutoDiff.h"
#include <math.h>

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
    output.der = (1/pow(cos(input.val), 2)) * input.der;
    return output;
}

autodiff arcsin(autodiff input)
{
    autodiff output;
    output.val = asin(input.val);
    output.der = (1/sqrt(1 - pow(input.val, 2))) * input.der;
    return output;
}

autodiff arccos(autodiff input)
{
    autodiff output;
    output.val = acos(input.val);
    output.der = -(1/sqrt(1 - pow(input.val, 2))) * input.der;
    return output;
}

autodiff arctan(autodiff input)
{
    autodiff output;
    output.val = atan(input.val);
    output.der = (1/(1+pow(input.val, 2))) * input.der;
    return output;
}

autodiff exp(autodiff input)
{
    autodiff output;
    output.val = exp(input.val);
    output.der = exp(input.val) * input.der;
    return output;
}

autodiff log(autodiff input)
{
    autodiff output;
    output.val = log(input.val);
    output.der = (1/input.val) * input.der;
    return output;
}

autodiff pow(autodiff input, double exponent)
{
    autodiff output;
    output.val = pow(input.val, exponent);
    output.der = exponent * pow(input.val, exponent - 1) * input.der;
    return output;
}

autodiff sinh(autodiff input)
{
    autodiff output;
    output.val = sinh(input.val);
    output.der = cosh(input.val) * input.der;
    return output;
}

autodiff cosh(autodiff input)
{
    autodiff output;
    output.val = cosh(input.val);
    output.der = sinh(input.va) * input.der;
    return output;
}

autodiff tanh(autodiff input)
{
    autodiff output;
    output.val = tanh(input.val);
    output.der = (1/pow(cosh(input.val), 2)) * input.der;
    return output;
}
