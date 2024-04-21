/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Greedy solver
 */

#include <stdio.h>

#include "greedy.h"
#include "point.h"
#include "problem.h"
#include "solution.h"

Solution* Greedy::solve(const Problem* problem, int solution_size) const {
  const int dimensions = problem->getDimensions();
  const int size = problem->getSize();

  Solution* result = new Solution(problem);
  float initial_center[dimensions];
  for (int dim = 0; dim < dimensions; dim++) {
    initial_center[dim] = 0;
    for (int point = 0; point < size; point++) {
      initial_center[dim] += problem->getPosition(point)[dim];
    }
    initial_center[dim] /= size;
  }
  for (int i = 0; i < solution_size; i++) {
    int longest_distance_point = 0;
    float longest_distance = 999999;
    for (int point = 0; point < size; point++) {
      if (result->hasPoint(point)) continue;
      float distance = distanceBetween(dimensions, problem->getPosition(longest_distance),
                                       problem->getPosition(point));
      if (distance > longest_distance) {
        longest_distance = distance;
        longest_distance_point = point;
      }
    }
    result->addPoint(longest_distance_point);
  }
  return result;
}
