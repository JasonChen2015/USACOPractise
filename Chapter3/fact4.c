/*
ID: cyl12341
LANG: C
TASK: fact4
*/
#include <stdio.h>
#include <assert.h>

int main() {
    int n, s = 1;
    int c2 = 0, c5 = 0;;
    int i, t;

    FILE *fin = fopen("fact4.in", "r");
    FILE *fout = fopen("fact4.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    for (i = 2; i <= n; i++) {
        // get the last none 0 number
        t = i;
        while (t % 10 == 0) { t = t / 10; } // remove suffix 0
        // get factor 2 & 5
        while (t % 2 == 0) { t = t / 2; c2++; }
        while (t % 5 == 0) { t = t / 5; c5++; }
        s = (s * t) % 10;
    }
    if (c2 > c5) {
        c2 = (c2 - c5) % 4 + 4;
        for (i = 0; i < c2; i++) s = (s * 2) % 10;
    }
    fprintf(fout, "%d\n", s);
    
    fclose(fin);
    fclose(fout);
    return 0;
}

