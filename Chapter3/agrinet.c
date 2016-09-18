/*
ID: cyl12341
LANG: C
TASK: agrinet
*/

#include <stdio.h>
#include <assert.h>

#define INF 1e6

int dis[100][100];
int e[100];
int l[100];

int main(void) {
    int n;
    int i, j, s, len;

    FILE *fin = fopen("agrinet.in", "r");
    FILE *fout = fopen("agrinet.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) fscanf(fin, "%d", &dis[i][j]);
        l[i] = dis[0][i];
    }

    // add first node
    s = 1; len = 0;
    e[0] = 1;
    while (s < n) {
        int t = INF;
        // choose the next point
        for (i = 0; i < n; i++)
            if (!e[i] && l[i] < t) {
                t = l[i]; j = i;
            }
        s++; e[j] = 1; len += l[j];
        // refresh the distance
        for (i = 0; i < n; i++)
            if (i != j && !e[i] && dis[i][j] < l[i]) l[i] = dis[i][j];
    }

    fprintf(fout, "%d\n", len);

    return 0;
}

