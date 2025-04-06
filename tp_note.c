#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "htable.h"

// Structure représentant un point 2D
typedef struct {
    double x;   // Coordonnée horizontale
    double y;   // Coordonnée verticale
} Point;

// Structure représentant une paire d'indices de points
typedef struct {
    int a;      // Indice du premier point
    int b;      // Indice du deuxième point
} Pair;

/* Calcule la distance euclidienne entre deux points
 * Paramètres :
 *   p1 - Premier point
 *   p2 - Deuxième point
 * Retourne :
 *   La distance entre p1 et p2
 */
double distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy); // Théorème de Pythagore
}

/* Convertit une paire de coordonnées de grille (i,j) en un identifiant unique
 * selon le schéma diagonal vu en TD
 * Paramètres :
 *   i - Coordonnée horizontale de la cellule
 *   j - Coordonnée verticale de la cellule
 * Retourne :
 *   Un entier unique représentant la cellule
 */
int map(int i, int j) {
    int somme_diagonales = (i + j) * (i + j + 1) / 2; // Formule de la somme arithmétique
    return somme_diagonales + j; // Ajout de la position verticale
}

/* Algorithme principal de recherche de la paire de points la plus proche
 * Paramètres :
 *   points - Tableau de points
 *   n - Nombre de points
 * Retourne :
 *   Une structure Pair contenant les indices des deux points les plus proches
 */
Pair pppp_random(Point* points, int n) {
    if (n < 2) exit(EXIT_FAILURE); // Validation d'entrée
    
    Pair meilleure_paire = {0, 1}; // Initialisation avec les deux premiers points
    double d_min = distance(points[0], points[1]); // Distance initiale
    int redemarrage = 1; // Contrôle de la boucle de réinitialisation
    
    while (redemarrage) {
        redemarrage = 0;
        double delta = d_min / sqrt(2); // Taille de cellule basée sur la distance actuelle
        HashTable* ht = ht_create(); // Création de la table de hachage
        
        // Parcours de tous les points dans l'ordre
        for (int t = 0; t < n; t++) {
            Point pt = points[t];
            // Calcul de la cellule courante
            int i = (int)(pt.x / delta);
            int j = (int)(pt.y / delta);
            
            // Vérification des 25 cellules voisines (grille 5x5)
            for (int di = -2; di <= 2; di++) {       // Décalage horizontal
                for (int dj = -2; dj <= 2; dj++) {   // Décalage vertical
                    int ni = i + di; // Nouvelle coordonnée i
                    int nj = j + dj; // Nouvelle coordonnée j
                    int cle = map(ni, nj); // Conversion en clé unique
                    
                    // Récupération du point dans la cellule voisine
                    Point* q = (Point*)ht_read(ht, cle);
                    if (q != NULL && q != &pt) { // Évite la comparaison avec soi-même
                        double dist = distance(pt, *q);
                        if (dist < d_min) { // Nouvelle meilleure paire trouvée
                            d_min = dist;
                            meilleure_paire.a = t; // Index du point courant
                            meilleure_paire.b = (int)(q - points); // Index via arithmétique des pointeurs
                            ht_free(ht); // Libération mémoire avant redémarrage
                            redemarrage = 1; // Force le redémarrage de l'algorithme
                            goto redemarrage_boucle; // Sorte de la double boucle
                        }
                    }
                }
            }
            
            // Ajout du point à la table de hachage
            int cle = map(i, j);
            ht_write(ht, cle, &points[t]);
        }
        
        redemarrage_boucle:
        ht_free(ht); // Nettoyage mémoire important
    }
    
    return meilleure_paire;
}

/* Exemple d'utilisation (à adapter selon le main fourni dans l'archive)
 * Note : Ce main est simplifié pour la démonstration
 */
int main() {
    // Création d'un jeu de points de test
    Point points[] = {{0,0}, {1,1}, {3,4}, {5,5}};
    int n = sizeof(points) / sizeof(points[0]);
    
    // Appel de l'algorithme
    Pair resultat = pppp_random(points, n);
    
    // Affichage du résultat
    printf("Paire la plus proche: (%d, %d)\n", resultat.a, resultat.b);
    printf("Points: (%.1f,%.1f) et (%.1f,%.1f)\n",
           points[resultat.a].x, points[resultat.a].y,
           points[resultat.b].x, points[resultat.b].y);
    
    return 0;
}