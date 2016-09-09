/*
ID: cyl12341
LANG: C
TASK: ariprog
*/
#include <stdio.h>
#include <assert.h>

#define MAXM 250

int square[MAXM];
int bisquare[MAXM * MAXM * 2];

void createBisquare(int num)
{
    int i, j;
    for (i = 0; i <= num; i++)
        square[i] = i * i;
    for (i = 0; i <= num; i++)
        for (j = i; j <= num; j++)
            bisquare[square[i] + square[j]] = 1;
}

int main (void)
{
    int n, m, a, b, maxa, maxb, i;

    FILE *fin = fopen("ariprog.in", "r");
    FILE *fout = fopen("ariprog.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d\n%d", &n, &m);
    
    createBisquare(m);
    maxb = 2 * m * m / (n - 1);
    for (b = 1; b <= maxb; b++) {
        maxa = 2 * m * m - b * (n - 1);
        for (a = 0; a <= maxa; a++) {
            for (i = 0; i < n; i++)
                if (bisquare[a + i * b] == 0) break;
            if (i == n)
                fprintf(fout, "%d %d\n", a, b);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

