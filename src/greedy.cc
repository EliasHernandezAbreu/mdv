/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Greedy solver
 */

#include "greedy.h"
#include "point.h"
#include "problem.h"
#include "solution.h"
#include <cstdio>

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
    puts("hi");
    int longest_distance_point = 0;
    float longest_distance = -999999;
    for (int point = 0; point < size; point++) {
      if (result->hasPoint(point)) continue;
      float distance = distanceBetween(dimensions, problem->getPosition(longest_distance_point),
                                       problem->getPosition(point));
      printf("distance from ");
      printPoint(dimensions, problem->getPosition(longest_distance_point));
      printf(" to ");
      printPoint(dimensions, problem->getPosition(point));
      printf(" is %f\n", distance);

      if (distance > longest_distance) {
        longest_distance = distance;
        longest_distance_point = point;
      }
    }
    printf("adding point %d\n", longest_distance_point);
    result->addPoint(longest_distance_point);
  }
  return result;
}
