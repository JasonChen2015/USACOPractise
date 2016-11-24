/*
ID: cyl12341
LANG: C
TASK: butter
*/
#include <stdio.h>
#include <assert.h>

#define MAXDIS 180000

int n, m, c;
int linkcount[801];
int maplink[801][801];
int map[801][801];
int cow[501];

int spfa(int s) {
    int i, j, t, p, q;
    int dis[801];   // the distance to point s
    int e[801];     // if point exist in queue
    int queue[2000]; // record the point to be process
    for (i = 0; i <= m; i++) { dis[i] = MAXDIS; e[i] = 0; }
    dis[s] = 0;
    p = -1; q = 0; queue[q] = s; e[queue[q]] = 1;
    while (p < q) {
        p++;
        for (i = 0; i < linkcount[queue[p]]; i++) {
            j = maplink[queue[p]][i];
            if (j != s) {
                t = dis[queue[p]] + map[queue[p]][j];
                if (dis[j] > t) {
                    dis[j] = t;
                    if (!e[j]) {
                        q++; queue[q] = j; e[j] = 1;
                    }
                }
            }
        }
        e[queue[p]] = 0;
    }
    // count the units that cow walks to point s
    t = 0;
    for (i = 0; i < n; i++) {
        t += dis[cow[i]];
    }
    return t;
}

int main() {
    int i, j, k, max;
    FILE *fin = fopen("butter.in", "r");
    FILE *fout = fopen("butter.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d%d", &n, &m, &c);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &cow[i]);
    }
    for (i = 0; i < c; i++) {
        fscanf(fin, "%d%d", &j, &k);
        fscanf(fin, "%d", &map[j][k]);
        map[k][j] = map[j][k];
        linkcount[j]++; maplink[j][linkcount[j] - 1] = k;
        linkcount[k]++; maplink[k][linkcount[k] - 1] = j;
    }

    max = MAXDIS;
    for (i = 1; i <= m; i++) {
        k = spfa(i);
        max = max > k ? k : max;
    }

    fprintf(fout, "%d\n", max);

    fclose(fin);
    fclose(fout);
    return 0;
}

