/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Main file
 */

#include "algorithm.h"
#include "greedy.h"
#include "problem.h"

int main(int argc, char** argv) {
  const char test_files[6][24] = {
    "test/max_div_15_2.txt",
    "test/max_div_15_3.txt",
    "test/max_div_20_2.txt",
    "test/max_div_20_3.txt",
    "test/max_div_30_2.txt",
    "test/max_div_30_3.txt"
  };

  Algorithm* solver = new Greedy();
  Problem test_problem = Problem(test_files[0]);
  Solution* solution = solver->solve(&test_problem, 3);
  solution->print();
}
