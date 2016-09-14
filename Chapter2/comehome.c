/*
ID: cyl12341
LANG: C
TASK: comehome
*/
#include <stdio.h>
#include <assert.h>

int c[52][52]; // 'a'(0) - 'z'(25) - 'A'(26) - 'Z'(51)
int dis[52];
int seq[10000];
int e[52];

int getPoint(char ch) {
    if ('a' <= ch && ch <= 'z') return (ch - 97);
    if ('A' <= ch && ch <= 'Z') return (ch - 39);
    return 0;
}

int main(void) {
    int n, p, q;
    int i, t;
    char ch1, ch2;

    FILE *fin = fopen("comehome.in", "r");
    FILE *fout = fopen("comehome.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    fscanf(fin, "%c", &ch1);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%c %c %d", &ch1, &ch2, &t);
        p = getPoint(ch1);
        q = getPoint(ch2);
        if (c[p][q] == 0 || c[p][q] > t) c[p][q] = c[q][p] = t;
        fscanf(fin, "%c", &ch1);
    }

    p = 0; q = 1;
    seq[q] = 51; e[seq[q]] = 1;
    while (p < q) {
        p++;
        e[seq[p]] = 0;
        for (i = 0; i < 51; i++) {
            if (i != seq[p] && c[seq[p]][i] > 0) {
                if (dis[i] == 0 || dis[seq[p]] + c[seq[p]][i] < dis[i]) {
                    dis[i] = dis[seq[p]] + c[seq[p]][i];
                    if (!e[i]) {
                        q++; seq[q] = i; e[i] = 1;
                    }
                }
            }
        }
    }

    n = 100000;
    for (i = 26; i < 51; i++) {
        if (dis[i] != 0 && dis[i] < n) {
            n = dis[i];
            p = i;
        }
    }

    fprintf(fout, "%c %d\n", p + 39, n);

    fclose(fin);
    fclose(fout);
    return 0;
}

