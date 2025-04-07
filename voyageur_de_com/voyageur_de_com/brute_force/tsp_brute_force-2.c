#include "tools.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>

//
//  TSP - BRUTE-FORCE
//
// -> la structure "point" est définie dans "tools.h"
// -> tsp_main peut être testé dès les 3 premières fonctions codées
//

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

bool NextPermutation(int *P, int n) {
  if (n < 2) return false;

  // Étape 1 : trouver le plus grand i tel que P[i] < P[i+1]
  int i = n - 2;
  while (i >= 0 && P[i] >= P[i + 1]) i--;

  if (i < 0) return false; // dernière permutation atteinte

  // Étape 2 : trouver le plus grand j > i tel que P[j] > P[i]
  int j = n - 1;
  while (P[j] <= P[i]) j--;

  // Étape 3 : échanger P[i] et P[j]
  swap(&P[i], &P[j]);

  // Étape 4 : renverser la sous-liste P[i+1..n-1]
  int left = i + 1, right = n - 1;
  while (left < right) {
      swap(&P[left], &P[right]);
      left++;
      right--;
  }

  return true;
}



double dist(point A, point B) {
  double dx = A.x - B.x;
  double dy = A.y - B.y;
  return sqrt(dx * dx + dy * dy);
}

double value(point *V, int n, int *P) {
  double total = 0.0;
  for (int i = 0; i < n; i++) {
      total += dist(V[P[i]], V[P[(i + 1) % n]]);
  }
  return total;
}

double tsp_brute_force(point *V, int n, int *Q) {
  int P[n];
  for (int i = 0; i < n; i++) P[i] = i;

  double best = DBL_MAX;

  do {
      double val = value(V, n, P);
      if (val < best) {
          best = val;
          memcpy(Q, P, n * sizeof(int));
      }
  } while (NextPermutation(P, n));

  return best;
}

void MaxPermutation(int *P, int n, int k) {
  for (int i = k; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
          if (P[i] < P[j]) {
              int tmp = P[i];
              P[i] = P[j];
              P[j] = tmp;
          }
      }
  }
}

double value_opt(point *V, int n, int *P, double wmin) {
  double total = 0.0;

  for (int i = 0; i < n - 1; i++) {
      total += dist(V[P[i]], V[P[i + 1]]);
      if (total >= wmin) return -(i + 1); // on retourne -k
  }

  total += dist(V[P[n - 1]], V[P[0]]);
  if (total >= wmin) return -n; // dépasse avec le retour

  return total;
}

double tsp_brute_force_opt(point *V, int n, int *Q) {
  int P[n];
  for (int i = 0; i < n; i++) P[i] = i;

  double best = DBL_MAX;

  do {
      double val = value_opt(V, n, P, best);
      if (val >= 0 && val < best) {
          best = val;
          memcpy(Q, P, n * sizeof(int));
      } else if (val < 0) {
          int k = -val;
          MaxPermutation(P, n, k);
      }
  } while (NextPermutation(P + 1, n - 1)); // fixe P[0]

  return best;
}