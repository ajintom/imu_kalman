#include "../_wip_quaternion.h"
#include "../_wip_vector.h"

void quaternion_basics_constructors(void)
{
  _wip_::Quaternion q1(1, 2, 3, 4);
  TEST_CHECK(q1.w == 1);
  TEST_CHECK(q1.v.x == 2);
  TEST_CHECK(q1.v.y == 3);
  TEST_CHECK(q1.v.z == 4);

  _wip_::Vector vec1(2, 3, 4);
  _wip_::Quaternion q2(1, vec1);
  TEST_CHECK(q2.w == 1);
  TEST_CHECK(q2.v.x == 2);
  TEST_CHECK(q2.v.y == 3);
  TEST_CHECK(q2.v.z == 4);

  _wip_::Quaternion q3;
  q3.w = 1;
  q3.v.x = 2;
  q3.v.y = 3;
  q3.v.z = 4;
  TEST_CHECK(q3.w == 1);
  TEST_CHECK(q3.v.x == 2);
  TEST_CHECK(q3.v.y == 3);
  TEST_CHECK(q3.v.z == 4);

  _wip_::Quaternion q4 = q1;
  TEST_CHECK(q4.w == 1);
  TEST_CHECK(q4.v.x == 2);
  TEST_CHECK(q4.v.y == 3);
  TEST_CHECK(q4.v.z == 4);
}

void quaternion_arithmetic_addition(void)
{
  _wip_::Quaternion q1(0, 0, 0, 0);
  _wip_::Quaternion q2(1, 2, 3, 4);
  _wip_::Quaternion q3 = q1+q2;
  TEST_CHECK(q3.w == 1);
  TEST_CHECK(q3.v.x == 2);
  TEST_CHECK(q3.v.y == 3);
  TEST_CHECK(q3.v.z == 4);
}

void quaternion_arithmetic_subtraction(void)
{
  _wip_::Quaternion q1(2, 4, 6, 8);
  _wip_::Quaternion q2(1, 2, 3, 4);
  _wip_::Quaternion q3 = q1-q2;
  TEST_CHECK(q3.w == 1);
  TEST_CHECK(q3.v.x == 2);
  TEST_CHECK(q3.v.y == 3);
  TEST_CHECK(q3.v.z == 4);
}

void quaternion_arithmetic_scalarProduct(void)
{
  float f1 = 2;
  _wip_::Quaternion q2(1, 2, 3, 4);
  _wip_::Quaternion q3 = q2*f1;
  TEST_CHECK(q3.w == 2);
  TEST_CHECK(q3.v.x == 4);
  TEST_CHECK(q3.v.y == 6);
  TEST_CHECK(q3.v.z == 8);
}

void quaternion_arithmetic_scalarDivision(void)
{
  _wip_::Quaternion q1(2, 4, 6, 8);
  float f1 = 2;
  _wip_::Quaternion q3 = q1/f1;
  TEST_CHECK(q3.w == 1);
  TEST_CHECK(q3.v.x == 2);
  TEST_CHECK(q3.v.y == 3);
  TEST_CHECK(q3.v.z == 4);
}

void quaternion_arithmetic_quaternionProduct(void)
{
  _wip_::Quaternion q1(1, 2, 3, 4);
  _wip_::Quaternion q2(5, 6, 7, 8);
  _wip_::Quaternion q3 = q1*q2;
  TEST_CHECK(q3.w == -60);
  TEST_CHECK(q3.v.x == 12);
  TEST_CHECK(q3.v.y == 30);
  TEST_CHECK(q3.v.z == 24);

  q1 = _wip_::Quaternion(2, 4, 6, 8);
  q2 = _wip_::Quaternion(1, 3, 6, 9);
  q3 = q1.qprod(q2);
  TEST_CHECK(q3.w == -118);
  TEST_CHECK(q3.v.x == 16);
  TEST_CHECK(q3.v.y == 6);
  TEST_CHECK(q3.v.z == 32);
}

void quaternion_arithmeticAssignement_plusEquals(void)
{
  _wip_::Quaternion q1(0, 0, 0, 0);
  _wip_::Quaternion q2(1, 2, 3, 4);
  q1 += q2;
  TEST_CHECK(q1.w == 1);
  TEST_CHECK(q1.v.x == 2);
  TEST_CHECK(q1.v.y == 3);
  TEST_CHECK(q1.v.z == 4);
}

void quaternion_arithmeticAssignement_minusEquals(void)
{
  _wip_::Quaternion q1(2, 4, 6, 8);
  _wip_::Quaternion q2(1, 2, 3, 4);
  q1 -= q2;
  TEST_CHECK(q1.w == 1);
  TEST_CHECK(q1.v.x == 2);
  TEST_CHECK(q1.v.y == 3);
  TEST_CHECK(q1.v.z == 4);
}

void quaternion_arithmeticAssignement_mulEquals(void)
{
  float q2 = 2;
  _wip_::Quaternion q1(1, 2, 3, 4);
  q1 *= q2;
  TEST_CHECK(q1.w == 2);
  TEST_CHECK(q1.v.x == 4);
  TEST_CHECK(q1.v.y == 6);
  TEST_CHECK(q1.v.z == 8);
}

