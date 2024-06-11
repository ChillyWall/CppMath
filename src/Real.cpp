#include "Real.h"

size_t Real::default_adding_digits = 10;

Real::Real(const std::string& str, long long point) {
    num_ = Integer(str);
    while (num_.nums_.back() == 0 and num_.nums_.size() > 1) {
        num_.nums_.pop_back();
    }

    long long first_num, pt = 0;
    long long posi = 0;
    bool has_first_num = false;
    bool has_point = false;
    auto itr = str.begin();
    while (itr < str.end()) {
        if (std::isdigit(*itr)) {
            if ((!has_first_num) && *itr != '0') {
                first_num = posi;
                has_first_num = true;
            }
            posi++;
        } else if ((!has_point) && *itr == '.') {
            pt = posi - 1;
            has_point = true;
        }
        itr++;
    }
    if (has_point == false) {
        pt = posi - 1;
    }
    remove_zeros();
    point_ = pt - first_num + point;
}

void Real::move_point(size_t step) {
    num_.nums_.insert(num_.nums_.begin(), step, 0);
}

Real operator+(const Real& a, const Real& b) {
    Real res;
    long long a_beg, b_beg, step;
    a_beg = a.point_ - a.size() + 1;
    b_beg = b.point_ - b.size() + 1;
    if (a_beg > b_beg) {
        step = a_beg - b_beg;
        res = a;
        res.move_point(step);
        res.num_ += b.num_;
        res.point_ += res.size() - a.size() - step;
        res.remove_zeros();
    } else if (a_beg < b_beg) {
        step = b_beg - a_beg;
        res = b;
        res.move_point(step);
        res.num_ += a.num_;
        res.point_ += res.size() - b.size() - step;
        res.remove_zeros();
    } else {
        res.num_ = a.num_ + b.num_;
        res.point_ = res.size() - a.size() + a.point_;
        res.remove_zeros();
    }
    return res;
}

Real operator-(const Real& a, const Real& b) {
    Real res;
    long long a_beg, b_beg, step;
    a_beg = a.point_ - a.size() + 1;
    b_beg = b.point_ - b.size() + 1;
    if (a_beg > b_beg) {
        step = a_beg - b_beg;
        res = a;
        res.move_point(step);
        res.num_ -= b.num_;
        res.point_ += res.size() - a.size() - step;
        res.remove_zeros();
    } else if (a_beg < b_beg) {
        step = b_beg - a_beg;
        res = b;
        res.move_point(step);
        res.num_ -= a.num_;
        res.point_ += res.size() - b.size() - step;
        res.remove_zeros();
    } else {
        res.num_ = a.num_ - b.num_;
        res.point_ = res.size() - a.size() + a.point_;
        res.remove_zeros();
    }
    return res;
}

Real operator*(const Real& a, const Real& b) {
    Real res;
    res.num_ = a.num_ * b.num_;
    res.point_ = a.point_ + b.point_;
    res.remove_zeros();
    return res;
}

Real operator/(const Real& a, const Real& b) {
    Real res(a);
    res.move_point(a.default_adding_digits);
    res.num_ /= b.num_;
    res.point_ += b.point_;
    res.remove_zeros();
    return res;
}

bool operator==(const Real& a, const Real& b) {
    bool res = true;
    if (a.num_ != b.num_ || a.point_ != b.point_) {
        res = false;
    }

    return res;
}

bool operator>(const Real& a, const Real& b) {
    bool res = false;
    if (a.num_.positive() != b.num_.positive()) {
        res = a.num_.positive();
        if (a.if_zero() && b.if_zero()) {
            res = false;
        }
    } else if (a.point_ > b.point_) {
        res = a.num_.positive();
    } else if (a.point_ < b.point_) {
        res = !a.num_.positive();
    } else {
        for (size_t i = 0; i < a.num_.size(); i++) {
            short num1 = a[a.point_ - i];
            short num2 = b[a.point_ - i];
            if (num1 > num2) {
                res = a.positive();
                break;
            } else if (num1 < num2) {
                res = !a.positive();
                break;
            }
        }
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Real& num) {
    if (!(num.positive() || num.if_zero())) {
        os << '-';
    }
    long long beg, stop;
    beg = std::max(0ll, num.point_);
    stop = std::min(0ll, num.point_ - (long long)num.size() + 1);
    for (long long i = beg; i >= stop; i--) {
        std::cout << num[i];
        if (i == 0 && i != stop) {
            std::cout << '.';
        }
    }
    return os;
}