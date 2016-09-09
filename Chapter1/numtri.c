/*
ID: cyl12341
LANG: C
TASK: numtri
*/
#include <stdio.h>
#include <assert.h>

#define MAXR 1000
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main (void)
{
    int r, i, j, sum;
    int dp[MAXR + 1][MAXR + 1]; // dp[i][j] : the max sum after getting i number and reach jth position
    int tri[MAXR + 1][MAXR + 1];

    FILE *fin = fopen("numtri.in", "r");
    FILE *fout = fopen("numtri.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &r);
    for (i = 1; i <= r; i++)
        for (j = 1; j <= i; j++) {
            fscanf(fin, "%d", &tri[i][j]);
        }

    //initialize
    for (i = 0; i <= r; i++) {
        dp[0][i] = 0;
        dp[i][0] = 0;
    }
    //solve
    for (i = 1; i <= r; i++) {
        for (j = 1; j <= i; j++) {
            dp[i][j] = MAX(dp[i - 1][j], dp[i - 1][j - 1]) + tri[i][j];
        }
    }
    sum = 0;
    for (i = 1; i <= r; i++)
        sum = MAX(sum, dp[r][i]);

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}

