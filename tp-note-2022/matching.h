#ifndef MATCHING_H
#define MATCHING_H

#include "tools.h"

double matching_basic(point *V, graph M);
double matching_greedy(point *V, graph M);
double matching_rectangle(point *V, graph M);
bool   matching_flip(point *V, graph M);
double weight(point *V, graph G);

#endif /* MATCHING */
