/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Problem class for representing problems
 */

#ifndef PROBLEM_H
#define PROBLEM_H

class Problem {
public:
  /**
  * Constructs a problem with each point positions and distances between them
  * @param file_path The path to the file with the problem
  */
  Problem(const char* file_path);

  /**
  * Destructs the problem
  */
  ~Problem();

private:
  int size;
  int dimensions;
  float** positions;
  float** distances;
};

#endif
