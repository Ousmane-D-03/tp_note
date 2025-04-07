#include "matching.h"

#include "graph.h"
#include "tools.h"

//
//  -> les structures "point", "couple", "graph", et "edge" sont
//     définies dans "graph.h"
//
//  -> les fonctions createGraph(), freeGraph(), compEdge(),
//     et addEdge() sont codées dans "graph.c"
//
//  -> Les trois premières fonctions, dist(), weight() et
//     matching_check() vous sont données. Vous devez coder toutes les
//     suivantes, a priori dans l'ordre.

// Fonction qui renvoie la distance euclidienne entre deux points.
//
double dist(point A, point B) {
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(x * x + y * y);
}

// Renvoie le poids du graphe défini par G sur les points de V. Si u-v
// est une arête de G, alors son poids est dist(V[u],V[v]). On
// supposera que V et G sont de même taille, c'est-à-dire que G.n = |V|.
// On supposera aussi que G est symétrique, c'est-à-dire si v est
// un voisin de u, alors u est aussi un voisin de v.
//
double weight(point *V, graph G) {
    if (G.deg[0] < 0)
        return 0.0;                // graphe non initialisé
    double w = 0.0;                // le poids recherché
    for (int u = 0; u < G.n; u++)  // pour tous les sommets u
        for (int i = 0; i < G.deg[u]; i++) {
            int v = G.list[u][i];  // v = i-ème voisin de u
            if (u < v)
                w += dist(V[u], V[v]);  // seulement u-v, pas v-u
        }
    return w;
}

// Teste si un graphe G est un couplage (utile pour tester vos
// fonctions), et renvoie true si c'est le cas, false sinon. L'idée
// est de vérifier que tous les ont exactement un voisin (grâce à
// G.deg[u]), sauf si le nombre de sommets est impair où dans ce cas
// un seul sommet n'a aucun voisin (sommet isolé). On vérifie aussi
// que les listes d'adjacence soient symétriques et sans boucles, à
// savoir que si v est voisin de u alors u doit être voisin de v et de
// plus u ≠ v.
//
bool matching_check(graph G) {
    int isolated = -1, u, v;  // le sommet isolé (par défaut aucun)

    for (u = 0; u < G.n; u++) {  // si n=0 => true

        if (G.deg[u] == 0) {  // cas d'un sommet isolé
            if (G.n % 2 == 0)
                return false;  // pair et sommet isolé
            if (isolated >= 0)
                return false;  // impair et déjà un sommet isolé
            isolated = u;      // on a trouvé le sommet isolé
            continue;          // important !
        }

        if (G.deg[u] > 1)
            return false;  // plus d'un voisin
        v = G.list[u][0];  // v = voisin unique de u
        if (u == v)
            return false;  // c'est une boucle
        if (G.list[v][0] != u)
            return false;  // pas symétrique
    }

    return true;
}

// Routine qui met à zéro la longueur de chaque liste d'adjacence du
// graphe G. Les listes elles-mêmes ne doivent pas être modifiées (ni libérées).
//
// Cette fonction doit être appelée au début de matching_basic(),
// matching_greedy() et matching_rectangle() pour permettre une
// exécution dynamique lors du déplacement des points à la souris.
//
void resetGraph(graph G) {
    ;
    ;
    ;
}

// Calcule un couplage arbitrairement. La fonction doit construire un
// couplage dans le graphe G et renvoyer le poids de ce couplage. On
// supposera que V et G sont de même taille, c'est-à-dire que G.n =
// |V|. Le couplage doit être construit en temps O(n) à l'aide d'un
// simple parcours sur les points de V.
//
double matching_basic(point *V, graph G) {
    ;
    ;
    ;
    return 0.0;
}

// Couplage calculé par l'algorithme glouton. La fonction doit
// construire le couplage dans le graphe G et renvoyer le poids de ce
// couplage. On supposera que V et G sont de même taille, c'est-à-dire
// que G.n = |V|.
//
double matching_greedy(point *V, graph G) {
    ;
    ;
    ;
    return 0.0;
}

