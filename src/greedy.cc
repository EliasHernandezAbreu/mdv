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

Solution* Greedy::solve(const Problem* problem, int solution_size) {
  const int dimensions = problem->getDimensions();
  const int size = problem->getSize();
  Solution* result = new Solution(problem);

  // Initial center of all the points
  double* center = new double[dimensions];
  for (int dim = 0; dim < dimensions; dim++) {
    center[dim] = 0;
    for (int point = 0; point < size; point++) {
      center[dim] += problem->getPosition(point)[dim];
    }
    center[dim] /= size;
  }
  for (int i = 0; i < solution_size; i++) {
    int longest_distance_point = 0;
    double longest_distance = -999999;
    // Get point furthest from center
    for (int point = 0; point < size; point++) {
      if (result->hasPoint(point)) continue;
      double distance = distanceBetween(dimensions, center,
                                       problem->getPosition(point));
      if (distance > longest_distance) {
        longest_distance = distance;
        longest_distance_point = point;
      }
    }
    result->addPoint(longest_distance_point);
    if (i == 0) { // run only on first iteration cause then it points to the center
      delete[] center;
      center = result->getCenter();
    }
  }
  return result;
}
