#ifndef REAL_H
#define REAL_H


class Real
{
private:
    double _real;
    double _image;
public:
    Real(int r, int i);
    String toString() const;
};

#endif // REAL_H
