/*
ID: cyl12341
LANG: C
TASK: humble
*/
#include <stdio.h>
#include <assert.h>

int s[101];
int p[101];  // store which index of humble number to be multiplied
long h[100001];

int main(void) {
    int k, n;
    int q, i;
    long j, t;

    FILE *fin = fopen("humble.in", "r");
    FILE *fout = fopen("humble.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d", &k, &n);
    for (i = 0; i < k; i++) {
        fscanf(fin, "%d", &s[i]);
        p[i] = 0;
    }

    q = 0; h[q] = 1;
    while (q < n) {
        t = s[0] * h[p[0]];
        for (i = 1; i < k; i++) {
            j = s[i] * h[p[i]];
            if (j < t) {
                t = j;
            }
        }
        q++; h[q] = t; // new humble number
        // skip the repeated number
        for (i = 0; i < k; i++)
            if (s[i] * h[p[i]] == t) p[i]++;
    }

    fprintf(fout, "%ld\n", h[n]);

    fclose(fin);
    fclose(fout);
    return 0;
}

