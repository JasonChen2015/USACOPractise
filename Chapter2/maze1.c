/*
ID: cyl12341
LANG: C
TASK: maze1
*/
#include <stdio.h>
#include <assert.h>

char map[201][77];
int dis[100][38];
int seq[4000][2];

int main(void) {
    int w, h, p, q;
    int i, j;
    char ch;

    FILE *fin = fopen("maze1.in", "r");
    FILE *fout = fopen("maze1.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &w, &h);
    fscanf(fin, "%c", &ch);
    int ww = 2 * w, hh = 2 * h;
    for (i = 0; i <= hh; i++) {
        for (j = 0; j <= ww; j++) fscanf(fin, "%c", &map[i][j]);
        fscanf(fin, "%c", &ch);
    }

    // initialize the sequence
    p = 0; q = 0;
    for (i = 0; i < w; i++) {
        if (map[0][2 * i + 1] == ' ' && dis[0][i] == 0) {
            dis[0][i] = 1;
            q++; seq[q][0] = 0; seq[q][1] = i;
        }
        if (map[hh][2 * i + 1] == ' ' && dis[h - 1][i] == 0) {
            dis[h - 1][i] = 1;
            q++; seq[q][0] = h - 1; seq[q][1] = i;
        }
    }
    for (i = 0; i < h; i++) {
        if (map[2 * i + 1][0] == ' ' && dis[i][0] == 0) {
            dis[i][0] = 1;
            q++; seq[q][0] = i; seq[q][1] = 0;
        }
        if (map[2 * i + 1][ww] == ' ' && dis[i][w - 1] == 0) {
            dis[i][w - 1] = 1;
            q++; seq[q][0] = i; seq[q][1] = w - 1;
        }
    }

    // bfs
    while (p < q) {
        p++;
        int py = seq[p][0], px = seq[p][1];
        // up
        if (py > 0 && dis[py - 1][px] == 0 && map[2 * py][2 * px + 1] == ' ') {
            dis[py - 1][px] = dis[py][px] + 1;
            q++; seq[q][0] = py - 1; seq[q][1] = px;
        }
        // down
        if (py < h - 1 && dis[py + 1][px] == 0 && map[2 * py + 2][2 * px + 1] == ' ') {
            dis[py + 1][px] = dis[py][px] + 1;
            q++; seq[q][0] = py + 1; seq[q][1] = px;
        }
        // left
        if (px > 0 && dis[py][px - 1] == 0 && map[2 * py + 1][2 * px] == ' ') {
            dis[py][px - 1] = dis[py][px] + 1;
            q++; seq[q][0] = py; seq[q][1] = px - 1;
        }
        // right
        if (px < w - 1 && dis[py][px + 1] == 0 && map[2 * py + 1][2 * px + 2] == ' ') {
            dis[py][px + 1] = dis[py][px] + 1;
            q++; seq[q][0] = py; seq[q][1] = px + 1;
        }
    }

    int s = 0;
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            if (dis[i][j] > s) s = dis[i][j];
    fprintf(fout, "%d\n", s);

    fclose(fin);
    fclose(fout);
    return 0;
}

