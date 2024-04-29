/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Tabu search
 */

#include <cstdlib>
#include <ctime>

#include "grasp.h"
#include "tabu.h"
#include "problem.h"
#include "solution.h"

Tabu::Tabu(int iterations, int rcl_size) {
  this->iterations = iterations;
  this->rcl_size = rcl_size;
}

Solution* Tabu::solve(const Problem* problem, int solution_size) const {
  srand(clock());
  Grasp grasp_solver(iterations, rcl_size);
  Solution* best_result = grasp_solver.solve(problem, solution_size);

  int tabu_table[problem->getSize()][problem->getSize()];

  // Improve with local search
  float best_increment = 1;
  while (best_increment > 0) {
    int best_remove = 0;
    int best_add = 0;
    best_increment = 0;
    for (int remove = 0; remove < problem->getSize(); remove++) {
      if (!best_result->hasPoint(remove)) continue;
      for (int add = 0; add < problem->getSize(); add++) {
        if (best_result->hasPoint(add)) continue;
        float current_increment = -best_result->getTotalDistance();
        best_result->removePoint(remove);
        best_result->addPoint(add);
        current_increment += best_result->getTotalDistance();
        best_result->removePoint(add);
        best_result->addPoint(remove);
        if (current_increment > best_increment) {
          best_increment = current_increment;
          best_add = add;
          best_remove = remove;
        }
      }
    }
    if (best_increment > 0) {
      best_result->removePoint(best_remove);
      best_result->addPoint(best_add);
    }
  }
  
  return best_result;
}



