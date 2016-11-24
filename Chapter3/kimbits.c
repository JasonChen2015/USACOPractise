/*
ID: cyl12341
LANG: C
TASK: kimbits
*/
#include <stdio.h>
#include <assert.h>

long long dp[32][32];

int main() {
    int n, l;
    long long m;
    int i, j;
    char c[32] = "00000000000000000000000000000000";
    FILE *fin = fopen("kimbits.in", "r");
    FILE *fout = fopen("kimbits.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d%lld", &n, &l, &m);

    dp[0][0] = 1; dp[0][1] = 0;
    for (i = 1; i <= n; i++) {
        dp[i][0] = 1;
        for (j = 1; j < i; j++) dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        for (j = i; j <= n; j++) dp[i][j] = dp[i][i - 1] + 1;
    }
    i = n;
    while (m > 0) {
        if (l == 0 || m == 1) break;
        for (; i >= 0; i--) {
            if (dp[i][l] < m) {
                break;
            }
        }
        c[n - i - 1] = '1';
        m = m - dp[i][l];
        l--;
    }
    c[n] = '\0';

    fprintf(fout, "%s\n", c);
    return 0;
}

