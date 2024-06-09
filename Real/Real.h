#ifndef REAL_H_
#define REAL_H_ 1

#include <iostream>
#include "../Integer/Integer.h"

class Real {
private:
    Integer num_;
    long long point_;
public:
    Real() {
        num_ = Integer();
        point_ = 0;
    }

    ~Real() {}

    explicit Real(long long num) {
        num_ = Integer();
        *this = Real(std::to_string(num));
    }

    explicit Real(const char* str_num) {
        num_ = Integer();
        *this = Real(std::string(str_num));
    }

    explicit Real(const std::string& str);

    size_t size() const {
        return num_.size();
    }

    bool positive() {
        return num_.positive();
    }

    short operator[](long long index) const {
        if (point_ + size() - 1 <= index <= point_) {
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
    friend Real operator%(const Real& a, const Real& b);

    friend Real operator-(const Real& a) {
        Real minus_a = a;
        minus_a.num_ = -a.num_;
        return minus_a;
    }

    Real& operator+=(Real a);
    Real& operator-=(Real a);
    Real& operator*=(Real a);
    Real& operator/=(Real a);
    Real& operator%=(Real a);

    friend bool operator>(const Real& a, const Real& b);
    friend bool operator<(const Real& a, const Real& b) {
        return not (a > b or a == b);
    }
    friend bool operator==(const Real& a, const Real& b);
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