/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Greedy solver
 */

#ifndef GREEDY_H
#define GREEDY_H

#include "algorithm.h"
#include "problem.h"

class Greedy: public Algorithm {
public:
  /**
  * Solves a given problem
  * @param problem The problem to solve
  * @param solution_size The amount of points to include in the solution
  * @returns The found solution to the problem
  */
  virtual Solution* solve(const Problem* problem, int solution_size) const override;
};

#endif
