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
#include <stdexcept>

#include "solution.h"
#include "point.h"
#include "problem.h"

Solution::Solution(const Problem* problem) {
  this->problem = problem;
  solution_points = new char[problem->getSize()]();
  center = new double[problem->getDimensions()]();
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

double* Solution::getCenter() const {
  return center;
}

bool Solution::hasPoint(int index) const {
  return solution_points[index] > 0;
}

void Solution::addPoint(int index) {
  if (solution_points[index] > 0) return;
  for (int p = 0; p < problem->getSize(); p++) {
    if (solution_points[p] == 0) continue;
    total_distance += distanceBetween(problem->getDimensions(), 
                                      problem->getPosition(p),
                                      problem->getPosition(index));
  }
  solution_points[index]++;
  for (int d = 0; d < problem->getDimensions(); d++) {
    center[d] *= size;
    center[d] += problem->getPosition(index)[d];
    center[d] /= size + 1;
  }
  size++;
}

void Solution::removePoint(int index) {
  if (solution_points[index] == 0) return;
  for (int p = 0; p < problem->getSize(); p++) {
    if (!solution_points[p]) continue;
    total_distance -= distanceBetween(problem->getDimensions(), 
                                      problem->getPosition(p),
                                      problem->getPosition(index));
  }
  solution_points[index] = 0;
  for (int d = 0; d < problem->getDimensions(); d++) {
    center[d] *= size;
    center[d] -= problem->getPosition(index)[d];
    center[d] /= size - 1;
  }
  size--;
}

double Solution::getTotalDistance() const {
  return total_distance;
}

double Solution::confirmTotalDistance() const {
  double distance = 0;
  for (int from = 0; from < problem->getSize(); from++) {
    if (!hasPoint(from)) continue;
    for (int to = from + 1; to < problem->getSize(); to++) {
      if (!hasPoint(to)) continue;
      distance += distanceBetween(problem->getDimensions(),
                                  problem->getPosition(from),
                                  problem->getPosition(to));
    }
  }
  return distance;
}

void Solution::reloadTotalDistance() {
  total_distance = confirmTotalDistance();
}

char* Solution::getPointsString() const {
  char* result = new char[3 * size + 1](); // 2 digits number + space + final null char
  for (int i = 0; i < problem->getSize(); i++) {
    if (solution_points[i] > 0) {
      char tmp[14];
      sprintf(tmp, "%d ", i);
      strcat(result, tmp);
    }
  }
  return result;
}

void Solution::copy(const Solution* other) {
  this->problem = other->problem;
  this->size = other->size;
  this->total_distance = other->total_distance;
  memcpy(this->center, other->center, sizeof(double) * problem->getDimensions());
  // this->size is the amount of points in the solution, solution points has an entry for every point
  memcpy(this->solution_points, other->solution_points, sizeof(bool) * problem->getSize());
}

double Solution::evaluateMovement(int out, int in) {
  if (out == in) return 0;
  if (hasPoint(in) || !hasPoint(out)) throw std::runtime_error("Impossible to evaluate");
  double current_increment = -getTotalDistance();
  removePoint(out);
  addPoint(in);
  current_increment += getTotalDistance();
  removePoint(in);
  addPoint(out);
  return current_increment;
}

void Solution::doMovement(Movement* movement) {
  removePoint(movement->out);
  addPoint(movement->in);
}
