#ifndef COMPLEX_H_
#define COMPLEX_H_ 1

#include "Real.h"

class Complex {
    private:

    Real re_;
    Real im_;
    Real mod_;
    Real paa_;

    void cal_mod_();
    void cal_paa_();

    public:
    Complex() : re_ { Real(0) }, im_ { Real(0) }, mod_ { Real(0) }, paa_ { Real(0) } {}
    Complex(const Real& real, const Real& imaginary) : re_ { real }, im_ { imaginary } {
        cal_mod_();
    }
    Complex(Real&& real, Real&& imaginary) noexcept : re_ {std::move(real)}, im_{std::move(imaginary)} {}

};

#include "Complex.cpp.impl"
#endif