/*
ID: cyl12341
LANG: C
TASK: castle
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 50

int origin[MAXN + 1][MAXN + 1];
int color[MAXN + 1][MAXN + 1];
int size[MAXN * MAXN + 1];
int n, m, pcolor;

void floodfill(int pcolor, int x, int y)
{
    int precolor[MAXN * MAXN + 1][2];
    int inqueue[MAXN + 1][MAXN + 1];
    int p, q, tx, ty, i, j;
    p = 0; q = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) inqueue[j][i] = 0;
    precolor[q][0] = x; precolor[q][1] = y; inqueue[x][y] = 1;
    while (p != q) {
        p++;
        tx = precolor[p][0];
        ty = precolor[p][1];
		inqueue[tx][ty] = 0;
        color[tx][ty] = pcolor;
        // wall to the west
        if ((origin[tx][ty] & 1) == 0)
            if (tx > 1 && color[tx - 1][ty] == 0 && inqueue[tx - 1][ty] == 0) {
                q++;
                precolor[q][0] = tx - 1;
                precolor[q][1] = ty;
                inqueue[tx - 1][ty] = 1;
            }
        // wall to the north
        if ((origin[tx][ty] & 2) == 0)
            if (ty > 1 && color[tx][ty - 1] == 0 && inqueue[tx][ty - 1] == 0) {
                q++;
                precolor[q][0] = tx;
                precolor[q][1] = ty - 1;
                inqueue[tx][ty - 1] = 1;
            }
        // wall to the east
        if ((origin[tx][ty] & 4) == 0)
            if (tx < m && color[tx + 1][ty] == 0 && inqueue[tx + 1][ty] == 0) {
                q++;
                precolor[q][0] = tx + 1;
                precolor[q][1] = ty;
                inqueue[tx + 1][ty] = 1;
            }
        // wall to the south
        if ((origin[tx][ty] & 8) == 0)
            if (ty < n && color[tx][ty + 1] == 0 && inqueue[tx][ty + 1] == 0) {
                q++;
                precolor[q][0] = tx;
                precolor[q][1] = ty + 1;
                inqueue[tx][ty + 1] = 1;
            }
    }
}

int main (void)
{
    int i, j, t, maxsize, mergesize, mx, my;
    char ch;

    FILE *fin = fopen("castle.in", "r");
    FILE *fout = fopen("castle.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &m, &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) {
            fscanf(fin, "%d", &origin[j][i]);
            color[j][i] = 0;
        }

    // floodfill each module
    pcolor = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++) {
            if (color[j][i] == 0) {
                pcolor++;
                floodfill(pcolor, j, i);
            }
        }

    // calculate the size of a room
    maxsize = 0;
    for (i = 1; i <=n; i++)
        for (j = 1; j <= m; j++) {
            size[color[j][i]]++;
        }
    for (i = 1; i <= pcolor; i++)
        if (size[i] > maxsize) maxsize = size[i];

    // remove a single wall
    mergesize = maxsize;
    for (j = 1; j <= m; j++) 
        for (i = n; i >= 1; i--) {
            // wall to the north
            if ((origin[j][i] & 2) != 0 && i > 1)
                if (color[j][i] != color[j][i - 1]) {
                    t = size[color[j][i]] + size[color[j][i - 1]];
                    if (t > mergesize) {
                        mergesize = t;
                        mx = j; my = i; ch = 'N';
                    }
                }
            // wall to the east
            if ((origin[j][i] & 4) != 0 && j < m)
                if (color[j][i] != color[j + 1][i]) {
                    t = size[color[j][i]] + size[color[j + 1][i]];
                    if (t > mergesize) {
                        mergesize = t;
                        mx = j; my = i; ch = 'E';
                    }
                }
        }

    fprintf(fout, "%d\n%d\n%d\n", pcolor, maxsize, mergesize);
    fprintf(fout, "%d %d %c\n", my, mx, ch);

    fclose(fin);
    fclose(fout);
    return 0;
}

