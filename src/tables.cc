/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Generator of tables for the solutions
 */

#include <cstdio>
#include <ctime>

#include "algorithm.h"
#include "greedy.h"
#include "colors.h"

void greedyTable(int test_amount, const char** test_files) {
  Algorithm* solver = new Greedy();
  printf(UBOLD "%-24s %-2s %-1s %-2s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
         "z", "S", "CPU");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
    Problem test_problem = Problem(test_files[i]);
    long start_time = clock();
    Solution* solution = solver->solve(&test_problem, m);
    double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;

    printf("%-24s %-2d %-1d %-2d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
           test_problem.getDimensions(), m, solution->getTotalDistance(),
           solution->getPointsString(), ms_took);
    }
    puts("");
  }
}
