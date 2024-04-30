/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Grasp solver
 */

#include <cstdlib>
#include <ctime>

#include "grasp.h"
#include "point.h"
#include "problem.h"
#include "solution.h"

Grasp::Grasp(int iterations, int rcl_size) {
  this->iterations = iterations;
  this->rcl_size = rcl_size;
}

Solution* Grasp::solve(const Problem* problem, int solution_size) const {
  srand(clock());
  const int dimensions = problem->getDimensions();
  const int size = problem->getSize();
  Solution* best_result = new Solution(problem);

  for (int cur_it = 0; cur_it < iterations; cur_it++) {
    // Initial center of all the points
    Solution* current_result = new Solution(problem);
    double* center = new double[dimensions];
    for (int dim = 0; dim < dimensions; dim++) {
      center[dim] = 0;
      for (int point = 0; point < size; point++) {
        center[dim] += problem->getPosition(point)[dim];
      }
      center[dim] /= size;
    }

    // Add points to solution
    for (int i = 0; i < solution_size; i++) {
      // Create rcl
      double rcl_distances[rcl_size];
      int rcl_points[rcl_size];
      for (int rclentry = 0; rclentry < rcl_size; rclentry++) {
        rcl_distances[rclentry] = 0;
        rcl_points[rclentry] = rclentry;
      }
      // Look for furthest points
      for (int point = 0; point < size; point++) {
        if (current_result->hasPoint(point)) continue;
        double distance = distanceBetween(dimensions, center,
                                         problem->getPosition(point));
        // Get worst item in rcl
        int rcl_worst_entry = 0;
        for (int rclentry = 0; rclentry < rcl_size; rclentry++) {
          if (rcl_distances[rclentry] < rcl_distances[rcl_worst_entry])
            rcl_worst_entry = rclentry;
        }
        // Substitude entry by new distance if its better
        if (distance > rcl_distances[rcl_worst_entry]) {
          rcl_distances[rcl_worst_entry] = distance;
          rcl_points[rcl_worst_entry] = point;
        }
      }
      // Add a random point from the rcl to the solution
      current_result->addPoint(rcl_points[rand() % rcl_size]);
      if (i == 0) { // run only on first iteration cause then it points to the center
        delete[] center;
        center = current_result->getCenter();
      }
    }
    // Change the solutions if they are better
    if (current_result->getTotalDistance() > best_result->getTotalDistance()) {
      best_result->copy(current_result);
    }
    delete current_result;
  }
  return best_result;
}

