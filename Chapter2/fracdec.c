/*
ID: cyl12341
LANG: C
TASK: fracdec
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

int e[100000];
int f[100000];

int main(void) {
    int n, d, p;
    int ok;

    FILE *fin = fopen("fracdec.in", "r");
    FILE *fout = fopen("fracdec.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &n, &d);

    memset(e, -1, sizeof(e));
    ok = 0; p = 0;
    f[p] = n / d;
    n = n % d;
    e[n] = p;
    fprintf(fout, "%d.", f[p]);
    while (!ok) {
        n *= 10;
        p++;
        f[p] = n / d;
        n = n % d;
        if (n == 0 || e[n] != -1) {
            ok = 1;
        } else {
            e[n] = p;
        }
    }

    int i, j = 1, k = f[0];
    do { j++; k /= 10; } while (k > 0);
    if (n == 0) {
        for (i = 1; i <= p; i++) {
            fprintf(fout, "%d", f[i]);
            if (++j == 76) { j = 0; fprintf(fout, "\n"); }
        }
        fprintf(fout, "\n");
    } else {
        for (i = 1; i <= e[n]; i++) {
            fprintf(fout, "%d", f[i]);
            if (++j == 76) { j = 0; fprintf(fout, "\n"); }
        }
        fprintf(fout, "(");
        if (++j == 76) { j = 0; fprintf(fout, "\n"); }
        for (i = e[n] + 1; i <= p; i++) {
            fprintf(fout, "%d", f[i]);
            if (++j == 76) { j = 0; fprintf(fout, "\n"); }
        }
        fprintf(fout, ")\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

