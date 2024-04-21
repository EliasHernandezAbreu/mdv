/**
 * DAA - P8
 * Maximum diversity problem
 * 
 * @author Elías Hernández Abreu
 * @since 21 / 4 / 2024
 *
 * @file Greedy solver
 */

#ifndef GREEDY_H
#define GREEDY_H

#include "algorithm.h"
#include "problem.h"

class Greedy: public Algorithm {
public:
  virtual Solution* solve(const Problem* problem) const override;
};

#endif
