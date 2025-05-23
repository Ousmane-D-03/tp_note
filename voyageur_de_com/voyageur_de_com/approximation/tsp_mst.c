#include "tools.h"
#include "tsp_mst.h"
#include "tsp_brute_force.h"
#include <stdlib.h>


//
//  TSP - MST
//
//  -> compléter uniquement tsp_mst() en fin de fichier
//  -> la structure "graph" est définie dans "tools.h"
//  -> la structure "edge" est définie dans "tsp_mst.h"
//

// Crée un graphe à n>0 sommets et sans arêtes. Les listes
// (potentielles de voisins) sont de tailles n, mais attention les
// degrés ne sont pas initialisés ! Il faudra le faire impérativement
// dans tsp_mst(). On code le fait que les degrés ne sont pas
// initialisés par G.deg[0]<0, ce qui permet de détecter la situation.
graph createGraph(int n) {
  graph G;
  G.n    = n;
  G.deg  = malloc(n * sizeof(*(G.deg)));
  G.list = malloc(n * sizeof(*(G.list)));
  for (int u = 0; u < n; u++)
    G.list[u] = malloc(n * sizeof(int)); // taille n par défaut
  G.deg[0] = -1; // par défaut, G ne sera pas dessiné par drawGraph()
  return G;
}

// Libère un graphe G et ses listes.
void freeGraph(graph G) {
  for (int u = 0; u < G.n; u++)
    free(G.list[u]);
  free(G.list);
  free(G.deg);
}

// Ajoute l'arête u-v au graphe G de manière symétrique. Les degrés de
// u et v doivent être à jour et les listes suffisamment grandes.
void addEdge(graph G, int u, int v) {
  G.list[u][G.deg[u]++] = v;
  G.list[v][G.deg[v]++] = u;
}

// Fonction de comparaison du poids de deux arêtes à utiliser avec
// qsort() pour un tri par ordre croissant. Ne pas hésiter à utiliser
// "man qsort" en ligne de commande pour l'aide sur cette fonction de
// la libraire standard du C.
int compEdge(const void *e1, const void *e2) {
  double const x = ((edge *)e1)->weight;
  double const y = ((edge *)e2)->weight;
  return (x > y) - (x < y); // -1,0,+1 suivant que x<y, x=y, ou x>y
}

// Fusionne les arbres de racines x et y selon l'heuristique du rang.
void Union(int x, int y, int *parent, int *rank) {
  if (rank[x] > rank[y])
    parent[y] = x;
  else {
    parent[x] = y;
    if (rank[x] == rank[y])
      rank[y]++;
  }
}

// Renvoie la racine de l'arbre contenant u (sa composante donc) selon
// l'heuristique de la compression de chemin.
int Find(int u, int *parent) {
  if (u != parent[u])
    parent[u] = Find(parent[u], parent);
  return parent[u];
}

// Calcule dans le tableau P l'ordre de première visite des sommets du
// graphe G selon un parcours en profondeur d'abord à partir du sommet
// u. Le paramètre p est le sommet parent de u. On doit avoir p<0 si u
// est l'origine du parcours (premier appel).
void dfs(graph G, int u, int *P, int p) {
  static int t; // t = temps ou indice (variable globale) du tableau P
  if (p < 0) {
    if (G.deg[0] < 0)
      return; // si G n'existe pas
    t = 0;
  }
  P[t++] = u;
  for (int i = 0; i < G.deg[u]; i++)
    if (G.list[u][i] != p)
      dfs(G, G.list[u][i], P, u);
}

double tsp_mst(point *V, int n, int *P, graph T) {
  // Cette fonction à compléter doit calculer trois choses (=les
  // sorties) à partir de V et n (=les entrées):
  //
  // 1. le graphe T, soit l'arbre couvrant V de poids minimum;
  // 2. la tournée P, soit l'ordre de visite selon le DFS de T;
  // 3. la valeur de la tournée P.
  //
  // NB: P et T doivent être créés et libérés par l'appelant. Il est
  // important de vider T, en remetant à zéro le degré de tous ses
  // sommets, avant de le remplir car tsp_mst() sera appelée plusieurs
  // fois.
  //
  // Algorithme:
  // 1. remplir puis trier le tableau d'arêtes avec qsort()
  // 2. répéter pour chaque arête u-v, mais pas plus de n-1 fois:
  //    si u-v ne forme pas un cycle de T (<=> u,v dans des composantes
  //    différentes) alors ajouter u-v au graphe T
  // 3. calculer dans P le DFS de T

  // E = tableau de toutes les arêtes définies à partir des n points de V
  int m = n * (n - 1) / 2; // nombre d'arêtes dans un graphe complet
  edge *E = malloc(m * sizeof(edge));
  
  // Remplissage du tableau d'arêtes
  int k = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      E[k].u = i;
      E[k].v = j;
      E[k].weight = distance(V[i], V[j]);
      k++;
    }
  }
  
  // Tri des arêtes par poids croissant
  qsort(E, m, sizeof(edge), compEdge);
  
  // Initialisation pour Union-Find
  int *parent = malloc(n * sizeof(int));
  int *rank = malloc(n * sizeof(int));
  for (int u = 0; u < n; u++) {
    parent[u] = u;
    rank[u] = 0;
    T.deg[u] = 0; // Réinitialisation des degrés de T
  }
  
  // Construction de l'arbre couvrant minimal
  int edges_added = 0;
  for (int i = 0; i < m && edges_added < n - 1; i++) {
    int u = E[i].u;
    int v = E[i].v;
    
    int root_u = Find(u, parent);
    int root_v = Find(v, parent);
    
    if (root_u != root_v) {
      addEdge(T, u, v);
      Union(root_u, root_v, parent, rank);
      edges_added++;
    }
  }
  
  // Libération de la mémoire
  free(parent);
  free(rank);
  free(E);
  
  if (T.deg[0] < 0)
    return 0;
  
  // Calcul de la tournée par parcours en profondeur
  dfs(T, 0, P, -1);
  return tourLength(V, n, P);
}


/*
Voici l'explication de l'algorithme implémenté :
Création du tableau d'arêtes :
On calcule le nombre total d'arêtes possibles dans un graphe complet à n sommets : m = n(n-1)/2
On alloue un tableau E de taille m pour stocker toutes les arêtes possibles
On remplit ce tableau avec toutes les arêtes possibles et leurs poids (distances entre points)
Tri des arêtes :
On utilise qsort avec la fonction compEdge pour trier les arêtes par poids croissant
Initialisation de l'Union-Find :
On crée les tableaux parent et rank pour la structure Union-Find
On initialise chaque sommet comme sa propre racine
On réinitialise les degrés de l'arbre T
Construction de l'arbre couvrant minimal :
On parcourt les arêtes triées par poids croissant
Pour chaque arête, on vérifie si ses extrémités sont dans des composantes différentes
Si oui, on ajoute l'arête à T et on fusionne les composantes
On s'arrête quand on a ajouté n-1 arêtes (un arbre)
Calcul de la tournée :
On effectue un parcours en profondeur (DFS) de l'arbre T
Le parcours donne l'ordre de visite des points dans P
On calcule et retourne la longueur totale de la tournée
Cet algorithme garantit une tournée dont la longueur est au plus 2 fois la longueur optimale, 
ce qui en fait une 2-approximation du problème du voyageur de commerce.
*/