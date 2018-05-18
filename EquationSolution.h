#ifndef EQUATIONSOLUTION_H
#define EQUATIONSOLUTION_H

/*将解以逗号方式隔开，最后一个解后加逗号，如果无解输出"No Solution"*/
class EquationSolution
{
public:
    EquationSolution();
    static String solveLnrEqtnWithOneUkn(const String& exp);//解一元一次方程,如"x=1"
    static String solveQdrtcEqtnWithOneUkn(const String& exp);//解一元二次方程,如"x=1+2i,1-2i"
    static String solveCbcEqtnWithOneUkn(const String& exp);//解一元三次方程
    static String solveLnrEqtnWithMultiUkn(const String& exp);//解多元一次方程,如"x=1,y=2"
};

#endif // EQUATIONSOLUTION_H
