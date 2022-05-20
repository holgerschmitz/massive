#ifndef MASSIVE_TYPES_HPP_
#define MASSIVE_TYPES_HPP_

#include "../huerto/types.hpp"

#ifdef MASSIVE_ONE_V
static const size_t V_DIMENSION = 1;
#endif

#ifdef MASSIVE_TWO_V
static const size_t V_DIMENSION = 2;
#endif

#ifdef MASSIVE_THREE_V
static const size_t V_DIMENSION = 3;
#endif

typedef schnek::Array<int, V_DIMENSION> VIndex;
typedef schnek::Array<double, V_DIMENSION> VVector;

typedef schnek::Range<int, V_DIMENSION> VRange;
typedef schnek::Range<double, V_DIMENSION> VDomain;

#endif // MASSIVE_TYPES_HPP_