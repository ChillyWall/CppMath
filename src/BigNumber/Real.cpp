#include "Real.h"
long long Real::default_precision = 10;

Real::Real(const std::string& str, long long point) {
    num_ = Integer(str);
    while (num_.nums_.back() == 0 && num_.nums_.size() > 1) {
        num_.nums_.pop_back();
    }

    long long first_num = 0;
    long long pt = 0;
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
    round(-Real::default_precision);
}

void Real::round(long long digits) {
    long long dist = point_ - (long long)size() + 1 - digits;
    if (dist < 0LL) {
        while (dist < -1) {
            if (num_.nums_.size() == 1) {
                num_.nums_.front() = 0;
                point_ = 0;
                return ;
            }
            num_.nums_.pop_front();
            dist++;
        }

        bool if_carry = false;
        if (num_.nums_.front() == 5) {
            if (num_.nums_[1] % 2 == 1) {
                if_carry = true;
            }
        } else if (num_.nums_.front() > 5) {
            if_carry = true;
        }
        if (num_.nums_.size() > 1) {
            num_.nums_.pop_front();
        } else if (num_.nums_.size() == 1) {
            num_.nums_.front() = 0;
            if (!if_carry) {
                point_ = 0;
            }   
        }

        if (if_carry) {
            num_ += num_.positive() ? Integer(1) : -Integer(1);
        }
    }
    remove_zeros();
}

Real operator+(const Real& a, const Real& b) {
    if (a.if_zero()) {
        return b;
    } else if (b.if_zero()) {
        return a;
    }
    Real res;
    long long a_beg;
    long long b_beg;
    long long step;
    a_beg = a.point_ - a.size() + 1;
    b_beg = b.point_ - b.size() + 1;
    if (a_beg > b_beg) {
        step = a_beg - b_beg;
        res = a;
        res.add_zeros(step);
        res.num_ += b.num_;
        res.point_ += res.size() - a.size() - step;
    } else if (a_beg < b_beg) {
        step = b_beg - a_beg;
        res = b;
        res.add_zeros(step);
        res.num_ += a.num_;
        res.point_ += res.size() - b.size() - step;
    } else {
        res.num_ = a.num_ + b.num_;
        res.point_ = res.size() - a.size() + a.point_;
    }
    res.round(-Real::default_precision);
    return res;
}

Real operator-(const Real& a, const Real& b) {
    if (a.if_zero()) {
        return -b;
    } else if (b.if_zero()) {
        return a;
    }
    Real res;
    long long a_beg;
    long long b_beg;
    long long step;
    a_beg = a.point_ - a.size() + 1;
    b_beg = b.point_ - b.size() + 1;
    if (a_beg > b_beg) {
        step = a_beg - b_beg;
        res = a;
        res.add_zeros(step);
        res.num_ -= b.num_;
        res.point_ += res.size() - a.size() - step;
    } else if (a_beg < b_beg) {
        step = b_beg - a_beg;
        res = b;
        res.add_zeros(step);
        res.num_ = a.num_ - res.num_;
        res.point_ += res.size() - b.size() - step;
    } else {
        res.num_ = a.num_ - b.num_;
        res.point_ = res.size() - a.size() + a.point_;
    }
    res.round(-Real::default_precision);
    return res;
}

Real operator*(const Real& a, const Real& b) {
    Real res;
    res.num_ = a.num_ * b.num_;
    res.point_ = a.point_ + b.point_ + (long long)(res.size() - a.size() - b.size()) + 1LL;
    res.round(-Real::default_precision);
    return res;
}

Real operator/(const Real& a, const Real& b) {
    if (b.if_zero()) {
        throw std::invalid_argument("b should not be 0.");
    }
    if (a.if_zero()) {
        return Real(0);
    }
    Real res(a);
    long long dist = a.point_ - b.point_ - (long long)a.size() + Real::default_precision + (long long)b.size() + 2;
    if (dist > 0LL) {
        res.add_zeros(dist);
    } else {
        res.round(-Real::default_precision - 2);
    }

    long long diff = res.size() - b.size() + 1;
    res.num_ /= b.num_;
    diff -= res.size();
    res.point_ -= b.point_ + diff;
    res.round(-Real::default_precision);
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
    long long beg;
    long long stop;
    beg = std::max(0LL, num.point_);
    stop = std::min(0LL, num.point_ - (long long) num.size() + 1);
    for (long long i = beg; i >= stop; i--) {
        std::cout << num[i];
        if (i == 0 && i != stop) {
            std::cout << '.';
        }
    }
    return os;
}