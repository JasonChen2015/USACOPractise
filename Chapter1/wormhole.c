/*
ID: cyl12341
LANG: C
TASK: wormhole
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 12

int n;
int hole[MAXN + 1][2];
int partner[MAXN + 1];
int next[MAXN + 1];

int checkCircle(void)
{
    int i, pos, start;
    for (start = 1; start <= n; start++) {
        pos = start;
        for (i = 1; i <= n; i++)
            pos = next[partner[pos]];
        if (pos != 0) return 1;
    }
    return 0;
}

int solve(void)
{
    int i, j, total = 0;
    // find the unpaired hole
    for (i = 1; i <= n; i++) {
        if (partner[i] == 0) break;
    }
    // if all paired then check
    if (i > n) {
        if (checkCircle() == 1) return 1;
        else return 0;
    }
    // pair the hole
    for (j = i + 1; j <= n; j++) {
        if (partner[j] == 0) {
            partner[i] = j;
            partner[j] = i;
            total = total + solve();
            partner[i] = 0;
            partner[j] = 0;
        }
    }
    return total;
}

int main (void)
{
    int i, j;

    FILE *fin = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fin, "%d %d", &hole[i][0], &hole[i][1]);
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            if (hole[i][0] < hole[j][0] && hole[i][1] == hole[j][1])
                if (next[i] == 0 ||
                    (hole[j][0] - hole[i][0] < hole[next[i]][0] - hole[i][0]))
                    next[i] = j;
    }

    fprintf(fout, "%d\n", solve());

    fclose(fin);
    fclose(fout);
    return 0;
}

