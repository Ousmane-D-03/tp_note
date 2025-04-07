#ifndef GRAPH_H
#define GRAPH_H

// Un point (x,y).
typedef struct {
    double x, y;
} point;

// Un couple de points.
typedef struct {
    point A;
    point B;
} couple;

// Un graphe G.
typedef struct {
    int   n;     // n = nombre de sommets
    int  *deg;   // deg[u] = nombre de voisins du sommet u
    int **list;  // list[u][i] = i-ème voisin de u, i=0..deg[u]-1
} graph;

// Une arête u-v avec un poids.
typedef struct {
    int    u, v;    // extrémités de l'arête u-v
    double weight;  // poids de l'arête u-v
} edge;

graph createGraph(int n);

// Libère un graphe G et ses listes.
void freeGraph(graph G);

// Ajoute l'arête u-v au graphe G de manière symétrique. Les degrés de
// u et v doivent être à jour et les listes suffisamment grandes.
void addEdge(graph G, int u, int v);

int compEdge(const void *e1, const void *e2);

#endif
