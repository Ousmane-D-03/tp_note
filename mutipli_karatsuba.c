/**
 * Multiplie deux nombres avec l'algorithme de Karatsuba
 * @param x Premier nombre
 * @param y Deuxième nombre
 * @return Résultat de x * y
 */
int karatsuba(int x, int y) {
    // Cas de base : multiplication directe pour petits nombres
    if (x < 10 || y < 10) return x * y;
    
    // Calcule la moitié de la taille des nombres
    int m = (int)(log10(x) + 1) / 2;
    int pow10 = (int)pow(10, m);
    
    // Découpe x et y en parties haute et basse
    int a = x / pow10;
    int b = x % pow10;
    int c = y / pow10;
    int d = y % pow10;
    
    // Appels récursifs pour les sous-problèmes
    int ac = karatsuba(a, c);
    int bd = karatsuba(b, d);
    int ad_plus_bc = karatsuba(a + b, c + d) - ac - bd;  // Astuce de Karatsuba
    
    // Combine les résultats
    return ac * pow(10, 2*m) + ad_plus_bc * pow(10, m) + bd;
}