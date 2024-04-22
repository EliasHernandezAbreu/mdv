/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Grasp solver with local searches
 */

#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "algorithm.h"
#include "problem.h"

class LocalSearchGrasp: public Algorithm {
public:
  /**
   * Constructor
   */
  LocalSearchGrasp(int iterations, int rcl_size);

  /**
   * Destructor
   */
  virtual ~LocalSearchGrasp() override {}

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


