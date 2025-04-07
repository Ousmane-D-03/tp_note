//
// TAP - TP NOTE 2021
// HEURISTIQUE CHEAPEST INSERTION
//

#include "tp.h"

// Constantes à utiliser dans la fonction tsp_cheapest pour l'animation
#define ANIMATION 1        // Animation on/off pour algo cheapest.
#define ANIMATION_DELAY 2  // Pause, en secondes

////////////////////////
// FONCTIONS FOURNIES //
////////////////////////

// Distance Euclidienne
double dist(point A, point B);

// Valeur d'une tournée P de taille n.
double value(point *V, int n, int *P);

// Affichage d'un tableau d'entiers P de n cases.
void print_tab(int *P, int n);

//////////////////////////////////////////
// FONCTIONS A COMPLETER A PARTIR D'ICI //
//////////////////////////////////////////

// Exercice 1
void nearest_points(point *V, int n, int *first_ptr, int *second_ptr) {
    if (n < 2) return;

    double min_dist = INFINITY;
    int first = 0, second = 1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = dist(V[i], V[j]);
            if (d < min_dist || (d == min_dist && (i < first || (i == first && j < second)))) {
                if (d < min_dist) {
                    min_dist = d;
                    first = i;
                    second = j;
                } else {
                    if (i < first || (i == first && j < second)) {
                        first = i;
                        second = j;
                    }
                }
            }
        }
    }

    *first_ptr = first;
    *second_ptr = second;
}
// Exercice 2
void init_tour(point *V, int n, int *P) {
    for (int i = 0; i < n; i++) {
        P[i] = i;
    }
    int first, second;
    nearest_points(V, n, &first, &second);
    int tmp;
    SWAP(P[0], P[first], tmp);
    SWAP(P[1], P[second], tmp);
}

// Exercice 5
double score(point *V, int m, int *P, int i, int *pred_ptr) {
    double min_delta = INFINITY;
    int best_k = 0;

    for (int k = 0; k < m; k++) {
        int next_k = (k + 1) % m;
        double current = dist(V[P[k]], V[P[next_k]]);
        double new1 = dist(V[P[k]], V[P[i]]);
        double new2 = dist(V[P[i]], V[P[next_k]]);
        double delta = new1 + new2 - current;

        if (delta < min_delta || (delta == min_delta && k < best_k)) {
            min_delta = delta;
            best_k = k;
        }
    }

    *pred_ptr = best_k;
    return min_delta;
}

// Exercice 6
int new_point(point *V, int n, int m, int *P, int *pred_ptr) {
    double min_score = INFINITY;
    int best_i = m;
    int best_pred = 0;

    for (int i = m; i < n; i++) {
        int pred;
        double s = score(V, m, P, i, &pred);

        if (s < min_score || (s == min_score && i < best_i)) {
            min_score = s;
            best_i = i;
            best_pred = pred;
        }
    }

    *pred_ptr = best_pred;
    return best_i;
}

// Exercice 7
void rotate_right(int *P, int p, int q) {
    if (p >= q) return;
    int tmp = P[q];
    for (int i = q; i > p; i--) {
        P[i] = P[i - 1];
    }
    P[p] = tmp;
}
// Exercice 8
double tsp_cheapest(point *V, int n, int *P) {
    init_tour(V, n, P);
    int m = 2;

    while (m < n) {
        int pred;
        int new = new_point(V, n, m, P, &pred);
        rotate_right(P, pred + 1, new);
        m++;
        #if ANIMATION
            drawPartialTour(V, n, P, m);
            sleep(ANIMATION_DELAY);
        #endif
    }

    return value(V, n, P);
}

// Exercice 10
double gain(point *V, int n, int *P, int i, int j) {
    int j1 = j + 1;
    int j2 = (j1 + 1) % n;

    double original = dist(V[P[i]], V[P[(i+1) % n]]);
    original += dist(V[P[j]], V[P[j1]]);
    original += dist(V[P[j1]], V[P[j2]]);

    double new = dist(V[P[i]], V[P[j1]]);
    new += dist(V[P[j1]], V[P[(i+1) % n]]);
    new += dist(V[P[j]], V[P[j2]]);

    return original - new;
}

// Exercice 11
double first_flip25(point *V, int n, int *P) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j <= n-2; j++) {
            double g = gain(V, n, P, i, j);
            if (g > 0) {
                rotate_right(P, i + 1, j + 1);
                return g;
            }
        }
    }
    return 0.0;
}

// Exercice 12
double tsp_flip25(point *V, int n, int *P) {
    for (int i = 0; i < n; i++) {
        P[i] = i;
    }

    while (first_flip25(V, n, P) > 0);

    return value(V, n, P);
}