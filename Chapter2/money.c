/*
ID: cyl12341
LANG: C
TASK: money
*/
#include <stdio.h>
#include <assert.h>

int v, n;
int values[25];
long long a[10001][25];

void qs(int l, int r) {
    int i, j, mid, t;
    i = l; j = r; mid = values[(i + j) / 2];
    do {
        while (i < r && values[i] < mid) i++;
        while (l < j && mid < values[j]) j--;
        if (i <= j) {
            t = values[i];
            values[i] = values[j];
            values[j] = t;
            i++; j--;
        }
    } while (i < j);
    if (l < j) qs(l, j);
    if (i < r) qs(i, r);
}

int main(void) {
    FILE *fin = fopen("money.in", "r");
    FILE *fout = fopen("money.out", "w");
    assert(fin != NULL && fout != NULL);

    int i, j, k;
    long long s = 0;

    fscanf(fin, "%d %d", &v, &n);
    for (i = 0; i < v; i++) {
        fscanf(fin, "%d", &j);
        values[i] = j;
    }
    qs(0, v - 1);

    for (i = 1; i <= n; i++) {
        for (j = 0; j < v; j++) {
            if (i < values[j]) continue;
            if (i == values[j]) {
                a[i][j]++;
                break;
            }
            for (k = 0; k <= j; k++) {
                a[i][j] += a[i - values[j]][k];
            }
        }
    }

    for (i = 0; i < v; i++) s += a[n][i];

    fprintf(fout, "%lld\n", s);

    fclose(fin);
    fclose(fout);
    return 0;
}

