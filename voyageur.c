int held_karp(int dist[][n], int n) {
    int dp[1<<n][n];
    // Initialisation
    for (int i=0; i<n; i++) dp[1<<i][i] = dist[0][i];
    // Remplissage DP
    for (int mask=1; mask<(1<<n); mask++) {
        for (int i=0; i<n; i++) {
            if (mask & (1<<i)) {
                for (int j=0; j<n; j++) {
                    if (j != i && (mask & (1<<j))) {
                        dp[mask][i] = min(dp[mask][i], dp[mask^(1<<i)][j] + dist[j][i]);
                    }
                }
            }
        }
    }
    return dp[(1<<n)-1][0]; // Retour à la ville de départ
}