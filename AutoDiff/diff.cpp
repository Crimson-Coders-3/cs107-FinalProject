#include "AutoDiff.h"
#include <math.h>

AutoDiff sin(AutoDiff input)
{
    AutoDiff output;
    output.val = sin(input.val);
    output.dv = cos(input.val) * input.dv
    return output;
}

AutoDiff cos(AutoDiff input)
{   
    AutoDiff output;
    output.val = cos(input.val);
    output.dv = -sin(input.val) * input.dv
    return output;
}

AutoDiff tan(AutoDiff input)
{
    AutoDiff output;
    output.val = tan(input.val);
    output.dv = (1/pow(cos(input.val), 2)) * input.dv;
    return output;
}

AutoDiff arcsin(AutoDiff input)
{
    AutoDiff output;
    output.val = asin(input.val);
    output.dv = (1/sqrt(1 - pow(input.val, 2))) * input.dv;
    return output;
}

AutoDiff arccos(AutoDiff input)
{
    AutoDiff output;
    output.val = acos(input.val);
    output.dv = -(1/sqrt(1 - pow(input.val, 2))) * input.dv;
    return output;
}

AutoDiff arctan(AutoDiff input)
{
    AutoDiff output;
    output.val = atan(input.val);
    output.dv = (1/(1+pow(input.val, 2))) * input.dv;
    return output;
}

AutoDiff exp(AutoDiff input)
{
    AutoDiff output;
    output.val = exp(input.val);
    output.dv = exp(input.val) * input.dv;
    return output;
}

AutoDiff log(AutoDiff input)
{
    AutoDiff output;
    output.val = log(input.val);
    output.dv = (1/input.val) * input.dv;
    return output;
}

AutoDiff pow(AutoDiff input, double exponent)
{
    AutoDiff output;
    output.val = pow(input.val, exponent);
    output.dv = exponent * pow(input.val, exponent - 1) * input.dv;
    return output;
}

AutoDiff sinh(AutoDiff input)
{
    AutoDiff output;
    output.val = sinh(input.val);
    output.dv = cosh(input.val) * input.dv;
    return output;
}

AutoDiff cosh(AutoDiff input)
{
    AutoDiff output;
    output.val = cosh(input.val);
    output.dv = sinh(input.va) * input.dv;
    return output;
}

AutoDiff tanh(AutoDiff input)
{
    AutoDiff output;
    output.val = tanh(input.val);
    output.dv = (1/pow(cosh(input.val), 2)) * input.dv;
    return output;
}
