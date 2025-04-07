#include "tools.h"
#include "tsp_brute_force.h"
#include "tsp_prog_dyn.h"

//
//  TSP - PROGRAMMATION DYNAMIQUE
//
//  -> compléter uniquement tsp_prog_dyn()
//  -> la structure "cell" est définie dans "tsp_prog_dyn.h"
//

// Renvoie l'ensemble S\{i}.
int DeleteSet(int S, int i) { return S & ~(1 << i); }

int ExtractPath(cell **D, int t, int S, int n, int *Q) {
  /*
    Construit dans Q le chemin entre les points V[n-1] et V[t] passant
    par tous les points de S, c'est-à-dire le chemin extrait depuis la
    case D[t][S]. La longueur du chemin Q ainsi extrait vaut en
    principe D[t][S].length. Renvoie le nombre de points du chemin
    Q. On supposera Q[] assez grand pour recevoir tous ses points.
  */
  if(D[0][1].length < 0) return 0; // si D n'a pas été remplie

  // phase 1: extrait Q = V[t] ... V[n-1] dans cet ordre

  Q[0] = t;                   // écrit le dernier point V[t] en premier
  int k = 1;                  // k = taille de Q = nombre de points écrits dans Q
  while (Q[k - 1] != n - 1) { // on s'arrête lorsque le point V[n-1] est atteint
    Q[k] = D[Q[k - 1]][S].pred;
    S = DeleteSet(S, Q[k - 1]);
    k++;
  }

  // phase 2: renverse Q pour avoir Q = V[n-1] ... V[t], au cas où la
  // fonction dist() ne soit pas symétrique

  int p=0, q=k-1;
  while(p<q){
    SWAP(Q[p], Q[q], t);
    p++; q--;
  }

  return k;
}

double tsp_prog_dyn(point *V, int n, int *Q) {
  /*
    Version programmation dynamique du TSP. La tournée optimale
    calculée doit être écrite dans la permutation Q, tableau qui doit
    être alloué par l'appelant. La fonction doit renvoyer aussi la
    valeur de la tournée Q ou 0 s'il y a eut un problème, comme la
    pression de 'q' pour sortir de l'affichage.
    
    La table D est un tableau 2D de "cell" indexé par t ("int"),
    l'indice d'un point V[t], et S ("int") représentant un ensemble
    d'indices de points.

    o D[t][S].length = longueur minimum d'un chemin allant de V[n-1] à
      V[t] qui visite tous les points d'indice dans S

    o D[t][S].pred = l'indice du point précédant V[t] dans le chemin
      ci-dessus de longueur D[t][S].length

    NB1: Ne pas lancer tsp_prog_dyn() avec n>31 car:
         o les entiers (int sur 32 bits) ne seront pas assez grands
           pour représenter tous les sous-ensembles;
         o pour n=32, il faudra environ n*2^n / 10^9 = 137 secondes
           sur un ordinateur à 1 GHz, ce qui est un peu long; et
         o l'espace mémoire, le malloc() pour la table D, risque
           d'être problématique: 32 * 2^32 * sizeof(cell) représente
           déjà 1536 Go de mémoire.

         En pratique on peut monter facilement jusqu'à n=24 pour une
         dizaine de secondes de calcul.
 
    NB2: La variable globale "running" indique si l'affichage
         graphique est actif, la pression de 'q' la faisant passer à
         faux. L'usage de "running" permet à l'utilisateur de sortir
         des boucles de calcul lorsqu'elles sont trop longues. Donc
         dans la phase de test, pensez à ajouter "&& running" dans vos
         conditions de boucle pour quitter en court de route si c'est
         trop long.
  */

  //-------------------------------------------------------------
  // Phase 1: Déclaration de la table.
  //
  // Elle comporte (n-1)*2^(n-1) "cell". NB: la colonne S=0
  // (l'ensemble vide) n'est pas utilisée.

  int const L = n-1;    // L = nombre de lignes = indice du dernier point
  int const C = 1 << L; // C = nombre de colonnes

  cell **D = malloc(L*sizeof(cell*)); // L=n-1 lignes
  for (int t=0; t<L; t++) D[t] = malloc(C*sizeof(cell)); // C=2^{n-1} colonnes
  D[0][1].length=-1; // pour savoir si la table a été remplie


  //-------------------------------------------------------------
  // Phase 2: Remplissage de la table (par colonne)
  for (int S = 1; S < C; S++) {
    for (int t = 0; t < L; t++) {
      if (!(S & (1 << t))) continue; // t doit être dans S
      
      if (S == (1 << t)) {
        // Cas de base : S ne contient que t
        D[t][S].length = dist(V[n-1], V[t]);
        D[t][S].pred = n-1;
      } else {
        // Cas général : S contient plusieurs points
        double min_length = INFINITY;
        int best_pred = -1;
        
        for (int x = 0; x < L; x++) {
          if (x == t || !(S & (1 << x))) continue; // x doit être dans S\{t}
          
          int T = DeleteSet(S, t);
          double current_length = D[x][T].length + dist(V[x], V[t]);
          
          if (current_length < min_length) {
            min_length = current_length;
            best_pred = x;
          }
        }
        
        D[t][S].length = min_length;
        D[t][S].pred = best_pred;
      }
      
      // Affichage du chemin
      int k = ExtractPath(D, t, S, n, Q);
      drawPath(V, n, Q, k);
      if (!running) return 0;
    }
  }

  //-------------------------------------------------------------
  // Phase 3: Extraction de la tournée optimale
  double w = 0;
  
  if (running) {
    // Calcul de la longueur minimale
    double min_length = INFINITY;
    int best_t = -1;
    int final_S = (1 << L) - 1; // S contient tous les points sauf V[n-1]
    
    for (int t = 0; t < L; t++) {
      double current_length = D[t][final_S].length + dist(V[t], V[n-1]);
      if (current_length < min_length) {
        min_length = current_length;
        best_t = t;
      }
    }
    
    w = min_length;
    
    // Extraction du chemin optimal
    int k = ExtractPath(D, best_t, final_S, n, Q);
    Q[k] = n-1; // Ajout du point final
  }

  //-------------------------------------------------------------
  // Phase 4: Libération de la mémoire
  for (int t = 0; t < L; t++) {
    free(D[t]);
  }
  free(D);

  return w;
}
