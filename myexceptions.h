#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H
#include <exception>
#include <string>
using namespace std;


class myexception : public exception {
public :
  myexception(string s){
    msg = s;
  }
  virtual const char *what() const noexcept{
    return msg.c_str();
  }
private:
  string msg;
};

#endif // MYEXCEPTIONS_H
