#ifndef _WIP__QUATERNION_H
#define _WIP__QUATERNION_H

#include "_wip_vector.h"

namespace _wip_
{
  class Quaternion
  {
  public:
    Quaternion(float initw, float initx, float inity, float initz)
    : w{initw}, v(initx, inity, initz) {}
    Quaternion(float initw, Vector initv) : w{initw}, v{initv} {}
    Quaternion() : w{1}, v() {}
    float w;
    Vector v;

    // add two quaternions element by element
    Quaternion operator+(const Quaternion& rhs) const;
    Quaternion& operator+=(const Quaternion& rhs);

    // subtract one quaternion from another, element by element
    Quaternion operator-(const Quaternion& rhs) const;
    Quaternion& operator-=(const Quaternion& rhs);

    // multiply a quaternion by a scalar
    Quaternion operator*(const float& s) const;
    Quaternion& operator*=(const float& s);

    // divide a quaternion by a scalar
    Quaternion operator/(const float& s) const;
    Quaternion& operator/=(const float& s);

    // equality comparisons
    bool operator==(const Quaternion& rhs) const;
    bool operator==(const float& rhs) const;
    bool operator!=(const Quaternion& rhs) const;
    bool operator!=(const float& rhs) const;

    // quaternion product
    Quaternion qprod(const Quaternion& rhs) const;
    Quaternion operator*(const Quaternion& rhs) const;
    Quaternion& operator*=(const Quaternion& rhs);
    Quaternion qprod(const Vector& rhs) const;
    Quaternion operator*(const Vector& rhs) const;
    Quaternion& operator*=(const Vector& rhs);

    // norm
    float normsquared() const;
    float norm() const;
    Quaternion& normalize();

    Quaternion conj() const;
    Quaternion recip() const;

    Vector rotate(const Vector& q) const;
    Vector invRotate(const Vector& q) const;
  };

  Quaternion operator* (const float& lhs, const Quaternion& rhs);
}

#endif
