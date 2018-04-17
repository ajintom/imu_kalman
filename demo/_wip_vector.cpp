#include "_wip_vector.h"
#include <math.h>

namespace _wip_
{
  Vector Vector::operator+(const Vector& rhs) const
  {
    return Vector(this->x+rhs.x, this->y+rhs.y, this->z+rhs.z);
  }

  Vector& Vector::operator+=(const Vector& rhs)
  {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
  }

  Vector Vector::operator-(const Vector& rhs) const
  {
    return Vector(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z);
  }

  Vector& Vector::operator-=(const Vector& rhs)
  {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
  }

  Vector Vector::operator-() const { return Vector(-(this->x), -(this->y), -(this->z)); }

  Vector Vector::operator*(const float& s) const { return Vector(x*s, y*s, z*s); }
  Vector operator* (const float& lhs, const Vector& rhs) { return rhs*lhs; }

  Vector& Vector::operator*=(const float& s)
  {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  Vector Vector::operator/(const float& s) const { return Vector(x/s, y/s, z/s); }

  Vector& Vector::operator/=(const float& s)
  {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  bool Vector::operator==(const Vector& rhs)const
  {
    return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
  }

  bool Vector::operator==(const float& rhs) const
  {
    return (this->x == rhs && this->y == rhs && this->z == rhs);
  }

  bool Vector::operator!=(const Vector& rhs) const { return !(*this == rhs); }
  bool Vector::operator!=(const float& rhs) const { return !(*this == rhs); }

  float Vector::dot(const Vector& rhs) const
  {
    return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z;
  }

  float Vector::operator*(const Vector& rhs) const { return this->dot(rhs); }

  Vector Vector::cross(const Vector& rhs) const
  {
    return Vector (
      this->y*rhs.z - this->z*rhs.y,
      this->z*rhs.x - this->x*rhs.z,
      this->x*rhs.y - this->y*rhs.x
    );
  }

  float Vector::normsquared() const { return this->dot(*this); }
  float Vector::norm() const { return sqrt(this->normsquared()); }

  Vector& Vector::normalize()
  {
    if ( *this == 0.0 ) return *this; // avoid NaN
    float invnorm = 1.0 / this->norm();
    *this *= invnorm;
    return *this;
  }
}
