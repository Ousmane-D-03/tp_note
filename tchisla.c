/**
 * Trouve la plus petite expression utilisant le chiffre 'c' pour former 'n'
 * @param c Le chiffre autorisé (1-9)
 * @param n Le nombre cible à atteindre
 * @return Le nombre minimal de chiffres 'c' utilisés
 */
int tchisla2(int c, int n) {
    int T[2*n + 3];  // Stocke les symboles de l'expression (taille max théorique)
    
    // Boucle sur toutes les tailles d'expression possibles (1, 2, 3...)
    for (int k = 1; ; k++) {
        initialiser(T, k);  // Remplit T avec des 'c' et opérateurs initiaux
        
        // Génère toutes les combinaisons possibles pour une taille k
        do {
            // Évalue si l'expression courante vaut 'n'
            if (evaluate(T, k, c) == n) {
                return k;  // Solution trouvée !
            }
        } while (next_combination(T, k));  // Passe à la combinaison suivante
    }
}