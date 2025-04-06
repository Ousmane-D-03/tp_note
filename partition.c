#define MAX 1000
long dp[MAX][MAX];  // Tableau de mémoïsation

/**
 * Calcule le nombre de partitions de 'n' en 'k' parts
 * @param n Nombre à partitionner
 * @param k Nombre de parts
 * @return Nombre de partitions
 */
long partition_dp(int n, int k) {
    // Si déjà calculé, retourne la valeur stockée
    if (dp[n][k] != -1) return dp[n][k];
    
    // Cas de base : 1 seule façon si 1 part ou parts = n
    if (k == 1 || k == n) return dp[n][k] = 1;
    
    // Si les parts sont trop grandes, ignore le type 2
    if (n < 2 * k) return dp[n][k] = partition_dp(n - 1, k - 1);
    
    // Appel récursif : partitions de type 1 (avec 1) + type 2 (sans 1)
    return dp[n][k] = partition_dp(n - 1, k - 1) + partition_dp(n - k, k);
}

// Initialisation du tableau DP
void init_dp() {
    memset(dp, -1, sizeof(dp));  // -1 = non calculé
}

//dynammique
long p_dp(int n) {
    long dp[n+1][n+1];
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=n; j++) {
            if (j == 1 || i == j) dp[i][j] = 1;
            else if (i < 2*j) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
        }
    }
    long sum = 0;
    for (int k=1; k<=n; k++) sum += dp[n][k];
    return sum;
}

#include <stdio.h>

// Échange deux éléments
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition pour QuickSelect
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

// Trouve le k-ième plus petit élément
int quickSelect(int arr[], int left, int right, int k) {
    if (left == right) return arr[left];
    int pivotIndex = partition(arr, left, right);
    if (k == pivotIndex) return arr[k];
    else if (k < pivotIndex) return quickSelect(arr, left, pivotIndex - 1, k);
    else return quickSelect(arr, pivotIndex + 1, right, k);
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19};
    int n = 6, k = 3; // k=3 → 4ème élément (indices 0 à 5)
    printf("Le %d-ème plus petit élément est %d\n", k + 1, quickSelect(arr, 0, n - 1, k));
    return 0;
}