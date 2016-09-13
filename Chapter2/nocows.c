/*
ID: cyl12341
LANG: C
TASK: nocows
*/
#include <stdio.h>
#include <assert.h>

#define MOD 9901

int a[200][100];

int main(void) {
    int n, k, i, j, l;

    FILE *fin = fopen("nocows.in", "r");
    FILE *fout = fopen("nocows.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &n, &k);

    a[1][0] = 1;
    a[1][1] = 1;
    for (j = 2; j <= k; j++) {
        a[1][j] = 1;
        for (i = 2; i <= n; i++) {
            for (l = 1; l <= i - 2; l++) {
                a[i][j] += a[l][j - 1] * a[i - 1 - l][j - 1];
                a[i][j] %= MOD;
            }
        }
    }
    
    i = (a[n][k] - a[n][k - 1] + MOD) % MOD;
    fprintf(fout, "%d\n", i);
    
    fclose(fin);
    fclose(fout);
    return 0;
}

