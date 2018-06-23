#include "function1.h"
#include <iostream>
#include <string.h>
#include <sstream>

    using namespace std ;
    function1::function1(const char* string) {
        func = new double[101];
        calfunc = new double[102];
        int length = strlen(string)+1;
        text = new char[length];
        strcpy(text, string);
        getinformation();
        calculous();
    }

    double function1::getnum(string s) {
        double num = -1;
        stringstream ss(s);
        ss >> num;
        if(s.at(0) == '-' && (s.at(1)<'0' || s.at(1)>'9'))
            num = -1;
        return num;
    }

    void function1::getinformation() {
        bool haspow = false,
            skipthisnum = false,
            hasx = false;
        int top = -1;
        double stack[3] = { 0 };
        max = 0;
        char*p = text;
        while (*p) {
            if (*p == '+'||*p == '-') {
                if (haspow && hasx && top == 1) {
                    func[(int)stack[1]] += stack[0];
                    max = (int)stack[1] > max ? (int)stack[1] : max;
                }
                else if (haspow && hasx && top == 0) {
                    func[(int)stack[0]] += 1;
                    max = (int)stack[0] > max ? (int)stack[0] : max;
                }
                else if (!haspow && hasx && top == 0) {
                    func[1] += stack[0];
                    max = 1 > max ? 1 : max;
                }
                else if (!haspow && hasx && top == -1) {
                    func[1] += 1;
                    max = 1 > max ? 1 : max;
                }
                else if (!haspow && !hasx && top == 0) {
                    func[0] += stack[0];
                    max = 0 > max ? 0 : max;
                }
                top = -1;
                haspow = false,
                skipthisnum = false,
                hasx = false;
                if (*p == '-') {
                    stack[++top] = getnum(p);
                    skipthisnum = true;
                }
            }
            else if (!skipthisnum && (*p >= '0' && *p <= '9')) {
                stack[++top] = getnum(p);
                skipthisnum = true;
            }
            else if ((*p == '^')) {
                skipthisnum = false;
                haspow = true;
            }
            else if ((*p == 'x')) {
                skipthisnum = false;
                hasx = true;
            }
            else if(*p < '0' && *p > '9') {
                skipthisnum = false;
            }
            p++;
        }
        if (haspow && hasx && top == 1) {
            func[(int)stack[1]] += stack[0];
            max = (int)stack[1] > max ? (int)stack[1] : max;
        }
        else if (haspow && hasx && top == 0) {
            func[(int)stack[0]] += 1;
            max = (int)stack[0] > max ? (int)stack[0] : max;
        }
        else if (!haspow && hasx && top == 0) {
            func[1] += stack[0];
            max = 1 > max ? 1 : max;
        }
        else if (!haspow && hasx && top == -1) {
            func[1] += 1;
            max = 1 > max ? 1 : max;
        }
        else if (!haspow && !hasx && top == 0) {
            func[0] += stack[0];
            max = 0 > max ? 0 : max;
        }

    }

    void function1::setx(int p, int a) {
        func[p] = a;
        return;
    }
    double* function1::getfunc() {
        return func;
    }
    int function1::length() {
        return max;
    }
    void function1::print() {
        int i;
        for (int i = 0; i < 6; i++) {
            if (func[i])
                cout << func[i] << ' ';
            else
                printf("%d ", func[i]);
        }
        cout << endl;
    }
    double* function1::getcfunc() {
        return calfunc;
    }
    void function1::calculous() {

        for (int i = 0; i <= max; i++) {
            calfunc[i+1] = func[i]/(1.0*(i+1));
        }
        calfunc[0] = max + 1;

        return;
    }


