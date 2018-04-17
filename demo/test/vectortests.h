#include "../_wip_vector.h"
#include <math.h>

void vector_basics_constructors(void)
{
  _wip_::Vector vec1(1,2,3);
  TEST_CHECK_(vec1.x == 1, "Init: Expected %.2f, got %.2f", 1.0, vec1.x);
  TEST_CHECK_(vec1.y == 2, "Init: Expected %.2f, got %.2f", 2.0, vec1.y);
  TEST_CHECK_(vec1.z == 3, "Init: Expected %.2f, got %.2f", 3.0, vec1.z);
  _wip_::Vector vec2;
  vec2.x = 1;
  vec2.y = 2;
  vec2.z = 3;
  TEST_CHECK_(vec2.x == 1, "Void: Expected %.2f, got %.2f", 1.0, vec2.x);
  TEST_CHECK_(vec2.y == 2, "Void: Expected %.2f, got %.2f", 2.0, vec2.y);
  TEST_CHECK_(vec2.z == 3, "Void: Expected %.2f, got %.2f", 3.0, vec2.z);
  _wip_::Vector vec3 = vec1;
  TEST_CHECK_(vec3.x == 1, "Copy: Expected %.2f, got %.2f", 1.0, vec3.x);
  TEST_CHECK_(vec3.y == 2, "Copy: Expected %.2f, got %.2f", 2.0, vec3.y);
  TEST_CHECK_(vec3.z == 3, "Copy: Expected %.2f, got %.2f", 3.0, vec3.z);
}

void vector_arithmetic_addition(void)
{
  _wip_::Vector vec1(1, 2, 3);
  _wip_::Vector vec2 = vec1;
  _wip_::Vector res  = vec1 + vec2;
  TEST_CHECK_(res.x == 2, "Expected %.2f, got %.2f", 2.0, res.x);
  TEST_CHECK_(res.y == 4, "Expected %.2f, got %.2f", 4.0, res.y);
  TEST_CHECK_(res.z == 6, "Expected %.2f, got %.2f", 6.0, res.z);
}

void vector_arithmetic_subtraction(void)
{
  _wip_::Vector vec1(5, 10, 15);
  _wip_::Vector vec2(1, 2, 3);
  _wip_::Vector res  = vec1 - vec2;
  TEST_CHECK_(res.x == 4, "Expected %.2f, got %.2f", 4.0, res.x);
  TEST_CHECK_(res.y == 8, "Expected %.2f, got %.2f", 8.0, res.y);
  TEST_CHECK_(res.z == 12, "Expected %.2f, got %.2f", 12.0, res.z);
}

void vector_arithmetic_unarynegative(void)
{
  _wip_::Vector vec1(1, 2, 3);
  vec1 = -vec1;
  TEST_CHECK(vec1.x == -1);
  TEST_CHECK(vec1.y == -2);
  TEST_CHECK(vec1.z == -3);
}

void vector_arithmetic_scalarProduct(void)
{
  _wip_::Vector vec1(1, 2, 3);
  float mul = 2;
  _wip_::Vector res  = vec1 * mul;
  TEST_CHECK_(res.x == 2, "Expected %.2f, got %.2f", 2.0, res.x);
  TEST_CHECK_(res.y == 4, "Expected %.2f, got %.2f", 4.0, res.y);
  TEST_CHECK_(res.z == 6, "Expected %.2f, got %.2f", 6.0, res.z);
}

void vector_arithmetic_scalarDivision(void)
{
  _wip_::Vector vec1(2, 4, 6);
  float den = 2;
  _wip_::Vector res  = vec1 / den;
  TEST_CHECK_(res.x == 1, "Expected %.2f, got %.2f", 1.0, res.x);
  TEST_CHECK_(res.y == 2, "Expected %.2f, got %.2f", 2.0, res.y);
  TEST_CHECK_(res.z == 3, "Expected %.2f, got %.2f", 3.0, res.z);
}

void vector_arithmetic_dotProduct(void)
{
  _wip_::Vector vec1(1, 2, 3);
  _wip_::Vector vec2(4, 5, 6);
  float res = vec1.dot(vec2);
  TEST_CHECK_(res == 32, "Expected %.2f, got %.2f", 32.00, res);
  res = vec1 * vec2;
  TEST_CHECK_(res == 32, "Expected %.2f, got %.2f", 32.00, res);
}

void vector_arithmetic_crossProduct(void)
{
  _wip_::Vector vec1(1, 2, 3);
  _wip_::Vector vec2(4, 5, 6);
  _wip_::Vector res  = vec1.cross(vec2);
  TEST_CHECK_(res.x == -3, "Expected %.2f, got %.2f", -3.0, res.x);
  TEST_CHECK_(res.y ==  6, "Expected %.2f, got %.2f", 6.0, res.y);
  TEST_CHECK_(res.z == -3, "Expected %.2f, got %.2f", -3.0, res.z);
}

