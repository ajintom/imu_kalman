#include "_wip_quaternion.h"
#include "_wip_vector.h"
#include <math.h>

namespace _wip_
{
  Quaternion Quaternion::operator+(const Quaternion& rhs) const
  {
    return Quaternion(this->w + rhs.w, this->v + rhs.v);
  }

  Quaternion& Quaternion::operator+=(const Quaternion& rhs)
  {
    this->w += rhs.w;
    this->v += rhs.v;
    return *this;
  }

  Quaternion Quaternion::operator-(const Quaternion& rhs) const
  {
    return Quaternion(this->w - rhs.w, this->v - rhs.v);
  }

  Quaternion& Quaternion::operator-=(const Quaternion& rhs)
  {
    this->w -= rhs.w;
    this->v -= rhs.v;
    return *this;
  }

  Quaternion Quaternion::operator*(const float& s) const
  {
    return Quaternion(this->w*s, this->v*s);
  }
  Quaternion operator* (const float& lhs, const Quaternion& rhs) { return rhs*lhs; }

  Quaternion& Quaternion::operator*=(const float& s)
  {
    this->w *= s;
    this->v *= s;
    return *this;
  }

  Quaternion Quaternion::operator/(const float& s) const
  {
    return Quaternion(this->w/s, this->v/s);
  }

  Quaternion& Quaternion::operator/=(const float& s)
  {
    this->w /= s;
    this->v /= s;
    return *this;
  }

  bool Quaternion::operator==(const Quaternion& rhs) const { return (this->w == rhs.w && this->v == rhs.v); }
  bool Quaternion::operator==(const float& rhs) const { return (this->w == rhs && this->v == rhs); }
  bool Quaternion::operator!=(const Quaternion& rhs) const { return (this->w == rhs.w && this->v == rhs.v); }
  bool Quaternion::operator!=(const float& rhs) const { return (this->w == rhs && this->v == rhs); }

  Quaternion Quaternion::qprod(const Quaternion& rhs) const
  {
    return Quaternion
    (
      this->w * rhs.w - this->v.dot(rhs.v),
      this->w * rhs.v + rhs.w * this->v + this->v.cross(rhs.v)
    );
  }

  Quaternion Quaternion::operator*(const Quaternion& rhs) const { return this->qprod(rhs); }
  Quaternion& Quaternion::operator*=(const Quaternion& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  Quaternion Quaternion::qprod(const Vector& rhs) const
  {
    return Quaternion
    (
      0 - this->v.dot(rhs),
      this->w * rhs + this->v.cross(rhs)
    );
  }

  Quaternion Quaternion::operator*(const Vector& rhs) const { return this->qprod(rhs); }
  Quaternion& Quaternion::operator*=(const Vector& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  float Quaternion::normsquared() const { return this->w*this->w + this->v.normsquared(); }
  float Quaternion::norm() const { return sqrt(this->normsquared()); }

  Quaternion& Quaternion::normalize()
  {
    if ( *this == 0.0 ) return *this; // avoid NaN
    float invnorm = 1 / this->norm();
    *this *= invnorm;
    return *this;
  }

  Quaternion Quaternion::conj() const { return Quaternion(this->w, -(this->v)); }
  Quaternion Quaternion::recip() const { return (this->conj()) / this->normsquared(); }

  Vector Quaternion::rotate(const Vector& vec) const
  {
    float wx, wy, wz, xx, xy, xz, yy, yz, zz;
    wx = this->w*this->v.x;
    wy = this->w*this->v.y;
    wz = this->w*this->v.z;
    xx = this->v.x*this->v.x;
    xy = this->v.x*this->v.y;
    xz = this->v.x*this->v.z;
    yy = this->v.y*this->v.y;
    yz = this->v.y*this->v.z;
    zz = this->v.z*this->v.z;
    return 2 * Vector
    (
      vec.x * (0.5 - yy - zz) + vec.y * (xy - wz) + vec.z * (wy + xz),
      vec.x * (wz + xy) + vec.y * (0.5 - xx - zz) + vec.z * (yz - wx),
      vec.x * (xz - wy) + vec.y * (wx + yz) + vec.z * (0.5 - yy - xx)
    );
  }

  Vector Quaternion::invRotate(const Vector& vec) const
  {
    float wx, wy, wz, xx, xy, xz, yy, yz, zz;
    wx = this->w*this->v.x;
    wy = this->w*this->v.y;
    wz = this->w*this->v.z;
    xx = this->v.x*this->v.x;
    xy = this->v.x*this->v.y;
    xz = this->v.x*this->v.z;
    yy = this->v.y*this->v.y;
    yz = this->v.y*this->v.z;
    zz = this->v.z*this->v.z;
    return 2 * Vector
    (
      vec.x * (0.5 - yy - zz) + vec.y * (wz + xy) + vec.z * (xz - wy),
      vec.x * (xy - wz) + vec.y * (0.5 - xx - zz) + vec.z * (wx + yz),
      vec.x * (wy + xz) + vec.y * (yz - wx) + vec.z * (0.5 - yy - xx)
    );
  }
}
