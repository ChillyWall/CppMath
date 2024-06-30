#ifndef REAL_H_
#define REAL_H_ 1

#include <iostream>
#include "Integer.h"
#include <cctype>
#include <algorithm>

class Real {
    private:
    Integer num_;
    long long point_ = 0;
    void remove_zeros() {
        while (num_.size() > 1 && num_.nums_.front() == 0) {
            num_.nums_.pop_front();
        }
        if (num_.nums_.size() == 1 && if_zero()) {
            point_ = 0;
            num_.sign_ = true;
        }
    }

    void add_zeros(size_t num_of_zeros) {
        num_.append_zeros(num_of_zeros);
    }

    bool if_zero() const {
        return num_.if_zero();
    }


    public:
    static long long default_precision;
    Real() {
        num_ = Integer();
    }

    ~Real() {}
    explicit Real(int num, long long point = 0) {
        *this = Real(std::to_string(num), point);
    }

    explicit Real(long long num, long long point = 0) {
        *this = Real(std::to_string(num), point);
    }

    explicit Real(long double num, long long point = 0) {
        *this = Real(std::to_string(num), point);
    }

    explicit Real(double num, long long point = 0) {
        *this = Real(std::to_string(num), point);
    }

    explicit Real(const char* str_num, long long point = 0) {
        *this = Real(std::string(str_num), point);
    }

    explicit Real(const std::string& str, long long point = 0);

    Real(const Integer& i) : point_ {0} {
        num_ = i;
    }

    Real(Integer&& i) noexcept : point_ {0} {
        num_ = std::move(i);
    }

    Real(const Real& num) : num_ { num.num_ }, point_ { num.point_ } {}

    Real(Real&& num) noexcept : num_ { std::move(num.num_) }, point_ { num.point_ } {}

    size_t size() const {
        return num_.size();
    }

    bool positive() const {
        return num_.positive();
    }

    short operator[](long long index) const {
        if (index <= point_ && index > point_ - (long long) size()) {
            return num_[index + size() - 1 - point_];
        } else {
            return 0;
        }
    }

    void round(long long digits);

    Real& operator=(long long num) {
        *this = Real(std::to_string(num));
        return *this;
    }

    Real& operator=(int num) {
        *this = Real(std::to_string(num));
        return *this;
    }

    Real& operator=(const char* str_num) {
        *this = Real(std::string(str_num));
        return *this;
    }

    Real& operator=(const std::string& str_num) {
        *this = Real(str_num);
        return *this;
    }

    Real& operator=(double num) {
        *this = Real(num);
        return *this;
    }

    Real& operator=(long double num) {
        *this = Real(num);
        return *this;
    }

    Real& operator=(const Real& num) {
        num_ = num.num_;
        point_ = num.point_;
        return *this;
    }

    Real& operator=(Real&& num) noexcept {
        num_ = std::move(num.num_);
        point_ = num.point_;
        return *this;
    }

    Real& operator=(Integer&& num) noexcept {
        point_ = 0;
        num_ = std::move(num);
    }

    Real& operator=(const Integer& num) {
        point_ = 0;
        num_ = num;
    }

    Real abs() const {
        Real abs_num = *this;
        abs_num.num_ = num_.abs();
        return abs_num;
    }

    friend Real operator+(const Real& a, const Real& b);
    friend Real operator-(const Real& a, const Real& b);
    friend Real operator*(const Real& a, const Real& b);
    friend Real operator/(const Real& a, const Real& b);

    friend Real operator-(const Real& a) {
        Real minus_a = a;
        minus_a.num_ = -a.num_;
        return minus_a;
    }

    Real& operator+=(const Real& a) {
        *this = *this + a;
        return *this;
    }

    Real& operator+=(Real&& a) {
        *this = *this + a;
        return *this;
    }

    Real& operator-=(const Real& a) {
        *this = *this - a;
        return *this;
    }

    Real& operator*=(const Real& a) {
        *this = *this * a;
        return *this;
    }

    Real& operator/=(const Real& a) {
        *this = *this / a;
        return *this;
    }

    friend bool operator>(const Real& a, const Real& b);
    friend bool operator==(const Real& a, const Real& b);

    friend bool operator<(const Real& a, const Real& b) {
        return !(a > b || a == b);
    }

    friend bool operator!=(const Real& a, const Real& b) {
        return !(a == b);
    }

    friend bool operator>=(const Real& a, const Real& b) {
        return !(a < b);
    }

    friend bool operator<=(const Real& a, const Real& b) {
        return !(a > b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Real& num);
};

#endif