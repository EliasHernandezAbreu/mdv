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

  /**
  * Gets the amount of points in the problem
  * @returns The amount of points in the problem
  */
  int getSize() const;

  /**
  * Gets the dimensions of the points
  * @returns The dimensions of the points
  */
  int getDimensions() const;

  /**
  * Gets the position of a point
  * @param index The index of the point to get the position from
  * @returns The position of a point
  */
  const double* getPosition(int index) const;

  /**
  * Gets the distance between two points
  * @param from The point from where
  * @param to The point to where
  * @returns The distance between the two points
  */
  double distance(int from, int to) const;

private:
  int size;
  int dimensions;
  double** positions;
  double** distances;
};

#endif
