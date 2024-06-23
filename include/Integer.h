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
    bool sign_ = true; // 0 is negative and 1 is positive

    void remove_zeros() {
        while (nums_.size() > 1 && nums_.back() == 0) {
            nums_.pop_back();
        }
        if (nums_.size() == 1 && nums_.back() == 0) {
            sign_ = true;
        }
    }

    bool if_zero() const {
        return nums_.size() == 1 && nums_.back() == 0;
    }

    void append_zeros(size_t num_of_zeros) {
        nums_.insert(nums_.begin(), num_of_zeros, 0);
    }

    Integer multiply_single(short opnd) const;

public:
    Integer() {}

    ~Integer() {}

    explicit Integer(long long num) {
        *this = Integer(std::to_string(num));
    }

    explicit Integer(int num) {
        *this = Integer(std::to_string(num));
    }

    explicit Integer(const char* str_num) {
        *this = Integer(std::string(str_num));
    }

    explicit Integer(const std::string& str);

    Integer(const Integer& num) : nums_{ num.nums_ }, sign_{ num.sign_ } {}

    Integer(Integer&& num) noexcept : sign_{ num.sign_ } {
        nums_ = std::move(num.nums_);
    }

    size_t size() const {
        return nums_.size();
    }

    bool positive() const {
        return sign_;
    }

    short operator[](size_t index) const {
        if (index < nums_.size()) {
            return nums_[index];
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
        nums_ = num.nums_;
        sign_ = num.sign_;
        return *this;
    }

    Integer& operator=(Integer&& num) noexcept {
        nums_ = std::move(num.nums_);
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
        minus_a.sign_ = !a.sign_;
        return minus_a;
    }

    Integer& operator+=(const Integer& a) {
        *this = *this + a;
        return *this;
    }

    Integer& operator-=(const Integer& a) {
        *this = *this - a;
        return *this;
    }

    Integer& operator*=(const Integer& a) {
        *this = *this * a;
        return *this;
    }

    Integer& operator/=(const Integer& a) {
        *this = *this / a;
        return *this;
    }

    Integer& operator%=(const Integer& a) {
        *this = *this % a;
        return *this;
    }

    friend bool operator>(const Integer& a, const Integer& b);
    friend bool operator<(const Integer& a, const Integer& b) {
        return !(a > b || a == b);
    }
    friend bool operator==(const Integer& a, const Integer& b);
    friend bool operator!=(const Integer& a, const Integer& b) {
        return !(a == b);
    }
    friend bool operator>=(const Integer& a, const Integer& b) {
        return !(a < b);
    }
    friend bool operator<=(const Integer& a, const Integer& b) {
        return !(a > b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Integer& num);

    friend class Real;
};


#endif