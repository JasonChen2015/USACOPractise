/*
ID: cyl12341
LANG: C
TASK: inflate
*/

#include <stdio.h>
#include <assert.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

int dp[10001];

int main(void) {
    int m, n, v, t;
    int i, j;

    FILE *fin = fopen("inflate.in", "r");
    FILE *fout = fopen("inflate.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d", &m, &n);
    for (i = 1; i <= n; i++) {
        fscanf(fin, "%d%d", &v, &t);
        for (j = t; j <= m; j++) {
            dp[j] = MAX(dp[j], dp[j - t] + v);
        }
    }

    fprintf(fout, "%d\n", dp[m]);

    return 0;
}

