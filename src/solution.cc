/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Solution class for representing a solution
 */

#include "solution.h"

Solution::Solution(int size) {
  this->size = size;
  solution_points = new bool[size];
}

Solution::~Solution() {
  if (solution_points != nullptr) delete[] solution_points;
}
