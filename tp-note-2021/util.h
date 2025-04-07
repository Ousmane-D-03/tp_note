#include "tools.h"

// Macro pour simplifier les expressions de calcul des distances
#define D(a, b) (dist(V[P[a]], V[P[b]]))

double dist(point A, point B);

double value(point *V, int n, int *P);

void print_tab(int *P, int n);

// Tests

void print_points(FILE *f, point *V, int n);

void print_perm(FILE *f, int *P, int n);

void print_points_and_perm(FILE *f, point *V, int *P, int n);

point *copy_points(point *V, int n);

int *copy_perm(int *P, int n);

bool equal_tabs(int *P, int *Q, int n);

void scramble_tab(int *P, int n);

void random_perm(int *P, int n);