//////////////////////////////////////////////////////////////////////
// On représente un sous-ensemble de k points de V par un simple
// tableau d'indices de points de V. Bien sûr, il faut k <= n = |V|.
// Par exemple, si V possède n=6 points, V[0], V[1], ..., V[5],
// alors le tableau T = { 4, 0, 1 } représentera le sous-ensemble des
// k = 3 points suivants : { V[4], V[0], V[1] }. Notez que les indices
// de T ne sont pas forcément dans l'ordre croissant.
//////////////////////////////////////////////////////////////////////

// Renvoie un couple de points (A,B) de sorte que le sous-ensemble T
// de k>0 points de V soient inclus dans le rectangle défini par les
// points diagonaux A et B. Il faut que A soit le point de plus faible
// abscisse et ordonnée et que B soit le point de plus grande abscisse
// et ordonnée du rectangle. NB : Par rapport au système de coordonnées
// de la fenêtre graphique, A est le point en haut à gauche du
// rectangle et B le point en bas à droite.
//
couple boundingBox(int *T, int k, point *V) {
    // Cette initialisation n'est là que pour éviter un avertissement
    // du compilateur. Elle est donc incorrecte, vous devrez la changer.
    // On rappelle que la plus grande valeur double est DBL_MAX
    // et la plus petite est -DBL_MAX.
    couple R = {{0, 0}, {0, 0}};
    ;
    ;
    ;
    return R;
}

// Fonction récursive qui calcule un couplage pour le sous-ensemble T
// de k>0 points de V et l'ajoute au couplage courant G. Si k est
// pair, la fonction doit renvoyer -1. Sinon, elle doit renvoyer
// l'indice du point de V non couvert par le couplage qui vient d'être
// calculé.
//
int matching_rec(int *T, int k, point *V, graph G) {
    ;
    ;
    ;
    return -1;
}

// Couplage calculé par l'heuristique des rectangles. La fonction doit
// construire le couplage dans le graphe G et renvoyer le poids de ce
// couplage. On supposera que V et G sont de même taille, c'est-à-dire
// que G.n = |V|.
//
double matching_rectangle(point *V, graph G) {
    ;
    ;
    ;
    return 0.0;
}

// Cherche la première paire d'arêtes du couplage G telle que leurs
// flips produisent une diminution du poids du couplage. Si cette
// paire existe, le meilleur des deux flips possibles est effectué et
// on renvoie true. Sinon, on renvoie false. Pour être la première
// paire u1-v1, u2-v2 (en supposant u1 < v1 et u2 < v2), il faut tout
// simplement que u1 et u2 soient les plus petits indices possibles.
// Par exemple, si 4-9 et 6-8 est le premier flip possible, alors cela
// veut dire qu'il ne peut avoir d'autres flips possibles du type u-v
// (en supposant u<v) ni avec u<4 et ni avec v<6.
//
bool matching_flip(point *V, graph G) {
    ;
    ;
    ;
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////::
// Exercice 1: Ré-initialisation d'un graphe
void resetGraph(graph G) {
    for (int u = 0; u < G.n; u++) {
        G.deg[u] = 0;
    }
}

// Exercice 2: Couplage de base
double matching_basic(point *V, graph G) {
    resetGraph(G);
    for (int u = 0; u < G.n; u += 2) {
        if (u + 1 < G.n) {
            addEdge(G, u, u + 1);
        }
    }
    return weight(V, G);
}

// Exercice 3: Algorithme glouton
double matching_greedy(point *V, graph G) {
    resetGraph(G);
    int n = G.n;
    int edge_count = n * (n - 1) / 2;
    edge *edges = malloc(edge_count * sizeof(edge));
    int idx = 0;
    
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            edges[idx].u = u;
            edges[idx].v = v;
            edges[idx].weight = dist(V[u], V[v]);
            idx++;
        }
    }
    
    qsort(edges, edge_count, sizeof(edge), compEdge);
    bool *used = calloc(n, sizeof(bool));
    
    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (!used[u] && !used[v]) {
            addEdge(G, u, v);
            used[u] = used[v] = true;
        }
    }
    
    free(edges);
    free(used);
    return weight(V, G);
}

