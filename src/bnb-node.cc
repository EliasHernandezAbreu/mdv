/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Class for representing a bnb node
 */

#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

#include "bnb-node.h"
#include "point.h"
#include "problem.h"

BNBNode::BNBNode(const Problem* problem) {
  upper_bound = INFINITY;
  child_count = 0;
  nodes_in_solution = 0;
  problem_size = problem->getSize();
  children = std::vector<BNBNode>(0);
  partial_solution = new char[problem->getSize()]();
}

BNBNode::BNBNode() {
  upper_bound = INFINITY;
  child_count = 0;
  nodes_in_solution = 0;
  problem_size = 0;
  children = std::vector<BNBNode>(0);
  partial_solution = new char[0]();
}

BNBNode::~BNBNode() {
  // delete [] partial_solution;
}

void BNBNode::operator=(const BNBNode& other) {
  upper_bound = other.upper_bound;
  child_count = other.child_count;
  nodes_in_solution = other.nodes_in_solution;
  children = other.children;
  problem_size = other.problem_size;
  partial_solution = new char[problem_size];
  memcpy(partial_solution, other.partial_solution, sizeof(char) * problem_size);
}

std::vector<BNBNode> BNBNode::expand(const Problem* problem, int target_solution_size) {
  child_count = problem->getSize() - nodes_in_solution;
  children = std::vector<BNBNode>(child_count);

  int assigned_point = 0;
  for (int counter = 0; counter < child_count; counter++) {
    while (partial_solution[assigned_point] > 0) assigned_point++;
    children[counter] = BNBNode(problem);
    partial_solution[assigned_point] = 1;
    children[counter].setPartialSolution(partial_solution, problem, target_solution_size);
    partial_solution[assigned_point] = 0;
    assigned_point++;
  }
  // printf("new children size: %lu\n", children.size());
  return children;
}

void BNBNode::setPartialSolution(char* new_solution, const Problem* problem, int target_solution_size) {
  // Calculate defined diversity
  upper_bound = 0;
  for (int counter = 0; counter < problem->getSize(); counter++) {
    if (new_solution[counter] == 0) continue;
    if (partial_solution[counter] > 0) continue;

    for (int p = 0; p < problem->getSize(); p++) {
      if (partial_solution[p] == 0) continue;
      upper_bound += distanceBetween(problem->getDimensions(), 
                                        problem->getPosition(p),
                                        problem->getPosition(counter));
    }
    nodes_in_solution++;
    partial_solution[counter]++;
  }
  // Add max possible diversity
  double pseudo_mean_diversity;
  for (int node_in = 0; node_in < problem->getSize(); node_in++) {
    if (partial_solution[node_in] == 0) continue;
    for (int node_out = 0; node_out < problem->getSize(); node_out++) {
      if (partial_solution[node_out] > 0) continue;
      double current_pseudo_diversity = distanceBetween(problem->getDimensions(), 
                                        problem->getPosition(node_in),
                                        problem->getPosition(node_out));
      if (current_pseudo_diversity > pseudo_mean_diversity) {
        pseudo_mean_diversity = current_pseudo_diversity;
      }
    }
  }
  // This should be explained in more detail in the report
  if (nodes_in_solution != target_solution_size) {
    double mpd = pseudo_mean_diversity;
    double fraction = (double)(target_solution_size - 1 + nodes_in_solution) / 2;
    double times = target_solution_size - nodes_in_solution + 1;
    upper_bound += mpd * fraction * times;
    // for (int i = 0; i < problem_size; i++) printf("%d ", partial_solution[i]); puts("");
  }
}
