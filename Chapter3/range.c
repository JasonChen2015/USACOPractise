/*
ID: cyl12341
LANG: C
TASK: range
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 250

int field[MAXN + 1][MAXN + 1]; // field[row][column]
int n, maxsize;
int sum[MAXN + 1];

int isSquare(int start_r, int start_c, int end_r, int end_c, int size) {
    int i, ok;
    ok = 1;
    if (start_r < 1 || start_c < 1 || end_r > MAXN || end_c > MAXN) return 0;
    for (i = start_r; i <= end_r; i++) {
        if (!field[i][start_c] || (field[i][end_c] - field[i][start_c] + 1 != size)) {
            ok = 0;
            break;
        }
    }
    return ok;
}

void countSquare() {
    int i, j, k;
    for (k = 2; k <= maxsize; k++) {
        for (i = 1; i <= n - k + 1; i++) {
            for (j = 1; j <= n - k + 1; j++) {
                sum[k] += isSquare(i, j, i + k - 1, j + k - 1, k);
            }
        }
    }
}

int main(void) {
    int i, j;
    char ch;
    FILE *fin = fopen("range.in", "r");
    FILE *fout = fopen("range.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fin, "%c", &ch); // read the end-line sign of previous
        for (j = 1; j <= n; j++) {
            fscanf(fin, "%c", &ch);
            if (ch == '1') {
                field[i][j] = field[i][j - 1] + 1;
                if (field[i][j] > maxsize) maxsize = field[i][j];
            }
        }
    }

    countSquare();

    for (i = 2; i <= maxsize; i++) {
        if (sum[i] > 0) {
            fprintf(fout, "%d %d\n", i, sum[i]);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

