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
#include "problem.h"

Solution::Solution(const Problem* problem) {
  this->problem = problem;
  solution_points = new bool[problem->getSize()];
  center = new float[problem->getDimensions()]();
  size = 0;
}

Solution::~Solution() {
  if (solution_points != nullptr) delete[] solution_points;
}

float* Solution::getCenter() const {
  return center;
}

bool Solution::hasPoint(int index) const {
  return solution_points[index];
}

void Solution::addPoint(int index) {
  if (solution_points[index]) return;
  solution_points[index] = true;
  for (int d = 0; d < problem->getDimensions(); d++) {
    center[d] *= size;
    center[d] += problem->getPosition(index)[d];
    center[d] /= size + 1;
  }
  size++;
}

void Solution::removePoint(int index) {
  if (!solution_points[index]) return;
  solution_points[index] = false;
  for (int d = 0; d < problem->getDimensions(); d++) {
    center[d] *= size;
    center[d] -= problem->getPosition(index)[d];
    center[d] /= size - 1;
  }
  size--;
}
