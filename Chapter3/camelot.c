/*
ID: cyl12341
LANG: C
TASK: camelot
*/
#include <stdio.h>
#include <assert.h>

#define MAXCOL 26
#define MAXROW 30
#define MAXSTEP (26 * 30)

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) ((x) > 0 ? (x) : (-(x)))

const int knightMove[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
                              {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};
const int kingMove[25][2] = {// no move
                            {0, 0},
                            // one move
                            {-1, 0}, {-1, -1}, {0, -1}, {1, -1},
                            {1, 0}, {1, 1}, {0, 1}, {-1, 1},
                            // two moves
                            {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
                            {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {0, -2}, {0, 2},
                            {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}
                            };

FILE *fin, *fout;
int r, c, kingr, kingc, ksum;
int kpos[MAXSTEP + 1][2];
int dist[MAXCOL + 1][MAXROW + 1][MAXCOL + 1][MAXROW + 1];

// for BFS use
int queue[MAXSTEP + 1][2];
int v[MAXCOL + 1][MAXROW + 1]; // if visit the square
int e[MAXCOL + 1][MAXROW + 1]; // if exist in queue

void getData() {
    int i, e = 0;
    char ch;
    fscanf(fin, "%d%d", &r, &c);
    while (fscanf(fin, "%c", &ch) != EOF) {
        while (fscanf(fin, "%c", &ch) != EOF && (ch == '\n' || ch == ' ')); // read column
        if (ch < 'A' || ch > 'Z') break;
        fscanf(fin, "%d", &i);
        if (!e) {
            kingc = ch - 'A' + 1;
            kingr = i;
            e = 1;
        } else {
            kpos[ksum][0] = ch - 'A' + 1; // column
            kpos[ksum][1] = i;            // row
            ksum++;
        }
    }
}

void countKnightMoves(int col, int row) {
    int p, q, i, j, k, x, y;

    // initial
    for (i = 1; i <= c; i++) {
        for (j = 1; j <= r; j++) {
            v[i][j] = 0; e[i][j] = 0;
            dist[col][row][i][j] = MAXSTEP;
        }
    }
    dist[col][row][col][row] = 0;

    // bfs
    p = q = 0;
    queue[q][0] = col;
    queue[q][1] = row;
    while (p <= q) {
        x = queue[p][0];
        y = queue[p][1];
        v[x][y] = 1;
        for (k = 0; k < 8; k++) {
            int nx = x + knightMove[k][0];
            int ny = y + knightMove[k][1];
            if (nx <= 0 || nx > c || ny <= 0 || ny > r) continue;
            if (v[nx][ny] == 1) continue;
            if (e[nx][ny] == 0) {
                dist[col][row][nx][ny] = dist[col][row][x][y] + 1;
                q++; queue[q][0] = nx; queue[q][1] = ny;
                e[nx][ny] = 1;
            }
        }
        p++;
    }
}

int main() {
    int i, j, k, l, ans, sum, tmp, km;

    fin = fopen("camelot.in", "r");
    fout = fopen("camelot.out", "w");
    assert(fin != NULL && fout != NULL);

    // input data
    getData();

    // count step between each square
    for (i = 1; i <= c; i++) {
        for (j = 1; j <= r; j++)
            countKnightMoves(i, j);
    }

    // count
    ans = MAXSTEP * (ksum + 1);
    for (i = 1; i <= c; i++) {
        for (j = 1; j <= r; j++) {
            sum = 0;
            km = MAX(ABS(kingc - i), ABS(kingr - j));
            for (k = 0; k < ksum; k++) sum += dist[i][j][kpos[k][0]][kpos[k][1]];
            sum += km;
            ans = MIN(ans, sum);

            // judge if knight carry king with king's move(s)
            for (l = 0; l < 25; l++) {
                int x = kingc + kingMove[l][0];
                int y = kingr + kingMove[l][1];
                if (x <=0 || x > c || y <= 0 || y > r) continue;
                for (k = 0; k < ksum; k++) {
                    tmp = sum - dist[i][j][kpos[k][0]][kpos[k][1]] - km + 1
                            + dist[kpos[k][0]][kpos[k][1]][x][y] + dist[x][y][i][j];
                    // first element of kingMove array is no move
                    if (l == 0) tmp -= 1;
                    // from 9th element of kingMove array is two moves
                    if (l >= 9) tmp += 1;

                    // compare with final answer
                    if (ans > tmp) ans = tmp;
                }
            }
        }
    }

    fprintf(fout, "%d\n", ans);

    fclose(fin);
    fclose(fout);
    return 0;
}

