#define INF 1e9

/**
 * Trouve le plus court chemin depuis un nœud source
 * @param graph Matrice d'adjacence du graphe
 * @param src Nœud de départ
 * @param n Nombre total de nœuds
 */
void dijkstra(int graph[MAX][MAX], int src, int n) {
    int dist[MAX];      // Distances minimales connues
    int visited[MAX];   // Marqueurs de visite
    
    // Initialisation
    for (int i = 0; i < n; i++) {
        dist[i] = INF;      // Aucun chemin connu initialement
        visited[i] = 0;     // Aucun nœud visité
    }
    dist[src] = 0;          // Distance à soi-même = 0
    
    // Boucle principale : traite tous les nœuds
    for (int i = 0; i < n - 1; i++) {
        // Trouve le nœud non visité le plus proche
        int u = -1, min_dist = INF;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                u = v;
                min_dist = dist[v];
            }
        }
        if (u == -1) break;  // Aucun chemin possible
        
        visited[u] = 1;  // Marque le nœud comme visité
        
        // Met à jour les distances des voisins
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0) {  // Si voisin existant
                int new_dist = dist[u] + graph[u][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;  // Trouvé un chemin plus court !
                }
            }
        }
    }
}

#include <stdio.h>
#define INF 9999
#define V 5 // Nombre de nœuds

// Trouve le nœud avec la distance minimale
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra pour le plus court chemin depuis src
void dijkstra(int graph[V][V], int src) {
    int dist[V], visited[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Affiche les distances
    printf("Depuis le nœud %d:\n", src);
    for (int i = 0; i < V; i++) {
        printf("Vers %d: %d\n", i, dist[i]);
    }
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0},
        {4, 0, 8, 0, 0},
        {0, 8, 0, 7, 0},
        {0, 0, 7, 0, 9},
        {0, 0, 0, 9, 0}
    };
    dijkstra(graph, 0);
    return 0;
}