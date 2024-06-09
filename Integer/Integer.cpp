#include "Integer.h"

Integer::Integer(const std::string& str) {
    nums_ = std::deque<short>();
    sign_ = true;
    for (auto itr = str.rbegin(); itr < str.rend(); itr++) {
        if (isdigit(*itr)) {
            nums_.push_back(*itr-48);
        } else if (*itr == '-') {
            sign_ = false;
        }
    }
    remove_zeros();
}

Integer operator+(const Integer& a, const Integer& b) {
    Integer res;
    if (a.sign_ == b.sign_) {
        short next = 0;
        for (size_t i = 0; i < a.size() or i < b.size(); i++) {
            short op1 = a[i];
            short op2 = b[i];
            short sum = op1 + op2 + next;
            if (sum >= 10) {
                next = 1;
                sum -= 10;
            } else {
                next = 0;
            }
            res.nums_.push_back(sum);
        }
        res.sign_ = a.sign_;
        if (next == 1)
            res.nums_.push_back(next);
    } else {
        short next = 0;
        Integer num1(a.abs());
        Integer num2(b.abs());
        if (num1 >= num2) {
            res = num1 - num2;
            res.sign_ = a.sign_;
        } else {
            res = num2 - num1;
            res.sign_ = b.sign_;
        }
    }
    return res;
}

Integer operator-(const Integer& a, const Integer& b) {
    Integer res;
    if (a.sign_ == b.sign_) {
        Integer num1(a.abs());
        Integer num2(b.abs());
        bool sign = a.sign_;
        if (num1 < num2) {
            Integer mid = num1;
            num1 = num2;
            num2 = mid;
            sign = not sign;
        }
        short next = 0;
        for (size_t i = 0; i < num1.size() or i < num2.size(); i++) {
            short op1 = num1[i], op2 = num2[i];
            short dif = op1 - op2 + next;
            if (dif < 0) {
                next = -1;
                dif += 10;
            } else {
                next = 0;
            }
            res.nums_.push_back(dif);
        }
        res.sign_ = sign;
    } else {
        res = a + (-b);
    }
    res.remove_zeros();
    return res;
}

Integer operator*(const Integer& a, const Integer& b) {
    Integer res;
    for (size_t i = 0; i < b.size(); i++) {
        short multiplier = b[i];
        Integer product1;
        short next = 0;
        for (size_t j = 0; j < a.size(); j++) {
            short product2 = a[j] * multiplier + next;
            next = product2 / 10;
            product2 %= 10;
            product1.nums_.push_back(product2);
        }
        if (next) {
            product1.nums_.push_back(next);
        }
        product1.nums_.insert(product1.nums_.begin(), i, 0);
        res += product1;
    }
    res.sign_ = a.sign_ == b.sign_;
    return res;
}

Integer operator/(const Integer& a, const Integer& b) {
    Integer res;
    if (b == Integer('0')) {
        std::cout << "Wrong, the b should not be 0." << std::endl;
        return res;
    }

    if (a.size() >= b.size()) {
        Integer num1(a), num2(b.abs());
        size_t begin_point = num1.size() - b.size();
        for (size_t i = 0; i <= begin_point; i++) {
            Integer opnd1;
            auto begin_itr = num1.nums_.begin() + begin_point - i;
            opnd1.nums_ = std::deque<short>(begin_itr, num1.nums_.end());

            short lo = 0, hi = 10;
            while (hi - lo > 1) {
                short mid = (lo + hi) / 2;
                if (num2 * Integer(mid) > opnd1) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            res.nums_.push_front(lo);

            opnd1 -= Integer(lo) * num2;
            num1.nums_.erase(begin_itr, num1.nums_.end());
            num1.nums_.insert(num1.nums_.end(), opnd1.nums_.begin(), opnd1.nums_.end());
        }
    } else {
        res = Integer('0');
    }
    res.remove_zeros();
    res.sign_ = a.sign_ == b.sign_;
    return res;
}

Integer operator%(const Integer& a, const Integer& b) {
    return a - (a / b) * b;
}

Integer& Integer::operator+=(Integer a) {
    *this = *this + a;
    return *this;
}

Integer& Integer::operator-=(Integer a) {
    *this = *this - a;
    return *this;
}

Integer& Integer::operator*=(Integer a) {
    *this = *this * a;
    return *this;
}

Integer& Integer::operator/=(Integer a) {
    *this = *this / a;
    return *this;
}

Integer& Integer::operator%=(Integer a) {
    *this = *this % a;
    return *this;
}

bool operator==(const Integer& a, const Integer& b) {
    bool res = true;
    if (a.size() != b.size()) {
        res = false;
    } else if (a.sign_ != b.sign_) {
        res = false;
    } else {
        for (size_t i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                res = false;
                break;
            }
        }
    }
    if (a.size() == 1 and a[0] == 0 and b.size() == 1 and b[0] == 0)
        res = true;

    return res;
}

bool operator>(const Integer& a, const Integer& b) {
    bool res=false;
    if (a == b) {
        res = false;
    } else {
        if (a.sign_ != b.sign_) {
            res = a.sign_;
        } else if (a.size() > b.size()) {
            res = a.sign_;
        } else if (a.size() < b.size()) {
            res = not a.sign_;
        } else {
            for (size_t i = 0; i < a.size(); i++) {
                short num1 = a[a.size() - 1 - i];
                short num2 = b[a.size() - 1 - i];
                if (num1 > num2) {
                    res = true;
                    break;
                } else if (num1 < num2) {
                    res = false;
                    break;
                }
            }
        }
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Integer& num) {
    if (not num.sign_ and num != Integer(0ll)) {
        os << '-';
    }
    std::ostream_iterator<int, char> out_itr(std::cout);
    std::copy(num.nums_.rbegin(), num.nums_.rend(), out_itr);
    return os;
}