/*
ID: cyl12341
LANG: C
TASK: holstein
*/
#include <stdio.h>
#include <assert.h>

#define MAXV 25
#define MAXG 15

int queue[32768][MAXG + 1];

int main (void)
{
    int vitamin[MAXV + 1];
    int feeds[MAXG + 1][MAXV + 1];
    int v, g, i, j, k, p, q, t;
    int flag, ok;

    FILE *fin = fopen("holstein.in", "r");
    FILE *fout = fopen("holstein.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &v);
    for (i = 1; i <= v; i++)
        fscanf(fin, "%d", &vitamin[i]);
    fscanf(fin, "%d", &g);
    for (i = 1; i <= g; i++)
        for (j = 1; j <= v; j++)
            fscanf(fin, "%d", &feeds[i][j]);

    // search the solution with BFS
    flag = 0; p = -1; q = 0;
    while (flag == 0) {
        // get the previous solution
        p++;
        for (i = queue[p][0] + 1; i <= g; i++)
            if (queue[p][i] == 0) {
                // add to queue
                q++;
                for (j = 1; j <= g; j++) queue[q][j] = queue[p][j];
                queue[q][i] = 1;
				queue[q][0] = i;
                // check after adding the ith type of feeds
                ok = 1;
                for (j = 1; j <= v; j++) {
                    t = 0;
                    for (k = 1; k <= g; k++)
                        if (queue[q][k]) t += feeds[k][j];
                    if (t < vitamin[j]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok == 1) {
                    // print the solution
                    t = 0;
                    for (j = 1; j <= g; j++)
                        if (queue[q][j] == 1) t++;
                    fprintf(fout, "%d", t);
                    for (j = 1; j <= g; j++)
                        if (queue[q][j] == 1) fprintf(fout, " %d", j);
                    flag = 1;
                    break;
                }
            }
    }
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}
