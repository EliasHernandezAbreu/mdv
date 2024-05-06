/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Class for representing a branch and bound solver
 */

#include "bnb.h"
#include "problem.h"
#include "solution.h"

BranchNBound::BranchNBound(char lower_bound_mode, char branching_strategy) {
  this->lower_bound_mode = lower_bound_mode;
  this->branching_strategy = branching_strategy;
  node_amount = 0;
}

Solution* BranchNBound::solve(const Problem* problem, int solution_size) {
  Solution* result = new Solution(problem);
  return result;
}
