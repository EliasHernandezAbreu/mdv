/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Main file
 */

#include "tables.h"

int main(int argc, char** argv) {
  const char* test_files[6] = {
    "test/max_div_15_2.txt",
    "test/max_div_15_3.txt",
    "test/max_div_20_2.txt",
    "test/max_div_20_3.txt",
    "test/max_div_30_2.txt",
    "test/max_div_30_3.txt"
  };

  greedyTable(6, test_files);
}
