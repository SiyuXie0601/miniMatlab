#ifndef EQUATIONSOLUTION_H
#define EQUATIONSOLUTION_H
#include <string>
using namespace std;
/*将解以逗号方式隔开，最后一个解后加逗号，如果无解输出"No Solution"*/
class EquationSolution
{
public:
    EquationSolution();
    static string solveLnrEqtnWithOneUkn(const string& exp);//解一元一次方程,如"x=1"
    static string solveQdrtcEqtnWithOneUkn(const string& exp);//解一元二次方程,如"x=1+2i,1-2i"
    static string solveCbcEqtnWithOneUkn(const string& exp);//解一元三次方程
    static string solveLnrEqtnWithMultiUkn(const string& exp);//解多元一次方程,如"x=1,y=2"
};

#endif // EQUATIONSOLUTION_H
