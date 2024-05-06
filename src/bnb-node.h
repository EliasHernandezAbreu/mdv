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
#include <vector>

class BNBNode {
public:
  /**
   * Creates a bnb node using the problem as a reference
   * @param problem The problem to take info from
   */
  BNBNode(const Problem* problem);

  /**
   * Creates a bnb node
   */
  BNBNode();

  /**
   * Removes the node, deleting all it's children
   */
  ~BNBNode();

  /**
   * Get the lower bound
   * @returns The lower bound
   */
  double getUpperBound() const { return upper_bound; }

  /**
   * Get the child amount
   * @returns The child amount
   */
  double getChildAmount() const { return child_count; }

  /**
   * Gets the nodes in the solution
   * @returns The amount of nodes in the solution
   */
  int getNodeCountInSolution() const { return nodes_in_solution; }

  /**
   * Gets the solution
   * @returns The solution
   */
  const char* getPartialSolution() const { return partial_solution; }

  /**
   * Sets the solution and calculates the upper bound
   * @param new_solution The new solution
   * @param problem The problem to get info from
   */
  void setPartialSolution(char* new_solution, const Problem* problem, int target_solution_size);

  /**
   * Expands the node, creating its children
   * @param problem The problem to fetch info from
   * @returns The childs generated
   */
  std::vector<BNBNode> expand(const Problem* problem, int target_solution_size);

  /**
   * Copies another branch and bound node
   */
  void operator=(const BNBNode& other);

private:
  double upper_bound;
  int child_count;
  int nodes_in_solution;
  std::vector<BNBNode> children;
  char* partial_solution;
  int problem_size;
};

#endif