// Exercice 4: Calcul du rectangle englobant
couple boundingBox(int *T, int k, point *V) {
    double min_x = DBL_MAX, min_y = DBL_MAX;
    double max_x = -DBL_MAX, max_y = -DBL_MAX;
    
    for (int i = 0; i < k; i++) {
        point p = V[T[i]];
        if (p.x < min_x) min_x = p.x;
        if (p.y < min_y) min_y = p.y;
        if (p.x > max_x) max_x = p.x;
        if (p.y > max_y) max_y = p.y;
    }
    
    return (couple){{min_x, min_y}, {max_x, max_y}};
}

// Exercice 5: Fonction récursive
int matching_rec(int *T, int k, point *V, graph G) {
    if (k % 2 == 0) {
        return -1;
    }
    if (k == 1) {
        return T[0];
    }
    
    couple bb = boundingBox(T, k, V);
    double width = bb.B.x - bb.A.x;
    double height = bb.B.y - bb.A.y;
    double split = (width > height) ? (bb.A.x + bb.B.x) / 2 : (bb.A.y + bb.B.y) / 2;
    
    int *left = malloc(k * sizeof(int));
    int *right = malloc(k * sizeof(int));
    int l_cnt = 0, r_cnt = 0;
    
    for (int i = 0; i < k; i++) {
        point p = V[T[i]];
        if ((width > height && p.x <= split) || (width <= height && p.y <= split)) {
            left[l_cnt++] = T[i];
        } else {
            right[r_cnt++] = T[i];
        }
    }
    
    // Éviter les partitions vides
    if (l_cnt == 0 && r_cnt > 0) {
        left[l_cnt++] = right[--r_cnt];
    }
    if (r_cnt == 0 && l_cnt > 0) {
        right[r_cnt++] = left[--l_cnt];
    }
    
    int l_iso = matching_rec(left, l_cnt, V, G);
    int r_iso = matching_rec(right, r_cnt, V, G);
    
    free(left);
    free(right);
    
    if (l_iso != -1 && r_iso != -1) {
        addEdge(G, l_iso, r_iso);
        return -1;
    }
    return (l_iso != -1) ? l_iso : r_iso;
}

// Exercice 6: Algorithme récursif
double matching_rectangle(point *V, graph G) {
    resetGraph(G);
    int n = G.n;
    int *T = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) T[i] = i;
    matching_rec(T, n, V, G);
    free(T);
    return weight(V, G);
}

// Exercice 7: Flip des arêtes
bool matching_flip(point *V, graph G) {
    int n = G.n;
    edge *edges = malloc(n * sizeof(edge));
    int cnt = 0;
    bool *visited = calloc(n, sizeof(bool));
    
    for (int u = 0; u < n; u++) {
        if (!visited[u] && G.deg[u] > 0) {
            int v = G.list[u][0];
            edges[cnt++] = (edge){u, v, dist(V[u], V[v])};
            visited[u] = visited[v] = true;
        }
    }
    free(visited);
    
    for (int i = 0; i < cnt; i++) {
        for (int j = i+1; j < cnt; j++) {
            edge e1 = edges[i], e2 = edges[j];
            double original = e1.weight + e2.weight;
            
            double opt1 = dist(V[e1.u], V[e2.u]) + dist(V[e1.v], V[e2.v]);
            double opt2 = dist(V[e1.u], V[e2.v]) + dist(V[e1.v], V[e2.u]);
            
            if (opt1 < original || opt2 < original) {
                // Supprimer anciennes arêtes
                G.deg[e1.u] = G.deg[e1.v] = 0;
                G.deg[e2.u] = G.deg[e2.v] = 0;
                
                // Ajouter nouvelles arêtes
                if (opt1 <= opt2) {
                    addEdge(G, e1.u, e2.u);
                    addEdge(G, e1.v, e2.v);
                } else {
                    addEdge(G, e1.u, e2.v);
                    addEdge(G, e1.v, e2.u);
                }
                free(edges);
                return true;
            }
        }
    }
    
    free(edges);
    return false;
}