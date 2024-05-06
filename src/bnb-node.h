/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Class for representing a bnb node
 */

#ifndef BNB_NODE
#define BNB_NODE

#include "problem.h"

class BNBNode {
public:
  /**
   * Creates a bnb node using the problem as a reference
   * @param problem The problem to take info from
   */
  BNBNode(const Problem* problem);

  /**
   * Removes the node, deleting all it's children
   */
  ~BNBNode();

  /**
   * Get the lower bound
   * @returns The lower bound
   */
  double getUpperBound() { return upper_bound; }

  /**
   * Get the child amount
   * @returns The child amount
   */
  double getChildAmount() { return child_count; }

  /**
   * Gets the nodes in the solution
   * @returns The amount of nodes in the solution
   */
  int getNodeCountInSolution() { return nodes_in_solution; }

  /**
   * Gets the solution
   * @returns The solution
   */
  char* getPartialSolution() { return partial_solution; }

  /**
   * Expands the node, creating its children
   * @param problem The problem to fetch info from
   * @returns The childs generated
   */
  BNBNode* expand(const Problem* problem, int target_solution_size);

private:
  double upper_bound;
  int child_count;
  int nodes_in_solution;
  BNBNode* children;
  char* partial_solution;
};

#endif
