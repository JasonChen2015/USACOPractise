/*
ID: cyl12341
LANG: C
TASK: ratios
*/
#include <stdio.h>
#include <assert.h>

int main() {
    int a[3], b[3], c[3], d[3], t[3], s[4];
    int i, j, k, t0, t1, t2, q;
    FILE *fin = fopen("ratios.in", "r");
    FILE *fout = fopen("ratios.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d%d", &d[0], &d[1], &d[2]);
    fscanf(fin, "%d%d%d", &a[0], &a[1], &a[2]);
    fscanf(fin, "%d%d%d", &b[0], &b[1], &b[2]);
    fscanf(fin, "%d%d%d", &c[0], &c[1], &c[2]);

    q = 0;
    for (i = 0; i < 100; i++) {
        if (!q)
        for (j = 0; j < 100; j++) {
            if (!q)
            for (k = 0;  k < 100; k++) {
                if (i == 0 && j == 0 && k == 0) continue;
                // mixture radio
                t[0] = i * a[0] + j * b[0] + k * c[0];
                t[1] = i * a[1] + j * b[1] + k * c[1];
                t[2] = i * a[2] + j * b[2] + k * c[2];
                // multiple of goal radio
                if (d[0] != 0) { t0 = t[0] % d[0]; } else { t0 = 0; }
                if (d[1] != 0) { t1 = t[1] % d[1]; } else { t1 = 0; }
                if (d[2] != 0) { t2 = t[2] % d[2]; } else { t2 = 0; }
                if (t0 == 0 && t1 == 0 && t2 == 0) {
                    // check whether same multiple or not
                    if (d[0] != 0) { t[0] /= d[0]; } else { t[0] = 0; }
                    if (d[1] != 0) { t[1] /= d[1]; } else { t[1] = 0; }
                    if (d[2] != 0) { t[2] /= d[2]; } else { t[2] = 0; }
                    if (t[0] != 0 && t[1] != 0 && t[0] == t[1]) q++;
                    if (t[0] != 0 && t[2] != 0 && t[0] == t[2]) q++;
                    if (t[1] != 0 && t[2] != 0 && t[1] == t[2]) q++;
                    if (q == 3 || (q == 1 && d[0] * d[1] * d[2] == 0)) {
                        // get the answer
                        s[0] = i; s[1] = j; s[2] = k;
                        if (t[0] != 0) { s[3] = t[0]; } else { s[3] = t[1]; }
                        break;
                    }
                    q = 0;
                }
            }
        }
    }

    if (!q) {
        fprintf(fout, "NONE\n");
    } else {
        fprintf(fout, "%d %d %d %d\n", s[0], s[1], s[2], s[3]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

