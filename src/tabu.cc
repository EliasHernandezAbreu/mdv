/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Tabu search
 */

// #define DEBUG

#include <cmath>
#ifdef  DEBUG
  #include <cstdlib>
  #include <cstdio>
#endif
#include <cstring>

#include "grasp.h"
#include "tabu.h"
#include "problem.h"
#include "solution.h"

// Gets the best neighbor solutions from a given solution
void getTopCandidates(Solution* from_solution, int candidate_size, Movement* candidates);
// Gets the worst candidate from a candidate list
int getWorstCandidate(int candidate_size, Movement* candidates);
// Sorts the movements from best to worst
void sort(int size, Movement* movements_to_sort);
// Updates the tenures of the table
void updateTableTenures(int n, int m, int** table);


Tabu::Tabu(int iterations, int rcl_size, int tabu_tenure) {
  this->tabu_tenure = tabu_tenure;
  this->iterations = iterations;
  this->rcl_size = rcl_size;
}

Solution* Tabu::solve(const Problem* problem, int solution_size) const {
  // Get initial solution from grasp algorithm
  Grasp grasp_solver(iterations, rcl_size);
  Solution* best_solution = grasp_solver.solve(problem, solution_size);
  Solution current_solution(problem);
  current_solution.copy(best_solution);

  // Initialize tabu table and candidate table
  int** tabu_table = new int*[problem->getSize()];
  for (int i = 0; i < problem->getSize(); i++) {
    tabu_table[i] = new int[problem->getSize()]();
  }
  const int candidate_size = 5;
  Movement candidates[candidate_size]; // Candidates
  for (int i = 0; i < candidate_size; i++) {
    candidates[i].increment = -INFINITY;
  }

  // Max iterations of the algorithm
  for (int iteration = 0; iteration < iterations; iteration++) {
    #ifdef DEBUG
    printf("\ntarget solution size: %d Best solution:\n", solution_size);
    best_solution->print();
    printf("Current solution:\n");
    current_solution.print();
    if (best_solution->getTotalDistance() != best_solution->confirmTotalDistance()) {
      printf("got %f confirmed %f\n", best_solution->getTotalDistance(), best_solution->confirmTotalDistance());
      exit(1);
    };
    #endif
    
    // Update tabu table tenures
    updateTableTenures(problem->getSize(), problem->getSize(), tabu_table);
    getTopCandidates(&current_solution, candidate_size, candidates);
    // Gets the best candidate that isnt tabu, unless its the best thing ever
    for (int current_candidate_index = 0; current_candidate_index < candidate_size; current_candidate_index++) {
      Movement current_candidate = candidates[current_candidate_index];
      // Check if this solution is better than the best
      if (current_solution.getTotalDistance() + current_candidate.increment > best_solution->getTotalDistance()) {
        #ifdef DEBUG
        printf("Doing coolest movement: remove %d add %d\n", current_candidate.out, current_candidate.in);
        #endif
        current_solution.doMovement(&current_candidate);
        best_solution->copy(&current_solution);
        tabu_table[current_candidate.out][current_candidate.in] = tabu_tenure;
        break;
      }

      // If tabu movement skip
      if (tabu_table[current_candidate.in][current_candidate.out] > 0
      || tabu_table[current_candidate.out][current_candidate.in] > 0) continue;
      
      // Just set this to the current one
      #ifdef DEBUG
      printf("Doing movement: remove %d add %d\n", current_candidate.out, current_candidate.in);
      #endif
      current_solution.doMovement(&current_candidate);
      tabu_table[current_candidate.out][current_candidate.in] = tabu_tenure;
      break;
    }
  }
  
  // Return solution
  for (int i = 0; i < problem->getSize(); i++) {
    delete[] tabu_table[i];
  }
  delete[] tabu_table;
  best_solution->reloadTotalDistance();
  return best_solution;
}

// HELPER FUNCTIONS ===============================================================================

void getTopCandidates(Solution* from_solution, int candidate_size, Movement* candidates) {
  // Reset candidate list
  for (int i = 0; i < candidate_size; i++) candidates[i].increment = -INFINITY;

  // Iterate every movement posibility
  for (int in = 0; in < from_solution->getProblem()->getSize(); in++) {
    if (from_solution->hasPoint(in)) continue;
    for (int out = 0; out < from_solution->getProblem()->getSize(); out++) {
      if (!from_solution->hasPoint(out) || in == out) continue;

      // Evaluate movement and swap if its better than the worst in the candidates
      float this_increment = from_solution->evaluateMovement(out, in);
      int worst_candidate = getWorstCandidate(candidate_size, candidates);
      if (this_increment > candidates[worst_candidate].increment) {
        candidates[worst_candidate].increment = this_increment;
        candidates[worst_candidate].in = in;
        candidates[worst_candidate].out = out;
      }
    }
  }
  sort(candidate_size, candidates);
}

int getWorstCandidate(int candidate_size, Movement* candidates) {
  int worst_index = 0;
  float worst_increment = candidates[worst_index].increment;
  for (int current_candidate = 0; current_candidate < candidate_size; current_candidate++) {
    if (candidates[current_candidate].increment < worst_increment) {
      worst_index = current_candidate;
      worst_increment = candidates[current_candidate].increment;
    }
  }
  return worst_index;
}

void sort(int size, Movement* movements_to_sort) {
  for (int place_index = 0; place_index < size - 1; place_index++) {
    for (int get_index = place_index + 1; get_index < size; get_index++) {
      if (movements_to_sort[get_index].increment <= movements_to_sort[place_index].increment) continue;
      Movement temp;
      memcpy(&temp, movements_to_sort + place_index, sizeof(Movement));
      memcpy(movements_to_sort + place_index, movements_to_sort + get_index, sizeof(Movement));
      memcpy(movements_to_sort + get_index, &temp, sizeof(Movement));
    }
  }
}

void updateTableTenures(int n, int m, int** table) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (table[i][j] > 0) table[i][j]--;
    }
  }
}
