/*
ID: cyl12341
LANG: C
TASK: combo
*/
#include <stdio.h>
#include <assert.h>

#define MIN(x, y) ((x) > (y) ? (y) : (x))

// calculate the distance from x to y
int dis(int x, int y, int num)
{
    if (x > y) {
        return y - x + num;
    } else {
        return y - x;
    }
}

// adjust the position
int adjust(int pos, int num)
{
    if (pos > num) {
        return pos - num;
    } else if (pos <= 0) {
        return pos + num;
    } else {
        return pos;
    }
}

int main (void)
{
    int n, i, j, rest, sum;
    int comb[2][3];

    FILE *fin = fopen("combo.in", "r");
    FILE *fout = fopen("combo.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (i = 0; i < 2; i++)
    for (j = 0; j < 3; j++) {
        fscanf(fin, "%d", &comb[i][j]);
    }

    if (n > 5) { 
        rest = 1;
        for (i = 0; i < 3; i++) {
            int t = 0, t1, t2;
            t1 = dis(adjust(comb[1][i] - 2, n), adjust(comb[0][i] + 2, n), n) + 1;
            if (t1 <= 5) t = t + t1;
            t2 = dis(adjust(comb[0][i] - 2, n), adjust(comb[1][i] + 2, n), n) + 1;
            if (t2 <= 5) t = t + t2;
            if (t > 5) t = 5;
            rest = rest * t;
        }
        sum = 250 - rest;
    } else {
        sum = n * n * n;
    }

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}

