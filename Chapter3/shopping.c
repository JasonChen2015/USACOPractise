/*
ID: cyl12341
LANG: C
TASK: shopping
*/

#include<stdio.h>
#include<assert.h>

#define MAXPRDCODE 1000
#define MAXITEM 6
#define MAXPRICE 25000

int list[MAXITEM];
int price[MAXPRDCODE];
int amount[MAXPRDCODE];
int offer[100][MAXPRDCODE]; // offer[i][0] -- price
int dp[MAXITEM][MAXITEM][MAXITEM][MAXITEM][MAXITEM];

int min(int a, int b) {
    if (a > b) { return b; } else { return a; }
}

int main() {
    int s, b;
    int i, j, k, l, m, n, c;
    int ni, nj, nk, nl, nm;
    FILE *fin = fopen("shopping.in", "r");
    FILE *fout = fopen("shopping.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &s);
    for (i = 0; i < s; i++) {
        fscanf(fin, "%d", &n);
        for (j = 0; j < n; j++) {
            fscanf(fin, "%d%d", &c, &k);
            offer[i][c] = k;
        }
        fscanf(fin, "%d", &offer[i][0]);
    }
    fscanf(fin, "%d", &b);
    for (i = 0; i < b; i++) {
        fscanf(fin, "%d", &c);
        fscanf(fin, "%d%d", &amount[c], &price[c]);
        list[i] = c;
        // buy one thing as an offer
        s++;
        offer[s - 1][c] = 1;
        offer[s - 1][0] = price[c];
    }

    // initialize
    for (i = 0; i < MAXITEM; i++)
    for (j = 0; j < MAXITEM; j++)
    for (k = 0; k < MAXITEM; k++)
    for (l = 0; l < MAXITEM; l++)
    for (m = 0; m < MAXITEM; m++) {
        dp[i][j][k][l][m] = MAXPRICE;
    }
    dp[0][0][0][0][0] = 0;

    // dp
    for (i = 0; i <= amount[list[0]]; i++)
    for (j = 0; j <= amount[list[1]]; j++)
    for (k = 0; k <= amount[list[2]]; k++)
    for (l = 0; l <= amount[list[3]]; l++)
    for (m = 0; m <= amount[list[4]]; m++)
    for (n = 0; n < s; n++) {
        if (list[0] != 0) ni = i + offer[n][list[0]]; else ni = i;
        if (list[1] != 0) nj = j + offer[n][list[1]]; else nj = j;
        if (list[2] != 0) nk = k + offer[n][list[2]]; else nk = k;
        if (list[3] != 0) nl = l + offer[n][list[3]]; else nl = l;
        if (list[4] != 0) nm = m + offer[n][list[4]]; else nm = m;
        if ((ni <= amount[list[0]]) && (nj <= amount[list[1]]) &&
            (nk <= amount[list[2]]) && (nl <= amount[list[3]]) &&
            (nm <= amount[list[4]])) {
            dp[ni][nj][nk][nl][nm] = min(dp[ni][nj][nk][nl][nm],
                                         dp[i][j][k][l][m] + offer[n][0]);
        }
    }

    n = dp[amount[list[0]]][amount[list[1]]][amount[list[2]]][amount[list[3]]][amount[list[4]]];
    fprintf(fout, "%d\n", n);

    fclose(fin);
    fclose(fout);
    return 0;
}

