/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Functions for treating with points
 */

#include <math.h>

#include "point.h"

float distanceBetween(int dimensions, const float* point1, const float* point2) {
  float distance = 0;
  for (int dim = 0; dim < dimensions; dim++) {
    distance += powf(point1[dim] - point2[dim], 2);
  }
  distance = sqrtf(distance);
  return distance;
}

