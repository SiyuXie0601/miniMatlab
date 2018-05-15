#ifndef EQUATIONSOLUTION_H
#define EQUATIONSOLUTION_H


class EquationSolution
{
public:
    EquationSolution();
    static String solveLnrEqtnWithOneUkn(const String& exp);//解一元一次方程
    static String solveQdrtcEqtnWithOneUkn(const String& exp);//解一元二次方程
    static String solveCbcEqtnWithOneUkn(const String& exp);
    static String solveLnrEqtnWithTwoUkn(const String& exp);
};

#endif // EQUATIONSOLUTION_H
