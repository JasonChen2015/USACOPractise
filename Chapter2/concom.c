/*
ID: cyl12341
LANG: C
TASK: concom
*/
#include <stdio.h>
#include <assert.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

int n, m;
int r[101][101];  // relation
int tp[101][101]; // total p%

int main(void) {
    int i, j, k, t;

    FILE *fin = fopen("concom.in", "r");
    FILE *fout = fopen("concom.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (k = 0; k < n; k++) {
        fscanf(fin, "%d %d %d", &i, &j, &t);
        tp[i][j] = t;
        m = MAX(i, MAX(j, m));
    }

    for (i = 1; i <= m; i++) r[i][i] = 1;

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= m; j++) {
            if (i == j) continue;
            if (!r[i][j] && tp[i][j] > 50) {
                r[i][j] = 1;
                for (k = 1; k <= m; k++) {
                    tp[i][k] += tp[j][k];
                    if (r[j][k]) r[i][k] = 1;
                }
                j = 0; // relationship has been changed and search again
            }
        }
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= m; j++) {
            if (i == j) continue;
            if (r[i][j]) fprintf(fout, "%d %d\n", i, j);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

