#ifndef _WIP__VECTOR_H
#define _WIP__VECTOR_H

namespace _wip_
{
  class Vector
  {
  public:
    Vector(float initx, float inity, float initz) : x{initx}, y{inity}, z{initz} {}
    Vector() : x{0}, y{0}, z{0} {}
    float x;
    float y;
    float z;

    // add two vectors element by element
    Vector operator+(const Vector& rhs) const;
    Vector& operator+=(const Vector& rhs);

    // subtract one vector from another, element by element, and unary negative
    Vector operator-(const Vector& rhs) const;
    Vector& operator-=(const Vector& rhs);
    Vector operator-() const;

    // multiply a vector by a scalar
    Vector operator*(const float& s) const;
    Vector& operator*=(const float& s);

    // divide a vector by a scalar
    Vector operator/(const float& s) const;
    Vector& operator/=(const float& s);

    // equality comparisons
    bool operator==(const Vector& rhs) const;
    bool operator==(const float& rhs) const;
    bool operator!=(const Vector& rhs) const;
    bool operator!=(const float& rhs) const;

    // typical dot and cross products
    float dot(const Vector& rhs) const;
    float operator*(const Vector& rhs) const;
    Vector cross(const Vector& rhs) const;

    // norm
    float normsquared() const;
    float norm() const;
    Vector& normalize();
  };
  Vector operator* (const float& lhs, const Vector& rhs);
}

#endif
