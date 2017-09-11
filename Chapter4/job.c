/*
ID: cyl12341
LANG: C
TASK: job
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 1000
#define MAXM 30
#define MAXT 20

#define ASC 1
#define DESC 0

int n, m1, m2;
int jA[MAXN + 1], jB[MAXN + 1];
int a[MAXM + 1], b[MAXM + 1];
int tA[MAXM + 1], tB[MAXM + 1]; // machine process times

int main() {
    int i, j, t, k;
    int rA, rB;

    FILE *fin = fopen("job.in", "r");
    FILE *fout = fopen("job.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d%d", &n, &m1, &m2);
    for (i = 0; i < m1; i++) fscanf(fin, "%d", &a[i]);
    for (i = 0; i < m2; i++) fscanf(fin, "%d", &b[i]);

    // minimum time of machine As
    for (i = 0; i < n; i++) {
        t = MAXN * MAXT;
        for (j = 0; j < m1; j++) {
            if (tA[j] + a[j] < t) {
                t = tA[j] + a[j];
                k = j;
            }
        }
        tA[k] = jA[i] = t;
    }
    rA = t;

    // minimum time of machine Bs
    for (i = 0; i < n; i++) {
        t = MAXN * MAXT;
        for (j = 0; j < m2; j++) {
            if (tB[j] + b[j] < t) {
                t = tB[j] + b[j];
                k = j;
            }
        }
        tB[k] = jB[i] = t;
    }
    rB = 0;
    for (i = 0; i < n; i++) {
        if (jA[i] + jB[n - i - 1] > rB) rB = jA[i] + jB[n - i - 1];
    }

    fprintf(fout, "%d %d\n", rA, rB);

    fclose(fin);
    fclose(fout);

    return 0;
}
