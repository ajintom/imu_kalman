#ifndef _WIP__MAHONY_H
#define _WIP__MAHONY_H

#include "_wip_vector.h"
#include "_wip_quaternion.h"

namespace _wip_
{
  class MahonyFilter
  {
  public:
    MahonyFilter(int sampleRate)
    : k_P{0.5}, k_I{0.0}, k_a{1}, k_m{1}, samplePeriod{1.0f/(float)sampleRate} {}
    MahonyFilter(int sampleRate, Quaternion initq)
    : k_P{0.5}, k_I{0.0}, k_a{1}, k_m{1}, samplePeriod{1.0f/(float)sampleRate},
      q(initq) {}

    const Quaternion& filter(Vector omega, Vector v_a, Vector v_m, float period);
    const Quaternion& filter(Vector omega, Vector v_a, Vector v_m)
    {
      return filter(omega, v_a, v_m, samplePeriod);
    }

    const Quaternion& getQ() const {return q;}
    float getk_P() const {return k_P;}
    float getk_I() const {return k_I;}
    float getk_a() const {return k_a;}
    float getk_m() const {return k_m;}

    void setk_P(const float& kp) {k_P = kp > 1.0f ? 1 : kp < 0.0f ? 0 : kp;}
    void setk_I(const float& ki) {k_I = ki > 1.0f ? 1 : ki < 0.0f ? 0 : ki;}
    void setk_a(const float& ka) {k_a = ka > 1.0f ? 1 : ka < 0.0f ? 0 : ka;}
    void setk_m(const float& km) {k_m = km > 1.0f ? 1 : km < 0.0f ? 0 : km;}
    void setParams(const float& kp, const float& ki, const float& ka, const float& km)
      { setk_P(kp); setk_I(ki); setk_a(ka); setk_m(km); }
    void setSampleRate(int sampleRate) {samplePeriod = 1.0f/sampleRate;}

  private:
    float k_P;      // the proportional feedback gain parameter
    float k_I;      // the integral feedback gain parameter
    float k_a;      // acceleromter gain, expresses confidence in accel data
    float k_m;      // magnetometer gain, expresses confidence in magne data
    float samplePeriod;
    Quaternion q;   // the estimate of the orientation of the sensor
    Vector b_hat;   // integral of the error estimate
  };
}

#endif
