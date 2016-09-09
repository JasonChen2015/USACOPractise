/*
ID: cyl12341
LANG: C
TASK: subset
*/
#include <stdio.h>
#include <assert.h>

int n;
long long a[780][39];

int main(void) {
    int i, j, s;

    FILE *fin = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    s = (1 + n) * n / 2;

    if (s % 2 == 0) {
        s = s / 2;  // the sum of a set
        for (j = 1; j <= n; j++) {
            a[j][j] = 1;
            int t = (1 + j) * j / 2;
            if (t > s) t = s;
            for (i = 1; i <= t; i++) {
                a[i][j] += a[i][j - 1];
                if (i >= j)
                    a[i][j] += a[i - j][j - 1];
            }
        }
    }

    long long count = a[s][n] / 2;
    fprintf(fout, "%lld\n", count);

    fclose(fin);
    fclose(fout);

    return 0;
}

