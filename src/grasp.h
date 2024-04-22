/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Grasp solver
 */

#ifndef GRASP_H
#define GRASP_H

#include "algorithm.h"
#include "problem.h"

class Grasp: public Algorithm {
public:
  /**
   * Constructor
   */
  Grasp(int iterations, int rcl_size);

  /**
   * Destructor
   */
  virtual ~Grasp() override {}

  /**
  * Solves a given problem
  * @param problem The problem to solve
  * @param solution_size The amount of points to include in the solution
  * @returns The found solution to the problem
  */
  virtual Solution* solve(const Problem* problem, int solution_size) const override;

private:
  int iterations;
  int rcl_size;
};

#endif

