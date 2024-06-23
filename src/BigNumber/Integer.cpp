#include "Integer.h"

Integer::Integer(const std::string& str) {
    sign_ = true;
    for (auto itr = str.rbegin(); itr < str.rend(); itr++) {
        if (isdigit(*itr)) {
            nums_.push_back(*itr - 48);
        } else if (*itr == '-') {
            sign_ = false;
        }
    }
    remove_zeros();
}

Integer operator+(const Integer& a, const Integer& b) {
    if (a.if_zero()) {
        return b;
    } else if (b.if_zero()) {
        return a;
    }
    Integer res;
    if (a.sign_ == b.sign_) {
        short next = 0;
        for (size_t i = 0; i < a.size() || i < b.size(); i++) {
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
    if (a.if_zero()) {
        return b;
    } else if (b.if_zero()) {
        return a;
    }
    Integer res;
    if (a.sign_ == b.sign_) {
        Integer num1(a.abs());
        Integer num2(b.abs());
        bool sign = a.sign_;
        if (num1 < num2) {
            std::swap(num1, num2);
            sign = !sign;
        }
        short next = 0;
        for (size_t i = 0; i < num1.size() || i < num2.size(); i++) {
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

Integer Integer::multiply_single(short opnd) const {
    if (opnd == 0) {
        return Integer(0);
    } else if (opnd == 1) {
        return this->abs();
    } else if (opnd > 1 && opnd < 10) {
        Integer prod;
        short carry = 0;
        for (size_t j = 0; j < size(); j++) {
            short product = this->operator[](j) * opnd + carry;
            carry = product / 10;
            product %= 10;
            prod.nums_.push_back(product);
        }
        if (carry > 0) {
            prod.nums_.push_back(carry);
        }
        return prod;
    } else {
        throw std::invalid_argument("The opnd should be in the range of [0, 10).");
    }
}

Integer operator*(const Integer& a, const Integer& b) {
    if (a.if_zero() || b.if_zero()) {
        return Integer(0);
    }
    Integer res;
    Integer prod;
    for (size_t i = 0; i < b.size(); i++) {
        if (b[i] == 0) {
            continue;
        } else {
            prod = a.multiply_single(b[i]);
            prod.append_zeros(i);
            res += prod;
        }
    }
    res.sign_ = a.sign_ == b.sign_;
    return res;
}

Integer operator/(const Integer& a, const Integer& b) {
    Integer res;
    if (b.if_zero()) {
        std::invalid_argument("Wrong, the b should not be 0.");
    }
    if (a.if_zero()) {
        return a;
    }
    if (a.size() >= b.size()) {
        Integer b_abs(b.abs());
        auto itr = a.nums_.cbegin() + a.size() - b.size();
        Integer opnd1;
        opnd1.nums_ = std::deque<short>(itr, a.nums_.cend());

        while (itr != a.nums_.cbegin()) {
            itr--;
            short lo = 0;
            short hi = 10;
            while (hi - lo > 1) {
                short mid = (lo + hi) / 2;
                if (b_abs.multiply_single(mid) > opnd1) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            opnd1 -= Integer(lo) * b_abs;
            res.nums_.push_front(lo);
            if (opnd1.if_zero()) {
                opnd1.nums_.pop_back();
            }
            opnd1.nums_.push_front(*itr);
        }
        res.remove_zeros();
        short lo = 0;
        short hi = 10;
        while (hi - lo > 1) {
            short mid = (lo + hi) / 2;
            if (b_abs * Integer(mid) > opnd1) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        res.nums_.push_front(lo);
    } else {
        res = Integer(0LL);
    }
    res.sign_ = a.sign_ == b.sign_;
    return res;
}

bool operator==(const Integer& a, const Integer& b) {
    bool res = true;
    if (a.size() != b.size()) {
        res = false;
    } else if (a.sign_ != b.sign_) {
        res = false;
        if (a.if_zero() && b.if_zero()) {
            res = true;
        }
    } else {
        for (size_t i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                res = false;
                break;
            }
        }
    }
    return res;
}

bool operator>(const Integer& a, const Integer& b) {
    bool res = false;

    if (a.sign_ != b.sign_) {
        res = a.sign_;
    } else if (a.size() > b.size()) {
        res = a.sign_;
    } else if (a.size() < b.size()) {
        res = !a.sign_;
    } else {
        for (size_t i = 0; i < a.size(); i++) {
            short num1 = a[a.size() - 1 - i];
            short num2 = b[a.size() - 1 - i];
            if (num1 > num2) {
                res = a.sign_;
                break;
            } else if (num1 < num2) {
                res = !a.sign_;
                break;
            }
        }
    }
    if (a.if_zero() && b.if_zero()) {
        res = false;
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Integer& num) {
    if ((!num.sign_) && (num != Integer(0LL))) {
        os << '-';
    }
    std::ostream_iterator<int, char> out_itr(std::cout);
    std::copy(num.nums_.rbegin(), num.nums_.rend(), out_itr);
    return os;
}