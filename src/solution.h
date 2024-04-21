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

class Solution {
public:
  /**
  * Builds a solution from a given problem size
  * @param size The amount of points in total
  */
  Solution(int size);

  /**
  * Destroys a solution
  */
  ~Solution();

private:
  bool* solution_points;
  int size;
};

# endif
