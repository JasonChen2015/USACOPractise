/*
ID: cyl12341
LANG: C
TASK: stamps
*/
#include <stdio.h>
#include <assert.h>

#define MINPOS(a, b) ((b == 0) ? (a) : ((a) < (b) ? (a) : (b)))

int a[2000001];
int s[201];

int main(void) {
    int k, n;
    int i, j, t, p;
    int max;

    FILE *fin = fopen("stamps.in", "r");
    FILE *fout = fopen("stamps.out", "w");
    assert(fin != NULL && fout != NULL);

    // read data
    fscanf(fin, "%d%d", &k, &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &s[i]);
        a[s[i]] = 1;
    }

    // sort stamps
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i] > s[j]) {
                t = s[i]; s[i] = s[j]; s[j] = t;
            }
        }
    }

    // fill
    max = s[n - 1];
    p = 0;
    for (i = 2; i <= k; i++) {
        for (j = 1; j <= max; j++) {
            if (a[j] == i - 1) {
                for (t = 0; t < n; t++) a[j + s[t]] = MINPOS(i, a[j + s[t]]);
            }
        }
        max += s[n - 1];
        p = 1 - p;
    }

    for (i = s[0]; i <= max; i++)
        if (a[i] == 0) break;

    fprintf(fout, "%d\n", i - 1);

    fclose(fin);
    fclose(fout);
    return 0;
}

