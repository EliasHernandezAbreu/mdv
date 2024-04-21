/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Problem class for representing problems
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

#include "problem.h"

float readCommaFloat(FILE* input);

// Constructor
Problem::Problem(const char* file_path) {
  FILE* input = fopen(file_path, "r");
  if (input == nullptr) throw std::runtime_error("Input file not found");
  fscanf(input, "%d\n%d\n", &size, &dimensions);
  // Coordinates
  positions = new float*[size];
  for (int point = 0; point < size; point++) {
    positions[point] = new float[dimensions]();
    for (int coordinate = 0; coordinate < dimensions; coordinate++) {
      positions[point][coordinate] = readCommaFloat(input);
    }
  }
  // Distances
  distances = new float*[size];
  for (int i = 0; i < size; i++) {
    distances[i] = new float[size]();
    for (int j = 0; j < size; j++) {
      float distance = 0;
      for (int dim = 0; dim < dimensions; dim++) {
        distance += powf(positions[i][dim] - positions[j][dim], 2);
      }
      distance = sqrtf(distance);
      distances[i][j] = distance;
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

// Helper functions

// Read a comma separated float instead of point sepparated
float readCommaFloat(FILE* input) {
  int base, decimal;
  fscanf(input, "%d,", &base);
  int decimal_size = fscanf(input, "%d", &decimal);
  return float(base) + float(decimal) / float(decimal_size * 100);
}