void vector_arithmeticAssignment_plusEquals(void)
{
  _wip_::Vector vec1(1, 2, 3);
  _wip_::Vector vec2(4, 5, 6);
  vec1 += vec2;
  TEST_CHECK_(vec1.x == 5, "Expected %.2f, got %.2f", 5.0, vec1.x);
  TEST_CHECK_(vec1.y == 7, "Expected %.2f, got %.2f", 7.0, vec1.y);
  TEST_CHECK_(vec1.z == 9, "Expected %.2f, got %.2f", 9.0, vec1.z);
}

void vector_arithmeticAssignment_minusEquals(void)
{
  _wip_::Vector vec1(1, 2, 3);
  _wip_::Vector vec2(4, 5, 6);
  vec1 -= vec2;
  TEST_CHECK_(vec1.x == -3, "Expected %.2f, got %.2f", -3.0, vec1.x);
  TEST_CHECK_(vec1.y == -3, "Expected %.2f, got %.2f", -3.0, vec1.y);
  TEST_CHECK_(vec1.z == -3, "Expected %.2f, got %.2f", -3.0, vec1.z);
}

void vector_arithmeticAssignment_mulEquals(void)
{
  _wip_::Vector vec1(1, 2, 3);
  float rhs = 2;
  vec1 *= rhs;
  TEST_CHECK_(vec1.x == 2, "Expected %.2f, got %.2f", 2.0, vec1.x);
  TEST_CHECK_(vec1.y == 4, "Expected %.2f, got %.2f", 4.0, vec1.y);
  TEST_CHECK_(vec1.z == 6, "Expected %.2f, got %.2f", 6.0, vec1.z);
}

void vector_arithmeticAssignment_divEquals(void)
{
  _wip_::Vector vec1(1, 2, 3);
  float rhs = 2;
  vec1 /= rhs;
  TEST_CHECK_(vec1.x == 0.5, "Expected %.2f, got %.2f", 0.5, vec1.x);
  TEST_CHECK_(vec1.y == 1.0, "Expected %.2f, got %.2f", 1.0, vec1.y);
  TEST_CHECK_(vec1.z == 1.5, "Expected %.2f, got %.2f", 1.5, vec1.z);
}

void vector_norm_normsquared(void)
{
  _wip_::Vector vec1(5,6,7);
  float res = vec1.normsquared();
  TEST_CHECK_(res == 110, "Expected %.2f, got %.2f", 110.0, res);
}

void vector_norm_norm(void)
{
  _wip_::Vector vec1(1, 2, 3);
  float res = vec1.norm();
  TEST_CHECK_( (res - sqrt(14)) < 0.000001, "Expected %.2f, got %.2f", sqrt(14.0), res);
}

void vector_norm_normalize(void)
{
  _wip_::Vector vec1(1, 2, 3);
  vec1.normalize();
  TEST_CHECK_( (vec1.x - (1.0/sqrt(14.0)) ) < 0.00000000000001,
    "Expected %.2f, got %.2f", (1.0/sqrt(14.0)), vec1.x);
  TEST_CHECK_( (vec1.y - (2.0/sqrt(14.0)) ) < 0.00000000000001,
    "Expected %.2f, got %.2f", (2.0/sqrt(14.0)), vec1.y);
  TEST_CHECK_( (vec1.z - (3.0/sqrt(14.0)) ) < 0.00000000000001,
    "Expected %.2f, got %.2f", (3.0/sqrt(14.0)), vec1.z);
}

void vector_comparison(void)
{
  _wip_::Vector vec1(0, 0, 0);
  _wip_::Vector vec2(0, 0, 0);
  _wip_::Vector vec3(1, 1, 1);
  TEST_CHECK_(vec1 == vec2,
    "v == v: Vector 1 is [%.2f, %.2f, %.2f], Vector 2 is [%.2f, %.2f, %.2f]",
    vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z);
  TEST_CHECK_(vec1 == 0.0,
    "v == f: Vector 1 is [%.2f, %.2f, %.2f], float is %.2f",
    vec1.x, vec1.y, vec1.z, 0.0);
  TEST_CHECK_(vec1 != vec3,
    "v != v: Vector 1 is [%.2f, %.2f, %.2f], Vector 2 is [%.2f, %.2f, %.2f]",
    vec1.x, vec1.y, vec1.z, vec3.x, vec3.y, vec3.z);
  TEST_CHECK_(vec3 != 0.0,
    "v != f: Vector 3 is [%.2f, %.2f, %.2f], float is %.2f",
    vec3.x, vec3.y, vec3.z, 0.0);
}
