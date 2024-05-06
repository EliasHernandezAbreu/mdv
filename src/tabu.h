/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Tabu solver
 */

#ifndef TABU_H
#define TABU_H

#include "algorithm.h"
#include "problem.h"

class Tabu: public Algorithm {
public:
  /**
   * Constructor
   */
  Tabu(int iterations, int rcl_size, int tabu_tenure);

  /**
   * Destructor
   */
  virtual ~Tabu() override {}

  /**
  * Solves a given problem
  * @param problem The problem to solve
  * @param solution_size The amount of points to include in the solution
  * @returns The found solution to the problem
  */
  virtual Solution* solve(const Problem* problem, int solution_size) override;

private:
  int iterations;
  int rcl_size;
  int tabu_tenure;
};

#endif