void quaternion_arithmeticAssignement_divEquals(void)
{
  float q2 = 2;
  _wip_::Quaternion q1(2, 4, 6, 8);
  q1 /= q2;
  TEST_CHECK(q1.w == 1);
  TEST_CHECK(q1.v.x == 2);
  TEST_CHECK(q1.v.y == 3);
  TEST_CHECK(q1.v.z == 4);
}

void quaternion_arithmeticAssignement_qmulEquals(void)
{
  _wip_::Quaternion q3(1, 2, 3, 4);
  _wip_::Quaternion q2(5, 6, 7, 8);
  q3 *= q2;
  TEST_CHECK(q3.w == -60);
  TEST_CHECK(q3.v.x == 12);
  TEST_CHECK(q3.v.y == 30);
  TEST_CHECK(q3.v.z == 24);

  q3 = _wip_::Quaternion(2, 4, 6, 8);
  q2 = _wip_::Quaternion(1, 3, 6, 9);
  q3 *= q2;
  TEST_CHECK(q3.w == -118);
  TEST_CHECK(q3.v.x == 16);
  TEST_CHECK(q3.v.y == 6);
  TEST_CHECK(q3.v.z == 32);
}

void quaternion_norm_normsquared(void)
{
  _wip_::Quaternion q1(2, 4, 6, 8);
  float res = q1.normsquared();
  TEST_CHECK(res == 120);
}

void quaternion_norm_norm(void)
{
  _wip_::Quaternion q1(1, 2, 3, 4);
  float res = q1.norm();
  TEST_CHECK( (res - sqrt(30)) < 0.000001);
}

void quaternion_norm_normalize(void)
{
  _wip_::Quaternion q1(1, 2, 3, 4);
  q1.normalize();
  float invnorm = 1 / sqrt(30);
  TEST_CHECK( q1.w   == (1*invnorm) );
  TEST_CHECK( q1.v.x == (2*invnorm) );
  TEST_CHECK( q1.v.y == (3*invnorm) );
  TEST_CHECK( q1.v.z == (4*invnorm) );
}

void quaternion_other_conj(void)
{
  _wip_::Quaternion q1(1, 2, 3, 4);
  _wip_::Quaternion res = q1.conj();
  TEST_CHECK(res.w == 1);
  TEST_CHECK(res.v.x == -2);
  TEST_CHECK(res.v.y == -3);
  TEST_CHECK(res.v.z == -4);
}

void quaternion_other_recip(void)
{
  _wip_::Quaternion q(1,2,3,4);
  _wip_::Quaternion res = q.recip();
  TEST_CHECK_((res.w -  (1.0/30.0)) < 0.00001, "Expected  %.9f, got  %.9f",1.0/30.0, res.w);
  TEST_CHECK_(res.v.x - (-2.0/30.0) < 0.00001, "Expected %.9f, got %.9f", -2.0/30.0, res.v.x);
  TEST_CHECK_(res.v.y - (-3.0/30.0) < 0.00001, "Expected %.9f, got %.9f", -3.0/30.0, res.v.y);
  TEST_CHECK_(res.v.z - (-4.0/30.0) < 0.00001, "Expected %.9f, got %.9f", -4.0/30.0, res.v.z);
}

void quaternion_other_rotate(void)
{
  _wip_::Vector v(1, 2, 3);
  _wip_::Quaternion q( (6.0/9.0), (5.0/9.0), (4.0/9.0), (2.0/9.0) );
  _wip_::Vector rv = q.rotate(v);

  TEST_CHECK_(rv.norm() - v.norm() < 0.000001, "Rotate: Norm changed from %.2f to %.2f", v.norm(), rv.norm());
  TEST_CHECK_(rv.x - (277.0/81.0) < 0.000001, "Rotate: Expected %.9f, got %.9f", (277.0/81.0), rv.x);
  TEST_CHECK_(rv.y - (-22.0/81.0) < 0.000001, "Rotate: Expected %.9f, got %.9f", (-21.0/81.0), rv.y);
  TEST_CHECK_(rv.z - (121.0/81.0) < 0.000001, "Rotate: Expected %.9f, got %.9f", (121.0/81.0), rv.z);

  rv = q.invRotate(rv);
  TEST_CHECK_(rv.norm() - v.norm() < 0.000001, "Rotate: Norm changed from %.2f to %.2f", v.norm(), rv.norm());
  TEST_CHECK_(rv.x - 1 < 0.000001, "Inv: Expected %.9f, got %.9f", 1.0, rv.x);
  TEST_CHECK_(rv.y - 2 < 0.000001, "Inv: Expected %.9f, got %.9f", 2.0, rv.y);
  TEST_CHECK_(rv.z - 3 < 0.000001, "Inv: Expected %.9f, got %.9f", 3.0, rv.z);

  q = _wip_::Quaternion( 1, 0, 0, 0);
  rv = q.rotate(v);
  TEST_CHECK(rv.x == 1);
  TEST_CHECK(rv.y == 2);
  TEST_CHECK(rv.z == 3);

  q = _wip_::Quaternion( 0, 0, 0, 0);
  rv = q.rotate(v);
  TEST_CHECK(rv.x == 1);
  TEST_CHECK(rv.y == 2);
  TEST_CHECK(rv.z == 3);
}
