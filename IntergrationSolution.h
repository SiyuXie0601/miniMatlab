#ifndef INTERGRATIONSOLUTION_H
#define INTERGRATIONSOLUTION_H


class IntergrationSolution
{
public:
    IntergrationSolution();
    static double integrate(const String &eqtn, const String &var, double bgn, double end);
    static QImage drawCurve(const String &eqtn);
};

#endif // INTERGRATIONSOLUTION_H
