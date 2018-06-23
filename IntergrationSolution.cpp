#include "IntergrationSolution.h"
#include "function1.h"

IntergrationSolution::IntergrationSolution()
{

}

double IntergrationSolution::integrate(const QString &eqtn, double bgn, double end)
{
    string tempstring = eqtn.toStdString();
    const char* express = tempstring.c_str();
    function1 test(express);

    double* integral = test.getcfunc();
    double y1 = 0, y2 = 0;
    for(int j = 1; j <= integral[0]; j++){
           y1 += integral[j]*pow(bgn,j);
           y2 += integral[j]*pow(end,j);
        }
    double result = y2 - y1;
    return result;
}
