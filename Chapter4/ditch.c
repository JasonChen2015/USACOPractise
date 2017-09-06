/*
ID: cyl12341
LANG: C
TASK: ditch
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 200
#define MAXC 10000000

int n, m, ans;
int network[MAXN + 1][MAXN + 1];

void networkflow() {
    int i, f, t, p, q;
    int seq[MAXN + 1]; // intersections sequence of capacity
    int e[MAXN + 1]; // the intersection whether has been reached
    int prev[MAXN + 1]; // flow from which intersection

    while (1) {
        // initialize
        for (i = 0; i <= m; i++) {
            seq[i] = 0;
            e[i] = 0;
            prev[i] = 0;
        }

        // find the shortest capacity (BFS)
        p = q = 0;
        seq[++q] = 1; // add sources
        e[1] = 1;
        f = 0; // flag that find a capacity
        while (p <= q) {
            t = seq[++p];
            for (i = 1; i <= m; i++) {
                if (!e[i] && network[t][i] > 0) {
                    seq[++q] = i;
                    e[i] = 1;
                    prev[q] = p;
                    if (i == m) { // reach sinks
                        f = 1;
                        break;
                    }
                }
            }
            if (f) break;
        }
        if (!f) break; // find no capacity

        // reduce all arcs with bottleneck
        t = MAXC; // the min rate of capacity
        i = q;
        while (seq[i] != 1) {
            if (t > network[seq[prev[i]]][seq[i]]) {
                t = network[seq[prev[i]]][seq[i]];
            }
            i = prev[i];
        }
        ans += t;
        i = q;
        while (seq[i] != 1) {
            network[seq[prev[i]]][seq[i]] -= t;
            network[seq[i]][seq[prev[i]]] += t;
            i = prev[i];
        }
    }
}

int main() {
    int i, j, k, t;

    FILE *fin = fopen("ditch.in", "r");
    FILE *fout = fopen("ditch.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d", &n, &m);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d%d%d", &j, &k, &t);
        network[j][k] += t;
    }

    ans = 0;
    networkflow();

    fprintf(fout, "%d\n", ans);

    fclose(fin);
    fclose(fout);

    return 0;
}
