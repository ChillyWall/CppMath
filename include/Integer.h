#ifndef INTEGER_H_
#define INTEGER_H_ 1
#include <deque>
#include <string>
#include <cctype>
#include <iostream>
#include <iterator>

class Integer {
private:
    std::deque<short> nums_;
    bool sign_; // 0 is negative and 1 is positive

    void remove_zeros() {
        while (nums_.size() > 1 and nums_.back() == 0) {
            nums_.pop_back();
        }
    }

    bool if_zero() const {
        bool res = false;
        if (nums_.size() == 1 && nums_.back() == 0) {
            res = true;
        }
        return res;
    }

public:
    Integer() {
        nums_ = std::deque<short>();
        sign_ = true;
    }

    ~Integer() {}

    explicit Integer(long long num) {
        nums_ = std::deque<short>();
        *this = Integer(std::to_string(num));
    }

    explicit Integer(const char* str_num) {
        nums_ = std::deque<short>();
        *this = Integer(std::string(str_num));
    }

    explicit Integer(const std::string& str);

    size_t size() const {
        return nums_.size();
    }

    bool positive() const {
        return sign_;
    }

    short operator[](size_t index) const {
        if (index < nums_.size()) {
            return (nums_)[index];
        } else {
            return 0;
        }
    }

    Integer& operator=(long long num) {
        *this = Integer(std::to_string(num));
        return *this;
    }

    Integer& operator=(const char* str_num) {
        *this = Integer(std::string(str_num));
        return *this;
    }

    Integer& operator=(const std::string& str_num) {
        *this = Integer(str_num);
        return *this;
    }

    Integer& operator=(const Integer& num) {
        nums_ = std::deque<short>(num.nums_);
        sign_ = num.sign_;
        return *this;
    }

    Integer abs() const {
        Integer abs_num = *this;
        abs_num.sign_ = true;
        return abs_num;
    }

    friend Integer operator+(const Integer& a, const Integer& b);
    friend Integer operator-(const Integer& a, const Integer& b);
    friend Integer operator*(const Integer& a, const Integer& b);
    friend Integer operator/(const Integer& a, const Integer& b);

    friend Integer operator%(const Integer& a, const Integer& b) {
        return a - (a / b) * b;
    }

    friend Integer operator-(const Integer& a) {
        Integer minus_a = a;
        minus_a.sign_ = not a.sign_;
        return minus_a;
    }

    Integer& operator+=(Integer a) {
        *this = *this + a;
        return *this;
    }

    Integer& operator-=(Integer a) {
        *this = *this - a;
        return *this;
    }

    Integer& operator*=(Integer a) {
        *this = *this * a;
        return *this;
    }

    Integer& operator/=(Integer a) {
        *this = *this / a;
        return *this;
    }

    Integer& operator%=(Integer a) {
        *this = *this % a;
        return *this;
    }

    friend bool operator>(const Integer& a, const Integer& b);
    friend bool operator<(const Integer& a, const Integer& b) {
        return not (a > b or a == b);
    }
    friend bool operator==(const Integer& a, const Integer& b);
    friend bool operator!=(const Integer& a, const Integer& b) {
        return not (a == b);
    }
    friend bool operator>=(const Integer& a, const Integer& b) {
        return not (a < b);
    }
    friend bool operator<=(const Integer& a, const Integer& b) {
        return not (a > b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Integer& num);

    friend class Real;
};


#endif