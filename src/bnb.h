/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Class for representing a branch and bound solver
 */

#ifndef BRANCHNBOUND_H
#define BRANCHNBOUND_H

#define LOWER_BOUND_MODE_GREEDY 0
#define LOWER_BOUND_MODE_GRASP 1
#define LOWER_BOUND_MODE_NONE 2

#define BRANCHING_STRATEGY_LOWEST_UPPER_BOUND 0
#define BRANCHING_STRATEGY_DEEPEST_NODE  1

#include "algorithm.h"
#include "problem.h"
#include "solution.h"

class BranchNBound: public Algorithm {
public:
  /**
   * Creates a branch and bound solver
   * @param lower_bound_mode The algorithm used to find lower bounds
   * @param branching_strategy The strategy used to select the next node
   */
  BranchNBound(char lower_bound_mode, char branching_strategy);

  /**
   * Destructor
   */
  virtual ~BranchNBound() {}

  /**
   * Gets the amount of nodes the algorithm generated
   * @returns The amount of nodes generated
   */
  int getNodeAmount() { return node_amount; }

  /**
  * Solves a given problem
  * @param problem The problem to solve
  * @param solution_size The amount of points to include in the solution
  * @returns The found solution to the problem
  */
  Solution* solve(const Problem* problem, int solution_size) override;

private:
  int node_amount;
  char lower_bound_mode;
  char branching_strategy;
};

#endif

