/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Problem class for representing problems
 */

#include <cstdio>
#include <stdexcept>

#include "point.h"
#include "problem.h"

double readCommaFloat(FILE* input);

// Constructor
Problem::Problem(const char* file_path) {
  FILE* input = fopen(file_path, "r");
  if (input == nullptr) throw std::runtime_error("Input file not found");
  fscanf(input, "%d\n%d\n", &size, &dimensions);
  // Coordinates
  positions = new double*[size];
  for (int point = 0; point < size; point++) {
    positions[point] = new double[dimensions]();
    for (int coordinate = 0; coordinate < dimensions; coordinate++) {
      positions[point][coordinate] = readCommaFloat(input);
    }
  }
  // Distances
  distances = new double*[size];
  for (int i = 0; i < size; i++) {
    distances[i] = new double[size]();
    for (int j = 0; j < size; j++) {
      distances[i][j] = distanceBetween(dimensions, positions[i], positions[j]);
    }
  }
}

// Destructor
Problem::~Problem() {
  if (positions != nullptr) {
    for (int i = 0; i < size; i++)
      delete[] positions[i];
    delete[] positions;
  }
  if (distances != nullptr) {
    for (int i = 0; i < size; i++)
      delete[] distances[i];
    delete[] distances;
  }
}

int Problem::getSize() const {
  return size;
}

int Problem::getDimensions() const {
  return dimensions;
}

const double* Problem::getPosition(int index) const {
  return positions[index];
}

double Problem::distance(int from, int to) const {
  return distances[from][to];
}

// Helper functions

// Read a comma separated double instead of point sepparated
double readCommaFloat(FILE* input) {
  int base, decimal;
  fscanf(input, "%d,", &base);
  int decimal_size = fscanf(input, "%d", &decimal);
  return double(base) + double(decimal) / double(decimal_size * 100);
}
