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
#include "grasp.h"
#include "greedy.h"
#include "colors.h"
#include "local-search-grasp.h"
#include "tables.h"

void greedyTable(int test_amount, const char** test_files) {
  Algorithm* solver = new Greedy();
  printf(UBOLD "%-24s %-3s %-2s %-3s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
         "z", "S", "CPU");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
    Problem test_problem = Problem(test_files[i]);
    long start_time = clock();
    Solution* solution = solver->solve(&test_problem, m);
    double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;

    printf("%-24s %-3d %-2d %-3d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
           test_problem.getDimensions(), m, solution->getTotalDistance(),
           solution->getPointsString(), ms_took);
    }
    puts("");
  }
}

void graspTable(int test_amount, const char** test_files) {
  printf(UBOLD "%-24s %-3s %-2s %-3s %-4s %-6s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
         "iter", "|LRC|", "z", "S", "CPU");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
      for (int it = 10; it <= 20; it += 10) {
        for (int rcl_size = 2; rcl_size <= 3; rcl_size++) {
          Algorithm* solver = new Grasp(it, rcl_size);
          Problem test_problem = Problem(test_files[i]);
          long start_time = clock();
          Solution* solution = solver->solve(&test_problem, m);
          double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;

          printf("%-24s %-3d %-2d %-3d %-4d %-6d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
                 test_problem.getDimensions(), m, it, rcl_size, solution->getTotalDistance(),
                 solution->getPointsString(), ms_took);
          delete solver;
        }
      }
    }
    puts("");
  }
}

void localSearchGraspTable(int test_amount, const char** test_files) {
  printf(UBOLD "%-24s %-3s %-2s %-3s %-4s %-6s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
         "iter", "|LRC|", "z", "S", "CPU");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
      for (int it = 10; it <= 20; it += 10) {
        for (int rcl_size = 2; rcl_size <= 3; rcl_size++) {
          Algorithm* solver = new LocalSearchGrasp(it, rcl_size);
          Problem test_problem = Problem(test_files[i]);
          long start_time = clock();
          Solution* solution = solver->solve(&test_problem, m);
          double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;

          printf("%-24s %-3d %-2d %-3d %-4d %-6d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
                 test_problem.getDimensions(), m, it, rcl_size, solution->getTotalDistance(),
                 solution->getPointsString(), ms_took);
          delete solver;
        }
      }
    }
    puts("");
  }
}

void allTables(int test_amount, const char** test_files) {
  puts(NEG "GREEDY:" CLEAR);
  greedyTable(test_amount, test_files);
  puts(NEG "GRASP:" CLEAR);
  graspTable(test_amount, test_files);
  puts(NEG "LOCAL SEARCH:" CLEAR);
  localSearchGraspTable(test_amount, test_files);
}
