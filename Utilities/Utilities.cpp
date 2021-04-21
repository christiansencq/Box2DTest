#include "Utilities.h"

bool Compare(float m, float n)
{
    return fabsf(m-n) < EPSILON;
}