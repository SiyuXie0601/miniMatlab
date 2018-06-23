#ifndef FUNCTION1_H
#define FUNCTION1_H
#include <string>
using namespace std;

class function1 {
public:
    function1(const char* string);
    double getnum(string s);
    void getinformation();

    void setx(int p, int a);
    double* getfunc();
    int length();
    void print();
    double* getcfunc();
    void calculous();

private:
    char* text;
    int max;
    double *func;
    double *calfunc;
};

#endif // FUNCTION1_H
