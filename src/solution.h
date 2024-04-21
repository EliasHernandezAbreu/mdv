/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Solution class for representing a solution
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "problem.h"

class Solution {
public:
  /**
  * Builds a solution from a given problem size
  * @param problem The problem this solution is solution to
  */
  Solution(const Problem* problem);

  /**
  * Destroys a solution
  */
  ~Solution();

  /**
  * Prints the solution to the standard output
  */
  void print() const;

  /**
  * Gets the center of the points belonging to the solution
  * @returns An array with the centers of the points
  */
  float* getCenter() const;

  /**
  * Gets wether the solution has a point or not
  * @param index The point to check
  * @returns True if it has the point, false if not
  */
  bool hasPoint(int index) const;

  /**
  * Adds a point to the solution
  * @param index The position of the point to add
  */
  void addPoint(int index);

  /**
  * Removes a point from the solution
  * @param index The position of the point to remove
  */
  void removePoint(int index);

private:
  const Problem* problem;
  float* center;
  int size;
  bool* solution_points;
  float total_distance;
};

# endif
