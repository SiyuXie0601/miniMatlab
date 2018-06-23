#ifndef REAL_H
#define REAL_H
#include <string>
using namespace std;
class Real
{
private:
    double _real;
    double _image;
public:
    Real(double r, double i);
    string toString() const;//字符串形式为例如"1.2+5.9i"
};

#endif // REAL_H
