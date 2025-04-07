#include "tools.h"
#include "tsp_brute_force.h"
#include <stdlib.h>


//
//  TSP - HEURISTIQUES
//

void reverse(int *T, int p, int q) {
  // Renverse la partie T[p]...T[q] du tableau T avec p<q si
  // T={0,1,2,3,4,5,6} et p=2 et q=5, alors le nouveau tableau T sera
  // {0,1, 5,4,3,2, 6}.
  while (p < q) {
    int temp = T[p];
    T[p] = T[q];
    T[q] = temp;
    p++;
    q--;
  }
  return;
}

double first_flip(point *V, int n, int *P) {
  // Renvoie le gain>0 du premier flip réalisable, tout en réalisant
  // le flip, et 0 s'il n'y en a pas.
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 2; j < n; j++) {
      // Calcul du gain potentiel
      double gain = distance(V[P[i]], V[P[i+1]]) + distance(V[P[j]], V[P[(j+1)%n]])
                  - distance(V[P[i]], V[P[j]]) - distance(V[P[i+1]], V[P[(j+1)%n]]);
      
      if (gain > 0) {
        // Effectuer le flip en inversant la partie du tableau entre i+1 et j
        reverse(P, i+1, j);
        return gain;
      }
    }
  }
  return 0.0;
}

double tsp_flip(point *V, int n, int *P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i. Pensez aussi faire
  // drawTour() pour visualiser chaque flip.
  
  // Initialisation de la tournée
  for (int i = 0; i < n; i++) {
    P[i] = i;
  }
  
  double gain;
  do {
    gain = first_flip(V, n, P);
    if (gain > 0) {
      drawTour(V, n, P);
    }
  } while (gain > 0);
  
  return tourLength(V, n, P);
}

/*

Voici l'explication des fonctions que j'ai implémentées :
reverse(int *T, int p, int q) : Cette fonction inverse une partie d'un tableau entre les indices p et q. 
Elle est utilisée pour effectuer le flip en inversant la partie de la tournée entre les deux arêtes 
sélectionnées.
first_flip(point *V, int n, int *P) : Cette fonction recherche le premier flip réalisable qui 
améliore la longueur de la tournée. Elle :
Parcourt toutes les paires d'arêtes non consécutives
Calcule le gain potentiel du flip
Effectue le premier flip qui donne un gain positif
Retourne le gain ou 0 si aucun flip améliorant n'est trouvé
tsp_flip(point *V, int n, int *P) : Cette fonction implémente l'algorithme complet :
Initialise la tournée avec l'ordre naturel des points
Répète l'application de flips tant qu'il y a des améliorations possibles
Affiche la tournée après chaque amélioration
Retourne la longueur finale de la tournée
L'algorithme s'arrête lorsqu'aucun flip ne peut plus améliorer la longueur de la tournée, 
ce qui signifie qu'on a atteint un optimum local.

*/

double tsp_greedy(point *V, int n, int *P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i.
  
  // Tableau pour marquer les points déjà visités
  int *visited = (int *)calloc(n, sizeof(int));
  
  // On commence par le premier point
  P[0] = 0;
  visited[0] = 1;
  
  // Construction de la tournée point par point
  for (int i = 1; i < n; i++) {
    int last = P[i-1];
    int next = -1;
    double min_dist = -1;
    
    // Recherche du point non visité le plus proche
    for (int j = 0; j < n; j++) {
      if (!visited[j]) {
        double dist = distance(V[last], V[j]);
        if (next == -1 || dist < min_dist) {
          next = j;
          min_dist = dist;
        }
      }
    }
    
    // Ajout du point le plus proche à la tournée
    P[i] = next;
    visited[next] = 1;
  }
  
  free(visited);
  return tourLength(V, n, P);
}
/* 
Voici l'explication de l'algorithme glouton implémenté :
On commence par initialiser un tableau visited pour marquer les points déjà inclus dans la tournée.
On commence la tournée par le premier point (indice 0) et on le marque comme visité.
Pour chaque position suivante dans la tournée :
On prend le dernier point ajouté (last)
On cherche parmi tous les points non visités celui qui est le plus proche de last
On ajoute ce point le plus proche à la tournée et on le marque comme visité
À la fin, on libère la mémoire allouée pour le tableau visited et on retourne la longueur totale de la tournée.
Cet algorithme est simple et rapide, mais il ne garantit pas d'obtenir la tournée optimale. 
Il peut être utilisé comme point de départ pour d'autres heuristiques comme l'algorithme de flip 
que nous avons implémenté précédemment.
*/