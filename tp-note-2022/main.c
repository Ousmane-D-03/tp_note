#include "graph.h"
#include "matching.h"
#include "tools.h"

int main(int argc, char *argv[]) {
    int      n    = (argc >= 2) ? atoi(argv[1]) : 10;
    unsigned seed = time(NULL) % 1000;
    printf("seed: %u\n", seed);  // pour rejouer la même chose au cas où
    srandom(seed);

    TopChrono(0);  // initialise tous les chronos

    point *V = NULL;  // tableau de points

    // Choisissez ici la façon de générer des points pour vos tests,
    // en sélectionnant une seule des lignes V = ...
    //
    V = generatePoints(n);  // n points au hasard (n provient de argv[1]
    //
    // V = generateGrid(&n, 2, 2); // un carré
    // V = generateGrid(&n, 3, 5); // une grille 3x5 (n impair)
    //
    // Les trois lignes suivantes permettent de charger des points
    // à partir d'un fichier.
    //
    // V = generateLoad(&n, "points1.txt"); // test 1
    // V = generateLoad(&n, "points2.txt"); // test 2
    // V = generateLoad(&n, "points3.txt"); // test 3: points superposés
    // V = generateLoad(&n, "points4.txt"); // test 4: Exemple 1 page 6 du sujet
    // V = generateLoad(&n, "points5.txt"); // test 5: Exemple 2 page 6 du sujet
    //
    // V = generateCircles(n, 8); // n points sur 8 cercles
    // V = generateConvex(n); // n points aléatoires en position convexe

    if (n <= 0) {
        printf("Error: n=%d, it must be at least one.\n", n);
        exit(1);
    }  // ici n>=1

    init_SDL_OpenGL();     // initialisation avant de dessiner
    drawTour(V, n, NULL);  // dessine seulement les points

#define MESSAGE                                     \
    printf("running time: %s\n", TopChrono(1));     \
    printf("waiting for a key ... [h] for help\n"); \
    fflush(stdout);

    printf("\n*** matching (basic) ***\n");
    running = true;            // force l'exécution
    TopChrono(1);              // départ du chrono 1
    graph M = createGraph(n);  // graphe vide
    printf("cost: %g\n", matching_basic(V, M));
    MESSAGE;
    bool new_redraw = true;
    update          = true;  // force l'affichage
    while (running) {
        if (new_redraw)
            matching_basic(V, M);
        drawGraph(V, n, NULL, M);
        new_redraw =
            handleEvent(update);  // attend un évènement (si affichage) ou pas
    }
    printf("\n");

    printf("*** matching (greedy) ***\n");
    running = true;  // force l'exécution
    TopChrono(1);    // départ du chrono 1
    printf("cost: %g\n", matching_greedy(V, M));
    MESSAGE;
    update = true;  // force l'affichage
    while (running) {
        if (new_redraw)
            matching_greedy(V, M);
        drawGraph(V, n, NULL, M);
        new_redraw =
            handleEvent(update);  // attend un évènement (si affichage) ou pas
    }
    printf("\n");

    printf("*** matching (rectangle) ***\n");
    running = true;  // force l'exécution
    TopChrono(1);    // départ du chrono 1
    printf("cost: %g\n", matching_rectangle(V, M));
    MESSAGE;
    new_redraw = true;
    update     = true;  // force l'affichage
    while (running) {
        if (new_redraw)
            matching_rectangle(V, M);
        drawGraph(V, n, NULL, M);
        new_redraw =
            handleEvent(update);  // attend un évènement (si affichage) ou pas
    }
    printf("\n");

    printf("*** matching (rectangle) with flip ***\n");
    running = true;  // force l'exécution
    TopChrono(1);    // départ du chrono 1
    printf("cost (before flips): %g\n", matching_rectangle(V, M));
    while (matching_flip(V, M))
        drawGraph(V, n, NULL, M);
    printf("cost (after flips): %g\n", weight(V, M));
    MESSAGE;
    new_redraw = true;
    update     = true;  // force l'affichage
    while (running) {
        if (new_redraw)
            matching_rectangle(V, M);
        update =
            !matching_flip(V, M);  // force l'affichage si pas de flip possible
        drawGraph(V, n, NULL, M);
        new_redraw =
            handleEvent(update);  // attend un évènement (si affichage) ou pas
    }
    printf("\n");
    freeGraph(M);

    // Libération de la mémoire
    TopChrono(-1);
    free(V);

    cleaning_SDL_OpenGL();
    return 0;
}
