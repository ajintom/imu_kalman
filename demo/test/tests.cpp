#include "acutest.h"
#include "vectortests.h"
#include "quaterniontests.h"

// g++ test.cpp ../_wip_vector.cpp ../_wip_quaternion.cpp -std=c++11 -o tests

TEST_LIST =
{
  { "vector_basics_constructors", vector_basics_constructors },
  { "vector_arithmetic_addition", vector_arithmetic_addition },
  { "vector_arithmetic_subtraction", vector_arithmetic_subtraction },
  { "vector_arithmetic_unarynegative", vector_arithmetic_unarynegative },
  { "vector_arithmetic_scalarProduct", vector_arithmetic_scalarProduct },
  { "vector_arithmetic_scalarDivision", vector_arithmetic_scalarDivision },
  { "vector_arithmetic_dotProduct", vector_arithmetic_dotProduct },
  { "vector_arithmetic_crossProduct", vector_arithmetic_crossProduct },
  { "vector_arithmeticAssignment_plusEquals", vector_arithmeticAssignment_plusEquals },
  { "vector_arithmeticAssignment_minusEquals", vector_arithmeticAssignment_minusEquals },
  { "vector_arithmeticAssignment_mulEquals", vector_arithmeticAssignment_mulEquals },
  { "vector_arithmeticAssignment_divEquals", vector_arithmeticAssignment_divEquals },
  { "vector_norm_normsquared", vector_norm_normsquared },
  { "vector_norm_norm", vector_norm_norm },
  { "vector_norm_normalize", vector_norm_normalize },
  { "vector_comparison", vector_comparison },

  { "quaternion_basics_constructors", quaternion_basics_constructors },
  { "quaternion_arithmetic_addition", quaternion_arithmetic_addition },
  { "quaternion_arithmetic_subtraction", quaternion_arithmetic_subtraction },
  { "quaternion_arithmetic_scalarProduct", quaternion_arithmetic_scalarProduct },
  { "quaternion_arithmetic_scalarDivision", quaternion_arithmetic_scalarDivision },
  { "quaternion_arithmetic_quaternionProduct", quaternion_arithmetic_quaternionProduct },
  { "quaternion_arithmeticAssignement_plusEquals", quaternion_arithmeticAssignement_plusEquals },
  { "quaternion_arithmeticAssignement_minusEquals", quaternion_arithmeticAssignement_minusEquals },
  { "quaternion_arithmeticAssignement_mulEquals", quaternion_arithmeticAssignement_mulEquals },
  { "quaternion_arithmeticAssignement_divEquals", quaternion_arithmeticAssignement_divEquals },
  { "quaternion_arithmeticAssignement_qmulEquals", quaternion_arithmeticAssignement_qmulEquals },
  { "quaternion_norm_normsquared", quaternion_norm_normsquared },
  { "quaternion_norm_norm", quaternion_norm_norm },
  { "quaternion_norm_normalize", quaternion_norm_normalize },
  { "quaternion_other_conj", quaternion_other_conj },
  { "quaternion_other_recip", quaternion_other_recip },
  { "quaternion_other_rotate", quaternion_other_rotate },

  { 0 }
};
