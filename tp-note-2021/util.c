#include "util.h"

// Distance Euclidienne
double dist(point A, point B) {
    const double x = A.x - B.x;
    const double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

// Valeur de la tournée
double value(point *V, int n, int *P) {
    double w = 0;
    for (int i = 0; i < n - 1; i++)
        w += D(i, i + 1);
    return w + D(n - 1, 0);
}

// Affiche le tableau d'entiers P
void print_tab(int *P, int n) {
    for (int i = 0; i < n; ++i) {
        fprintf(stderr, "%d ", P[i]);
    }
    fprintf(stderr, "\n");
}

// Affiche le tableau d'entiers P
void print_points(FILE *f, point *V, int n) {
    for (int i = 0; i < n; ++i) {
       fprintf(f, "V[%2d] = (%-3.2f, %-3.2f)\n", i, V[i].x, V[i].y);
    }
    fprintf(f, "\n");
}

void print_perm(FILE *f, int *P, int n) {
    fprintf(f, "\n");
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%-3d ", i);
    }
    fprintf(f, "\n");
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%2d, ", P[i]);
    }
    fprintf(f, "\n");
}

void print_points_and_perm(FILE *f, point *V, int *P, int n) {
   print_perm(f, P, n);
   fprintf(f, "\n");
   print_points(f, V, n);
}

point *copy_points(point *V, int n){
   point *Vbis = malloc(n * sizeof(point));
   for (int i = 0; i < n; ++i) {
      Vbis[i] = V[i];
   }
   return Vbis;
}

int *copy_perm(int *P, int n){
   int *Pbis = malloc(n * sizeof(int));
   for (int i = 0; i < n; ++i) {
      Pbis[i] = P[i];
   }
   return Pbis;
}

bool equal_tabs(int *P, int *Q, int n) {
    for (int i = 0; i < n; ++i) {
        if (P[i] != Q[i])
            return false;
    }
    return true;
}

void scramble_tab(int *P, int n) {
    int tmp;

    if (n <= 1)
        return;

    int k = random() % n;
    SWAP(P[n-1], P[k], tmp);
    scramble_tab(P, n - 1);
}

void random_perm(int *P, int n) {
    for (int k = 0; k < n; ++k) {
        P[k] = k;
    }

    scramble_tab(P, n);
}
