#include "tools.h"
#include "graph.h"

//
//  -> les structures "graph", "edge" sont définies dans "graph.h"
//

// Crée un graphe à n>0 sommets et sans arêtes. Les listes
// (potentielles de voisins) sont de tailles n, mais attention les
// degrés ne sont pas initialisés ! Il faudra le faire impérativement
// dans tsp_mst(). On code le fait que les degrés ne sont pas
// initialisés par G.deg[0]<0, ce qui permet de détecter la situation.
graph createGraph(int n) {
  graph G;
  G.n = n;
  G.deg = malloc(n * sizeof(*(G.deg)));
  G.list = malloc(n * sizeof(*(G.list)));
  for (int u = 0; u<n; u++)
    G.list[u] = malloc(n*sizeof(int)); // taille n par défaut
  G.deg[0]=-1; // par défaut, G ne sera pas dessiné par drawGraph()
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
// la libraire standard du C. Si les poids sont égaux, on compare les
// champs "->u", et si encore égaux on compare les "->v".
int compEdge(const void *e1, const void *e2) {
  double const x = ((edge*)e1)->weight;
  double const y = ((edge*)e2)->weight;
  if( x == y ){
    int u1 = ((edge*)e1)->u;
    int u2 = ((edge*)e2)->u;
    if( u1 == u2 ){
      u1 = ((edge*)e1)->v;
      u2 = ((edge*)e2)->v;
    }
    return u1 - u2;
  }
  return (x > y) - (x < y); // -1,0,+1 suivant que x<y, x=y, ou x>y;
}

