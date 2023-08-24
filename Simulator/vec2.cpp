#include "vec2.h"
#include <cmath>

Vec2::Vec2()
    : x{0}
    , y{0}
{}

Vec2::Vec2(double a, double b)
    : x{a}
    , y{b}
{}

Vec2 Vec2::operator*(double a)
{
    Vec2 result;
    result.x = x*a;
    result.y = y*a;
    return result;
}

double Vec2::operator*(Vec2 const& vec)
{
    return x*vec.x + y*vec.y;
}

Vec2 Vec2::operator+(const Vec2 &vec)
{
    Vec2 result;
    result.x = x + vec.x;
    result.y = y + vec.y;
    return result;
}

Vec2 Vec2::operator-(const Vec2 &vec)
{
    Vec2 result;
    result.x = x - vec.x;
    result.y = y - vec.y;
    return result;
}

double Vec2::length() const
{
    return hypot(x, y);
}

Vec2 Vec2::normalize()
{
    if(this->length() == 0) return Vec2(0, 0);
    return Vec2(x*(1.0/this->length()), y*(1.0/this->length()));
}
