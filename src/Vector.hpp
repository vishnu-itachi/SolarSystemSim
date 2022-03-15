#pragma once

#include <cmath>
#include <corecrt_math.h>
// #include "vector.hpp"



class vector;

class unit_vector
{
public:
    double _a, _b;

    unit_vector() : _a(1), _b(1)
    {
    }
    unit_vector(double a, double b)
    {
        auto mag = sqrt(pow(a, 2) + pow(b, 2));
        _a = a / mag;
        _b = b / mag;
    }

    unit_vector operator+=(unit_vector &right)
    {
        _a += right._a, _b += right._b;
        _a /= magnitude(), _b /= magnitude();
        return *this;
    }

    double magnitude()
    {
        return sqrt(pow(_a, 2) + pow(_b, 2));
    };

    vector operator*(const double &right);
};


class vector : public unit_vector
{
public:
    double _a, _b;

    vector() : _a(0), _b(0)
    {
    }
    vector(double a, double b) : _a(a), _b(b)
    {
    }

    template<typename T>
    friend vector operator*(const vector &left, const T &right)
    {
        return vector(left._a * right, left._b * right);
    }
    friend vector operator*(const float &left, const vector &right)
    {
        return vector(left * right._a, left * right._b);
    }
    friend vector operator/(const vector &left, const float &right)
    {
        return vector(left._a / right, left._b / right);
    }
    friend vector operator/(const float &left, const vector &right)
    {
        return vector(left / right._a, left / right._b);
    }
    vector operator+=(const vector &right)
    {
        _a += right._a, _b += right._b;
        return *this;
    }
    vector operator/=(const double &right)
    {
        _a /= right, _b /= right;
        return *this;
    }
    friend vector operator+(const vector &left, const vector &right)
    {
        return vector(left._a + right._a, left._b + right._b);
    }
    friend vector operator-(const vector &left, const vector &right)
    {
        return vector(left._a - right._a, left._b - right._b);
    }

    friend vector operator*(const vector &left, const vector &right)
    {
        return vector(left._a * right._a, left._b * right._b);
    }
    friend vector operator/(const vector &left, const vector &right)
    {
        return vector(left._a / right._a, left._b / right._b);
    }

    // operator vector() const { return vector(_a, _b); }

    double magnitude()
    {
        return sqrt(pow(_a, 2) + pow(_b, 2));
    };

    unit_vector direction()
    {
        auto vec = *this / magnitude();
        return unit_vector(vec._a, vec._b);
    }
};


inline vector unit_vector::operator*(const double &magnitude)
{
    return vector(_a * magnitude, _b * magnitude);
}
