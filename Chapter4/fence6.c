/*
ID: cyl12341
LANG: C
TASK: fence6
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 100
#define MAXLEN 200

int dis[2 * MAXN + 1][2 * MAXN + 1]; // distance between points
int con[MAXN + 1][MAXN + 1]; // point of fence connection

FILE *fin, *fout;
int n, min, p;

void input() {
    int i, j, k, len;
    int l, r, nl, nr;
    int tmp[MAXN + 1];

    fin = fopen("fence6.in", "r");
    fout = fopen("fence6.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    p = 0;
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &k);
        fscanf(fin, "%d%d%d", &len, &nl, &nr);
        for (j = 0; j < nl + nr; j++) fscanf(fin, "%d", &tmp[j]);
        // get left point index
        l = 0;
        for (j = 0; j < nl; j++) {
            if (con[k][tmp[j]] != 0) {
                l = con[k][tmp[j]];
                break;
            }
        }
        if (l == 0) l = ++p; // new point
        for (j = 0; j < nl; j++) {
            con[k][tmp[j]] = l;
            con[tmp[j]][k] = l;
        }
        // get right point index
        r = 0;
        for (j = nl; j < nl + nr; j++) {
            if (con[k][tmp[j]] != 0) {
                r = con[k][tmp[j]];
                break;
            }
        }
        if (r == 0) r = ++p; // new point
        for (j = nl; j < nl + nr; j++) {
            con[k][tmp[j]] = r;
            con[tmp[j]][k] = r;
        }
        //
        dis[l][r] = len;
        dis[r][l] = len;
    }
}

void bfs(int s, int l, int n, int d, int gone[MAXN + 1]) {
    int i, t;
    if (n == s && l != n) {
        // go back to start point then exit
        if (d < min) min = d;
        return;
    }
    if (n == s) { // start
        for (i = 1; i <= p; i++) gone[i] = 0;
    }
    for (i = 1; i <= p; i++) { // find the next point
        if (i == n || i == l || gone[i]) continue;
        if (dis[n][i] > 0) {
            t = d + dis[n][i];
            if (t > min) continue;
            gone[i] = 1;
            bfs(s, n, i, t, gone);
            gone[i] = 0;
        }
    }
    return;
}

int main() {
    int i;
    int gone[MAXN + 1];

    input();
    min = MAXN * MAXLEN;
    for (i = 1; i <= p; i++) {
        bfs(i, i, i, 0, gone);
    }

    fprintf(fout, "%d\n", min);

    fclose(fin);
    fclose(fout);
    return 0;
}
