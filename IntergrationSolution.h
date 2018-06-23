#ifndef INTERGRATIONSOLUTION_H
#define INTERGRATIONSOLUTION_H
#include <QString>
#include <string>

using namespace std;
class IntergrationSolution
{
public:
    IntergrationSolution();
    static double integrate(const QString &eqtn, double bgn, double end);//给定曲线表达式eqtn,自变量var,开始区间bgn,结束区间end,求定积分
};

#endif // INTERGRATIONSOLUTION_H
