#ifndef REAL_H_
#define REAL_H_ 1

#include <iostream>
#include "Integer.h"
#include <cctype>
#include <algorithm>

class Real {
private:
    Integer num_;
    long long point_;
    void remove_zeros() {
        while (num_.size() > 1 and num_.nums_.front() == 0) {
            num_.nums_.pop_front();
        }
    }

    void move_point(size_t step);

    bool if_zero() const {
        bool res = false;
        if (num_ == Integer("0")) {
            res = true;
        }
        return res;
    }

    static size_t default_adding_digits;

public:
    Real() {
        num_ = Integer();
        point_ = 0;
    }

    ~Real() {}

    explicit Real(long long num, long long point = 0) {
        *this = Real(std::to_string(num), point);
    }

    explicit Real(const char* str_num, long long point = 0) {
        *this = Real(std::string(str_num), point);
    }

    explicit Real(const std::string& str, long long point = 0);

    size_t size() const {
        return num_.size();
    }

    bool positive() const {
        return num_.positive();
    }

    short operator[](long long index) const {
        if (point_ <= index < point_ + size()) {
            return num_[index + size() - 1 - point_];
        } else {
            return 0;
        }
    }

    Real& operator=(long long num) {
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

    Real& operator=(const Real& num) {
        num_ = num.num_;
        point_ = num.point_;
        return *this;
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

    Real& operator+=(Real a) {
        *this = *this + a;
        return *this;
    }

    Real& operator-=(Real a) {
        *this = *this - a;
        return *this;
    }

    Real& operator*=(Real a) {
        *this = *this * a;
        return *this;
    }

    Real& operator/=(Real a) {
        *this = *this / a;
        return *this;
    }

    friend bool operator>(const Real& a, const Real& b);
    friend bool operator==(const Real& a, const Real& b);

    friend bool operator<(const Real& a, const Real& b) {
        return not (a > b or a == b);
    }

    friend bool operator!=(const Real& a, const Real& b) {
        return not (a == b);
    }

    friend bool operator>=(const Real& a, const Real& b) {
        return not (a < b);
    }

    friend bool operator<=(const Real& a, const Real& b) {
        return not (a > b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Real& num);
};

#endif