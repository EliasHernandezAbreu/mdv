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

struct Movement {
  double increment;
  int in;
  int out;
};

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
   * Copies another solution
   * @param other The solution to copy
   */
  void copy(const Solution* other);

  /**
  * Prints the solution to the standard output
  */
  void print() const;

  /**
   * Gets the problem of the solution
   * @returns The problem of the solution
   */
  const Problem* getProblem() const { return problem; }

  /**
  * Gets the total distance of the solution
  * @returns The total distance
  */
  double getTotalDistance() const;

  /**
  * Gets the real total distance of the solution
  * @returns The real total distance
  */
  double confirmTotalDistance() const;

  /**
   * Reloads the total distance to avoid precission problems
   */
  void reloadTotalDistance();

  /**
  * Get points as string
  * @returns The points as a string
  */
  char* getPointsString() const;

  /**
  * Gets the center of the points belonging to the solution
  * @returns An array with the centers of the points
  */
  double* getCenter() const;

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

  /**
  * Evaluates the given movement and returns its increment
  * @param out The point to remove in the movement
  * @param in The point to add in the movement
  * @returns Its increment
  */
  double evaluateMovement(int out, int in);

  /**
  * Does the given movement()
  * @param movement The movement to do 
  */
  void doMovement(Movement* movement);

private:
  const Problem* problem;
  double* center;
  int size;
  char* solution_points;
  double total_distance;
};

# endif
