/*
ID: cyl12341
LANG: C
TASK: stall4
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 200
#define MAXM 200

int n, m, ans;
int map[MAXN + 1][MAXM + 1];
int cowpair[MAXN + 1]; // the stall which match the cow n
int stallpair[MAXM + 1]; // the cow which match the stall n
// for searching
int stallseen[MAXM + 1]; // whether has searched stall n in augmenting path

int hungarian(int p) {
    int i, c;
    for (i = 1; i <= m; i++) {
        if (map[p][i] && !stallseen[i]) {
            // set new connection
            stallseen[i] = 1;

            if (!stallpair[i]) {
                ans++;
                stallpair[i] = p;
                cowpair[p] = i;
                return 1;
            } else {
                c = stallpair[i];
                stallpair[i] = p;
                cowpair[p] = i;
                cowpair[c] = 0;
                if (hungarian(c)) return 1;
            }
        }
    }
    return 0;
}

int main() {
    int i, j, k, t;

    FILE *fin = fopen("stall4.in", "r");
    FILE *fout = fopen("stall4.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        fscanf(fin, "%d", &k);
        for (j = 0; j < k; j++) {
            fscanf(fin, "%d", &t);
            map[i][t] = 1;
        }
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) stallseen[j] = 0;
        hungarian(i);
    }

    fprintf(fout, "%d\n", ans);

    fclose(fin);
    fclose(fout);

    return 0;
}
