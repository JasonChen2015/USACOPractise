/*
ID: cyl12341
LANG: C
TASK: rockers
*/
#include <stdio.h>
#include <assert.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MAXN 20

int s[MAXN];
int dp[MAXN + 1][MAXN + 1][MAXN + 1];

int main() {
    int n, t, m;
    int i, j, k;

    FILE *fin = fopen("rockers.in", "r");
    FILE *fout = fopen("rockers.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d%d", &n, &t, &m);
    for (i = 1; i <= n; i++) fscanf(fin, "%d", &s[i]);

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= t; k++) {
                dp[i][j][k] = MAX(dp[i][j][k - 1], dp[i][j - 1][k]);
                if (k >= s[j]) {
                    // get song
                    dp[i][j][k] = MAX(dp[i][j][k], dp[i][j - 1][k - s[j]] + 1); // same CD
                    dp[i][j][k] = MAX(dp[i][j][k], dp[i - 1][j - 1][t] + 1); // new CD
                }
            }
        }
    }

    fprintf(fout, "%d\n", dp[m][n][t]);

    fclose(fin);
    fclose(fout);

    return 0;
}

