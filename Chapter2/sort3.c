/*
ID: cyl12341
LANG: C
TASK: sort3
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 1000
#define INTNUM 3
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main (void)
{
    int num[MAXN + 1];
    int count[INTNUM + 1];
    int map[INTNUM + 1][INTNUM + 1];
    int n, i, j, sum;

    FILE *fin = fopen("sort3.in", "r");
    FILE *fout = fopen("sort3.out", "w");
    assert(fin != NULL && fout != NULL);

    for (i = 1; i <= 3; i++) count[i] = 0;
    for (i = 1; i <= 3; i++)
        for (j = 1; j <= 3; j++) map[i][j] = 0;

    fscanf(fin, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fin, "%d", &num[i]);
        count[num[i]]++;
    }

    for (i = 1; i <=n; i++)
        if (i <= count[1]) {
            if (num[i] != 1) map[1][num[i]]++;
        } else if (i <= count[1] + count[2]) {
            if (num[i] != 2) map[2][num[i]]++;
        } else {
            if (num[i] != 3) map[3][num[i]]++;
        }

    sum = 0;
    // exchange 1 and 2
    if (map[1][2] != 0 && map[2][1] != 0)
        sum += MIN(map[1][2], map[2][1]);
    // exchange 1 and 3
    if (map[1][3] != 0 && map[3][1] != 0)
        sum += MIN(map[1][3], map[3][1]);
    // exchange 2 and 3
    if (map[2][3] != 0 && map[3][2] != 0)
        sum += MIN(map[2][3], map[3][2]);
    // exchange 1 and 2 and 3
    sum += (MAX(map[1][2], map[2][1]) - MIN(map[1][2], map[2][1])) * 2;

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}
