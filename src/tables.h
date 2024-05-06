/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Generator of tables for the solutions
 */

#ifndef TABLES_H
#define TABLES_H

// Generate all tables
void allTables(int test_amount, const char** test_files);
// Generate tables for greedy algorithm
void greedyTable(int test_amount, const char** test_files);
// Generate tables for greedy algorithm with local search
void localSearchGraspTable(int test_amount, const char** test_files);
// Generate tables for greedy algorithm
void graspTable(int test_amount, const char** test_files);
// Generate tabu search tables
void tabuTable(int test_amount, const char** test_files);
// Generate branch and bound search tables
void bnbTable(int test_amount, const char** test_files);

#endif
