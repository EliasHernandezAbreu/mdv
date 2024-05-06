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
#include <cstdlib>

#include "bnb-node.h"
#include "problem.h"

BNBNode::BNBNode(const Problem* problem) {
  upper_bound = INFINITY;
  child_count = 0;
  nodes_in_solution = 0;
  children = nullptr;
  partial_solution = new char[problem->getSize()]();
}

BNBNode::~BNBNode() {
  delete [] partial_solution;
  if (children != nullptr)
    delete [] children;
}

BNBNode* BNBNode::expand(const Problem* problem, int target_solution_size) {
  child_count = problem->getSize() - nodes_in_solution;
  children = (BNBNode*)malloc(sizeof(BNBNode) * child_count);

  for (int counter = 0; counter < child_count; counter++) {
    children[counter] = BNBNode(problem);
    // CALCULATE THAT CHILD UPPER BOUND 
  }
  return children;
}
