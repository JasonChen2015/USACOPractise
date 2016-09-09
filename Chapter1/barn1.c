/*
ID: cyl12341
LANG: C
TASK: barn1
 */
#include <stdio.h>
#include <assert.h>

#define MAXINT 1000

#define MIN(x, y) ((x) > (y) ? (y) : (x))

void qs(int array[], int l, int r) {
    int i, j, mid, t;
    i = l;
    j = r;
    mid = array[(l + r) / 2];
    do {
        while (i < r && array[i] < mid) i++;
        while (l < j && mid < array[j]) j--;
        if (i <= j) {
            t = array[i];
            array[i] = array[j];
            array[j] = t;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) qs(array, l, j);
    if (i < r) qs(array, i, r);
}


int main (void)
{
    int m, s, c, i, j, k;
    int barn[201];      // record if the stalls have cows in them
    int dp[51][201];    // dp[i][j] the min arrangement with i boards cover j stall

    FILE *fin = fopen("barn1.in", "r");
    FILE *fout = fopen("barn1.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d %d", &m, &s, &c);
    for (i = 1; i <= c; i++) {
        fscanf(fin, "%d", &barn[i]);
    }

    qs(barn, 1, c);
    if (m > c) m = c; // boards will not be more than stalls
    for (i = 1; i <= m; i++) {
        dp[i][0] = 0;
		dp[i][1] = 1;
        for (j = 2; j <= c; j++) {
            dp[i][j] = dp[i][j - 1] + barn[j] - barn[j - 1];
            if (i > 1) {
                for (k = 1; k < i; k++) {
                    dp[i][j] = MIN(dp[i][j], dp[k][j - 1] + 1);
                }
            }
        }
    }

    fprintf(fout, "%d\n", dp[m][c]);

    fclose(fin);
    fclose(fout);
    return 0;
}

