#ifndef INTERGRATIONSOLUTION_H
#define INTERGRATIONSOLUTION_H


class IntergrationSolution
{
public:
    IntergrationSolution();
    static double integrate(const String &eqtn, const String &var, double bgn, double end);//给定曲线表达式eqtn,自变量var,开始区间bgn,结束区间end,求定积分
    static QImage drawCurve(const String &eqtn);//给定曲线表达式eqtn,返回曲线图象
};

#endif // INTERGRATIONSOLUTION_H
