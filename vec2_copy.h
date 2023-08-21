#ifndef VEC2_COPY_H
#define VEC2_COPY_H


class Vec2
{
public:
    Vec2();
    Vec2(double a, double b);
    Vec2 operator*(double a); // Multiplication by Scalar
    double operator*(Vec2 const& vec); // Dot product
    Vec2 operator+(Vec2 const& vec); // Vector addition
    Vec2 operator-(Vec2 const& vec); // Vector subtraction
    double length() const;
    Vec2 normalize();

    double x;
    double y;
};

#endif // VEC2_COPY_H
