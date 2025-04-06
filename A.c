typedef struct {
    int node;     // Nœud actuel
    int g_cost;   // Coût réel depuis le départ
    int f_cost;   // Coût total (g + heuristique)
} AStarNode;

/**
 * Trouve un chemin avec l'heuristique fournie
 * @param graph Matrice d'adjacence
 * @param start Nœud de départ
 * @param end Nœud d'arrivée
 * @param heuristic Tableau d'heuristiques (ex: distance de Manhattan)
 * @param n Nombre de nœuds
 * @return Coût du chemin optimal, -1 si impossible
 */
int a_star(int graph[MAX][MAX], int start, int end, int heuristic[MAX], int n) {
    PriorityQueue *pq = create_priority_queue();  // File de priorité
    enqueue(pq, (AStarNode){start, 0, heuristic[start]});
    
    int g_scores[MAX];  // Meilleur coût connu pour chaque nœud
    for (int i = 0; i < n; i++) g_scores[i] = INF;
    g_scores[start] = 0;
    
    while (!is_empty(pq)) {
        AStarNode current = dequeue(pq);
        
        // Si on atteint la cible, retourne le coût
        if (current.node == end) return current.g_cost;
        
        // Explore tous les voisins
        for (int v = 0; v < n; v++) {
            if (graph[current.node][v] != 0) {  // Si voisin existant
                int tentative_g = current.g_cost + graph[current.node][v];
                
                // Si meilleur chemin trouvé
                if (tentative_g < g_scores[v]) {
                    g_scores[v] = tentative_g;
                    int f = tentative_g + heuristic[v];  // f = g + h
                    enqueue(pq, (AStarNode){v, tentative_g, f});
                }
            }
        }
    }
    return -1;  // Aucun chemin trouvé
}