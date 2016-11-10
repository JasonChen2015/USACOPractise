/*
ID: cyl12341
LANG: C
TASK: spin
*/
#include <stdio.h>
#include <assert.h>

int speed[5];
int cextent[5];  // pairs number for a wheel
int extent[5][5][2];

int status[360];

int main() {
    int i, j, k, l, p, q;
    int s;
    FILE *fin = fopen("spin.in", "r");
    FILE *fout = fopen("spin.out", "w");
    assert(fin != NULL && fout != NULL);

    // input
    for (i = 0; i < 5; i++) {
        fscanf(fin, "%d%d", &speed[i], &cextent[i]);
        for (j = 0; j < cextent[i]; j++) fscanf(fin, "%d%d", &extent[i][j][0], &extent[i][j][1]);
    }

    // loop
    s = 0;
    for (i = 0; i < 360; i++) {
        for (j = 0; j < 360; j++) status[j] = 0;
        for (j = 0; j < 5; j++) {
            for (k = 0; k < cextent[j]; k++) {
                p = i * speed[j] + extent[j][k][0];
                q = i * speed[j] + extent[j][k][0] + extent[j][k][1];
                for (l = p; l <= q; l++) status[l % 360]++;
            }
        }
        for (j = 0; j < 360; j++) {
            if (status[j] == 5) {
                s = 1;
                break;
            }
        }
        if (s) break;
    }

    if (s == 1) {
        fprintf(fout, "%d\n", i);
    } else {
        fprintf(fout, "none\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

