#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <string>
using namespace std;



class Matrix
{
private:
    double* _items;//以一维数组形式储存二维数组，矩阵第i行第j个元素(0<=i<_rowNum,0<=j<_colNum)的地址为&_items+(i*_colNum+j)*sizeof(double)
    int _colNum;
    int _rowNum;
public:
    Matrix(const QStringList &mtrxItems, int col, int row);//矩阵第i行第j个元素(0<=i<_rowNum,0<=j<_colNum)在mtrxItems中为第(i*_colNum+j)个元素(从第0个元素算起)
    Matrix(int col, int row);//将矩阵中中所有元素初始化为0
    int getRowNum() const;
    int getColNum() const;
    double  get(int i, int j) const;
    void set(int i, int j, double val);
    friend Matrix operator +(const Matrix &m1, const Matrix &m2);//矩阵m1与m2相加
    friend Matrix operator -(const Matrix &m1, const Matrix &m2);//矩阵m1与m2相减
    friend Matrix operator *(const Matrix &m1, const Matrix &m2);//矩阵m1与m2相乘
    friend Matrix operator *(double f, const Matrix &m);//矩阵m与实数f相乘
    friend Matrix operator *(const Matrix &m, double f);//矩阵m与实数f相乘
    string toString() const;//元素与元素之间用逗号隔开，行与行之间用分号隔开(最后一行后不需要分号)，例如 "1,2.5,3;3.7,4,8;2,9,100"
};

#endif // MATRIX_H
