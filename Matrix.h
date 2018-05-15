#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
private:
    double* _items;
    int _colNum;
    int _rowNum;
public:
    Matrix(const vector &mtrxItems, int col, int row);
    Matrix(int col, int row);
    int getRowNum() const;
    int getColNum() const;
    double  get(int i, int j) const;
    void set(int i, int j, double val);
    friend Matrix operator +(const Matrix &m1, const Matrix &m2);
    friend Matrix operator -(const Matrix &m1, const Matrix &m2);
    friend Matrix operator *(const Matrix &m1, const Matrix &m2);
    friend Matrix operator *(double f, const Matrix &m);
    friend Matrix operator *(const Matrix &m, double f);
    String toString() const;
};

#endif // MATRIX_H
