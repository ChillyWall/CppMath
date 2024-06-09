#ifndef DISCRETE_MATH_H_
#define DISCRETE_MATH_H_

#include <array>
#include <initializer_list>
#include "../Matrix/Matrix.h"

template <typename Integer>
Integer gcd(Integer a, Integer b);

template <typename Integer>
Integer lcm(Integer a, Integer b);

template <typename Integer>
struct eul {
    Integer r; // gcd(a, b)
    Integer s; // 贝祖恒等式中a的系数
    Integer t; // 贝祖恒等式中b的系数
    Integer p; // lcm(a, b) / a
    Integer q; // lcm(a, b) / b
};

template <typename Integer>
eul<Integer> exp_eul(Integer a, Integer b);

template <typename Integer>
Integer inverse_mod(Integer a, Integer m);

template <typename Integer>
Integer solve_lin_cong(Integer a, Integer b, Integer m);

template <typename Integer>
Integer solve_lin_congs(std::initializer_list<Integer> a, std::initializer_list<Integer> m);

template <typename Integer>
inline Integer Abs(Integer i) {
    return i < 0 ? -i : i;
}

template <typename Integer>
inline Integer div(Integer a, Integer b) {
    return Integer(a / b);
}

template <typename Integer>
inline Integer mod(Integer a, Integer m) {
    return Integer(a % m);
}

#include "discrete_math.cpp.impl"

#endif