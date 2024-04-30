/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Functions for treating with points
 */

#include <cstdio>
#include <cmath>

#include "point.h"

double distanceBetween(int dimensions, const double* point1, const double* point2) {
  double distance = 0;
  for (int dim = 0; dim < dimensions; dim++) {
    distance += powf(point1[dim] - point2[dim], 2);
  }
  distance = sqrtf(distance);
  return distance;
}

void printPoint(int dimensions, const double* point) {
  printf("[ ");
  for (int d = 0; d < dimensions; d++) {
    printf("%5.2f", point[d]);
  }
  printf(" ]");
}
