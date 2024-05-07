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
#include "bnb-node.h"
#include "grasp.h"
#include "greedy.h"
#include "colors.h"
#include "local-search-grasp.h"
#include "tabu.h"
#include "bnb.h"
#include "tables.h"

void greedyTable(int test_amount, const char** test_files) {
  Algorithm* solver = new Greedy();
  FILE* out = fopen("table-greedy.txt", "w");
  fprintf(out, UBOLD "%-24s %-3s %-2s %-3s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
         "z", "S", "CPU");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
    Problem test_problem = Problem(test_files[i]);
    long start_time = clock();
    Solution* solution = solver->solve(&test_problem, m);
    double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;

    fprintf(out, "%-24s %-3d %-2d %-3d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
           test_problem.getDimensions(), m, solution->getTotalDistance(),
           solution->getPointsString(), ms_took);
    }
    fputs("\n", out);
  }
  fclose(out);
}

void graspTable(int test_amount, const char** test_files) {
  FILE* out = fopen("table-grasp.txt", "w");
  fprintf(out, UBOLD "%-24s %-3s %-2s %-3s %-4s %-6s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
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

          fprintf(out, "%-24s %-3d %-2d %-3d %-4d %-6d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
                 test_problem.getDimensions(), m, it, rcl_size, solution->getTotalDistance(),
                 solution->getPointsString(), ms_took);
          delete solver;
        }
      }
    }
    fputs("\n", out);
  }
  fclose(out);
}

void localSearchGraspTable(int test_amount, const char** test_files) {
  FILE* out = fopen("table-ls.txt", "w");
  fprintf(out, UBOLD "%-24s %-3s %-2s %-3s %-4s %-6s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
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

          fprintf(out, "%-24s %-3d %-2d %-3d %-4d %-6d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
                 test_problem.getDimensions(), m, it, rcl_size, solution->getTotalDistance(),
                 solution->getPointsString(), ms_took);
          delete solver;
        }
      }
    }
    fputs("\n", out);
  }
}

void tabuTable(int test_amount, const char** test_files) {
  FILE* out = fopen("table-tabu.txt", "w");
  fprintf(out, UBOLD "%-24s %-3s %-2s %-3s %-4s %-11s %-14s %-20s %-16s" CLEAR "\n", "Problema", "n", "K", "m",
         "iter", "tabutenure", "z", "S", "CPU");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
      for (int it = 10; it <= 20; it += 10) {
        for (int tabu_tenure = 2; tabu_tenure <= 3; tabu_tenure++) {
          Algorithm* solver = new Tabu(it, 3, tabu_tenure);
          Problem test_problem = Problem(test_files[i]);
          long start_time = clock();
          Solution* solution = solver->solve(&test_problem, m);
          double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;

          fprintf(out, "%-24s %-3d %-2d %-3d %-4d %-11d %-14f %-20s %f ms\n", test_files[i], test_problem.getSize(),
                 test_problem.getDimensions(), m, it, tabu_tenure, solution->getTotalDistance(),
                 solution->getPointsString(), ms_took);
          delete solver;
        }
      }
    }
    fputs("\n", out);
  }
}

void bnbTable(int test_amount, const char** test_files, char branch_mode, char lower_bound_mode, const char* save_to) {
  // Can't use polymorphism with this one since we need the generated nodes amount
  BranchNBound* solver = new BranchNBound(lower_bound_mode, branch_mode);
  FILE* out = fopen(save_to, "w");
  fprintf(out, UBOLD "%-24s %-3s %-2s %-3s %-14s %-20s %-16s    %16s" CLEAR "\n",
          "Problema", "n", "K", "m", "z", "S", "CPU", "nodos generados");
  for (int i = 0; i < test_amount; i++) {
    for (int m = 2; m <= 5; m++) {
      printf("starting problem %s\n", test_files[i]);
    Problem test_problem = Problem(test_files[i]);
    long start_time = clock();
    Solution* solution = solver->solve(&test_problem, m);
    double ms_took = double(clock() - start_time) / double(CLOCKS_PER_SEC) * 1000;
    fprintf(out, "%-24s %-3d %-2d %-3d %-14f %-20s %f ms %16d\n", test_files[i], test_problem.getSize(),
           test_problem.getDimensions(), m, solution->getTotalDistance(),
           solution->getPointsString(), ms_took, solver->getNodeAmount());
    }
    fputs("\n", out);
  }
  fclose(out);
}

void allTables(int test_amount, const char** test_files) {
  puts(NEG "greedy..." CLEAR);
  greedyTable(test_amount, test_files);
  puts(NEG "grasp..." CLEAR);
  graspTable(test_amount, test_files);
  puts(NEG "local search..." CLEAR);
  localSearchGraspTable(test_amount, test_files);
  puts(NEG "tabu search..." CLEAR);
  tabuTable(test_amount, test_files);
  puts(NEG "branch and bound depth none..." CLEAR);
  bnbTable(test_amount, test_files, BRANCHING_STRATEGY_DEEPEST_NODE, LOWER_BOUND_MODE_NONE, "bnb-depth-none.txt");
  puts(NEG "branch and bound depth greedy..." CLEAR);
  bnbTable(test_amount, test_files, BRANCHING_STRATEGY_DEEPEST_NODE, LOWER_BOUND_MODE_GREEDY, "bnb-depth-greedy.txt");
  puts(NEG "branch and bound depth grasp..." CLEAR);
  bnbTable(test_amount, test_files, BRANCHING_STRATEGY_DEEPEST_NODE, LOWER_BOUND_MODE_GRASP, "bnb-depth-grasp.txt");
  puts(NEG "branch and bound bound greedy..." CLEAR);
  bnbTable(test_amount, test_files, BRANCHING_STRATEGY_LOWEST_UPPER_BOUND, LOWER_BOUND_MODE_GREEDY, "bnb-bound-greedy.txt");
  puts(NEG "branch and bound bound grasp..." CLEAR);
  bnbTable(test_amount, test_files, BRANCHING_STRATEGY_LOWEST_UPPER_BOUND, LOWER_BOUND_MODE_GRASP, "bnb-bound-grasp.txt");
}
