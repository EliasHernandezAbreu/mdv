/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Class for representing a branch and bound solver
 */

#include <cstdio>
#include <cstdlib>
#include <vector>

#include "bnb.h"
#include "bnb-node.h"
#include "grasp.h"
#include "greedy.h"
#include "problem.h"
#include "solution.h"

BranchNBound::BranchNBound(char lower_bound_mode, char branching_strategy) {
  this->lower_bound_mode = lower_bound_mode;
  this->branching_strategy = branching_strategy;
  node_amount = 0;
}

Solution* BranchNBound::solve(const Problem* problem, int solution_size) {
  double lower_bound;
  if (lower_bound_mode == LOWER_BOUND_MODE_GREEDY) {
    Solution* tmp = Greedy().solve(problem, solution_size);
    lower_bound = tmp->getTotalDistance();
    delete tmp;
  } else if (lower_bound_mode == LOWER_BOUND_MODE_GRASP) {
    Solution* tmp = Grasp(100, 3).solve(problem, solution_size);
    lower_bound = tmp->getTotalDistance();
    delete tmp;
  } else if (lower_bound_mode == LOWER_BOUND_MODE_NONE) {
    lower_bound = -1;
  } else {
    printf("lower bound mode not recognized: %d\n", lower_bound_mode);
    exit(1);
  }
  Solution* result = new Solution(problem);
  std::vector<BNBNode> open_nodes;
  BNBNode root(problem);
  open_nodes.reserve(problem->getSize() * problem->getSize());
  open_nodes.push_back(root);

  if (branching_strategy == BRANCHING_STRATEGY_DEEPEST_NODE) {
    while (!open_nodes.empty()) {
      // printf("stack size: %lu\n", open_nodes.size());
      BNBNode current_node = open_nodes.back();
      open_nodes.pop_back();
      if (current_node.getUpperBound() <= lower_bound) {
        // printf("lower than lower bound %f < %f\n", current_node.getUpperBound(), lower_bound);
        continue;
      }
      if (current_node.getNodeCountInSolution() == solution_size) {
        lower_bound = current_node.getUpperBound();
        result->copy(&current_node);
      }
      std::vector<BNBNode> children = current_node.expand(problem, solution_size);
      for (int counter = 0; counter < current_node.getChildAmount(); counter++) {
        open_nodes.push_back(children[counter]);
      }
    }

  } else if (branching_strategy == BRANCHING_STRATEGY_LOWEST_UPPER_BOUND) {
    while (!open_nodes.empty()) {
      long unsigned int best_node_pos = 0;
      for (long unsigned int current_pos = 0; current_pos < open_nodes.size(); current_pos++) {
        if (open_nodes[current_pos].getUpperBound() < open_nodes[best_node_pos].getUpperBound()) {
          best_node_pos = current_pos;
        }
      }
      BNBNode current_node = open_nodes[best_node_pos];
      open_nodes.erase(open_nodes.begin() + best_node_pos);
      if (current_node.getUpperBound() <= lower_bound) continue;
      if (current_node.getNodeCountInSolution() == solution_size) {
        lower_bound = current_node.getUpperBound();
        result->copy(&current_node);
      }
      std::vector<BNBNode> children = current_node.expand(problem, solution_size);
      for (int counter = 0; counter < current_node.getChildAmount(); counter++) {
        open_nodes.push_back(children[counter]);
      }
    }
  }

  printf("solution %f\n", result->confirmTotalDistance());
  return result;
}
