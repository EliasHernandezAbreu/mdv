/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Class for representing an algorithm
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "problem.h"
#include "solution.h"

class Algorithm {
public:
  /**
  * Solves a given problem
  * @param problem The problem to solve
  * @param solution_size The amount of points to include in the solution
  * @returns The found solution to the problem
  */
  virtual Solution* solve(const Problem* problem, int solution_size) const = 0;
};

#endif
