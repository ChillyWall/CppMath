#ifndef MATRIX_H_
#define MATRIX_H_ 1

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <exception>

struct MatrixShape {
    size_t m;  // 矩阵行数
    size_t n;  // 矩阵列数
};

template <typename T>
class Matrix {
    private:
    template <typename Tp>
    using ptr = std::unique_ptr<Tp>;
    typedef std::initializer_list<T> ild;
    typedef std::vector<T> vd;
    typedef ptr<T* []> pd;

    size_t m_;
    size_t n_;
    size_t size_;

    pd data_;

    void length_check(size_t n) const;
    void shape_check1(const MatrixShape& sh) const;

    public:
    Matrix() { m_ = 0; n_ = 0; size_ = 0; data_ = pd(); }
    Matrix(size_t m, size_t n);
    Matrix(size_t m, size_t n, ild data);
    Matrix(size_t m, size_t n, T filling);
    Matrix(const Matrix<T>& M);
    ~Matrix() { data_.release(); }

    void set(ild data);
    void set(vd data);
    void fill(const T& filling);

    size_t m() const { return m_; }
    size_t n() const { return n_; }
    MatrixShape shape() const {
        MatrixShape s = { m_, n_ };
        return s;
    }

    size_t size() const { return size_; }

    Matrix<T> inverse() const;
    T det() const;
    int rank() const;

    T& operator()(size_t i, size_t j);
    Matrix<T>& operator=(const Matrix<T>& M);
    Matrix<T>& operator=(Matrix<T>&& M);

    Matrix<T> operator+(const Matrix<T>& M) const;
    Matrix<T> operator-(const Matrix<T>& M) const;
    Matrix<T> operator*(const Matrix<T>& M) const;
    Matrix<T> operator*(T c) const;

    Matrix<T>& operator+=(const Matrix<T>& M);
    Matrix<T>& operator-=(const Matrix<T>& M);
    Matrix<T>& operator*=(T c);

    Matrix<T> transpose() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T>& M);

template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T>&& M);

template <typename T>
Matrix<T> rand_int_matrix(size_t m, size_t n);
template <typename T>
Matrix<T> rand_real_matrix(size_t m, size_t n);

template <typename T>
Matrix<T> diag_matrix(size_t n, std::vector<T>& data);

template <typename T>
struct LU_comp {
    Matrix<T> L;
    Matrix<T> U;
};

template <typename T>
LU_comp<T> LU(const Matrix<T>& A);

template <typename T>
struct LDU_comp {
    Matrix<T> L;
    std::vector<T> D;
    Matrix<T> U;
};

template <typename T>
LDU_comp<T> LDU(const Matrix<T>& A);

template <typename T>
struct PLU_comp {
    std::vector<size_t> P;
    Matrix<T> L;
    Matrix<T> U;
};

template <typename T>
PLU_comp<T> PLU(const Matrix<T>& A);

template <typename T>
Matrix<T> exchange_rows(std::vector<size_t> P, Matrix<T>& M);

template <typename T>
inline T abs(const T& n) {
    return n < 0 ? (-n) : n;
}

template <typename T>
Matrix<T> inverse(Matrix<T> M);

template <typename T>
T det(Matrix<T> M);

template <typename T>
int rank(Matrix<T> M);

template <typename T>
inline bool if_square(Matrix<T> A) {
    return A.m() == A.n();
}

template <typename T>
Matrix<T> solve(Matrix<T> A, Matrix<T> b);

#include "Matrix.cpp.impl"

#endif