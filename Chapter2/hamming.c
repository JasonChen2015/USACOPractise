/*
ID: cyl12341
LANG: C
TASK: hamming
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 64

int codewords[MAXN + 1];
int n, b, d, maxnum, flag;

int getHammingDistance(int x, int y)
{
    int i, t;
    t = x ^ y;
    i = 0;
    while (t != 0) {
        t = t & (t - 1);
        i++;
    }
    return i;
}

void findNext(int prev)
{
    int i, j, ok;
    if (flag == 1) return;
    for (i = prev + 1; i <= maxnum; i++) {
        // find the next codeword
        ok = 1;
        for (j = 1; j <= codewords[0]; j++)
            if (getHammingDistance(codewords[j], i) < d) {
                ok = 0;
                break;
            }
        if (ok == 1) {
            codewords[0]++;
            codewords[codewords[0]] = i;
            if (codewords[0] == n) {
                flag = 1;
            } else {
                findNext(i);
            }
            break;
        }
    }
}

int main (void)
{
    int i;

    FILE *fin = fopen("hamming.in", "r");
    FILE *fout = fopen("hamming.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &b);
    fscanf(fin, "%d", &d);

    maxnum = (1 << b) - 1;
    flag = 0;
    findNext(-1);

    for (i = 1; i <= n; i++) {
        if (i % 10 == 1) fprintf(fout, "%d", codewords[i]);
            else fprintf(fout, " %d", codewords[i]);
        if (i % 10 == 0) fprintf(fout, "\n");
    }
    if (n % 10 != 0) fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}

