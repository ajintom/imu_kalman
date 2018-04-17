#include "_wip_mahony.h"
#include "_wip_vector.h"
#include "_wip_quaternion.h"
#include <math.h>

namespace _wip_
{
  const Quaternion& MahonyFilter::filter(Vector omega,
                                         Vector v_a,
                                         Vector v_m,
                                         float period)
  {
    // this implementation is based on a close reading of Mahoney et al. 2008,
    // as well as Madgwick's open source implementations in C++ and Matlab

    v_a.normalize();
    v_m.normalize();

    // I'm honestly not sure why we do this, but if it works for Madgwick...
    Vector h = q.rotate(v_m);
    Vector b( sqrt(h.x*h.x + h.y*h.y), 0, h.z );
    Vector v_hat_m = q.invRotate(b); // estimated direction of magnetic field

    Vector v_hat_a = q.invRotate(Vector(0, 0, -1)); // estimated gravity vector

    // see eqs. (32c) and (48a) in Mahoney et al. 2008
    Vector w_mes = v_a.cross(v_hat_a) * k_a + v_m.cross(v_hat_m) * k_m;

    if (k_I > 0.0)
    {
      b_hat += k_I * w_mes * period; // see eq. (48c)
      q += ( (0.5 * q) * (omega + b_hat + k_P * w_mes) ) * period; // see eq. (48b)
    }
    else
    {
      b_hat = Vector(0, 0, 0); // Madgwick: "prevent integral windup"
      q += ( (0.5 * q) * (omega + k_P * w_mes) ) * period; // no need to add b_hat anymore...
    }

    return q.normalize(); // normalize returns reference to q
  }
}
