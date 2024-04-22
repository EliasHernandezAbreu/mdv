/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Solution class for representing a solution
 */

#include <cstdio>
#include <cstring>

#include "solution.h"
#include "point.h"
#include "problem.h"

Solution::Solution(const Problem* problem) {
  this->problem = problem;
  solution_points = new bool[problem->getSize()]();
  center = new float[problem->getDimensions()]();
  total_distance = 0;
  size = 0;
}

Solution::~Solution() {
  if (solution_points != nullptr) delete[] solution_points;
  if (center != nullptr) delete[] center; 
}

void Solution::print() const {
  for (int i = 0; i < problem->getSize(); i++) {
    if (hasPoint(i)) {
      printf("%d: [ ", i);
      for (int d = 0; d < problem->getDimensions(); d++) {
        printf("%5.2f ", problem->getPosition(i)[d]);
      }
      puts("]");
    }
  }
  printf("Total distance = %.2f\n", total_distance);
}

float* Solution::getCenter() const {
  return center;
}

bool Solution::hasPoint(int index) const {
  return solution_points[index];
}

void Solution::addPoint(int index) {
  if (solution_points[index]) return;
  for (int p = 0; p < problem->getSize(); p++) {
    if (!solution_points[p]) continue;
    total_distance += distanceBetween(problem->getDimensions(), 
                                      problem->getPosition(p),
                                      problem->getPosition(index));
  }
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
  for (int p = 0; p < problem->getSize(); p++) {
    if (!solution_points[p]) continue;
    total_distance -= distanceBetween(problem->getDimensions(), 
                                      problem->getPosition(p),
                                      problem->getPosition(index));
  }
  solution_points[index] = false;
  for (int d = 0; d < problem->getDimensions(); d++) {
    center[d] *= size;
    center[d] -= problem->getPosition(index)[d];
    center[d] /= size - 1;
  }
  size--;
}

float Solution::getTotalDistance() const {
  return total_distance;
}

char* Solution::getPointsString() const {
  char* result = new char[3 * size + 1](); // 2 digits number + space + final null char
  for (int i = 0; i < problem->getSize(); i++) {
    if (solution_points[i]) {
      char tmp[14];
      sprintf(tmp, "%d ", i);
      strcat(result, tmp);
    }
  }
  return result;
}
