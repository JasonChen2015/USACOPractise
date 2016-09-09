/*
ID: cyl12341
LANG: C
TASK: beads
 */
#include <stdio.h>
#include <assert.h>

int main(void)
{
    int i, j, n;
    int sum, tmp;
    char ch, beads[700];
    char l, r; // the left color and right color

    FILE *fin = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d\n", &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%c", &ch);
        beads[i] = ch;
        beads[i + n] = ch;
    }

    sum = 0;
    for (i = 0; i < 2 * n; i++) {
        tmp = 0;
        // from left to right
        j = i;
        r = beads[i];
        while ((j < 2 * n) && (beads[j] == r || beads[j] == 'w')) {
            j++;
            // keep getting white until get a colored one
            if (j < 2 * n && r == 'w' && beads[j] != 'w') r = beads[j];
        }
        tmp += j - i;
        // from right to left
        j = i -1;
        l = beads[i - 1];
        while ((j >= 0) && (beads[j] == l || beads[j] == 'w')) {
            j--;
            // keep getting white until get a colored one
            if (j >= 0 && l == 'w' && beads[j] != 'w') r = beads[j];
        }
        tmp += i - j - 1;
        // cause all the beads are the same color
        if (tmp > n) tmp = n;
        if (tmp > sum) sum = tmp;
    }

    fprintf(fout, "%d\n", sum);

    fclose(fout);
    return 0;
}

