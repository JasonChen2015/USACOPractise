/*
ID: cyl12341
LANG: C
TASK: ttwo
*/
#include <stdio.h>
#include <assert.h>

#define SIZE 10
#define DIRECT 4

enum {
    NONE = 0, NORTH, EAST, SOUTH, WEST
};

char map[SIZE][SIZE];
int status[SIZE][SIZE][DIRECT][SIZE][SIZE][DIRECT];
int fx, fy, fd, cx, cy, cd;

void moveOneStep(int *x, int *y, int *d) {
    switch (*d) {
    case NORTH:
        if (*y == 0 || map[*y - 1][*x] == '*') {
            *d = EAST;
        } else {
            *y = *y - 1;
        }
        break;
    case EAST:
        if (*x == 9 || map[*y][*x + 1] == '*') {
            *d = SOUTH;
        } else {
            *x = *x + 1;
        }
        break;
    case SOUTH:
        if (*y == 9 || map[*y + 1][*x] == '*') {
            *d = WEST;
        } else {
            *y = *y + 1;
        }
        break;
    case WEST:
        if (*x == 0 || map[*y][*x - 1] == '*') {
            *d = NORTH;
        } else {
            *x = *x - 1;
        }
        break;
    default:
        break;
    }
}

int main(void) {
    int i, j;

    FILE *fin = fopen("ttwo.in", "r");
    FILE *fout = fopen("ttwo.out", "w");
    assert(fin != NULL && fout != NULL);

    for (i = 0; i < SIZE; i++) {
        char ch;
        for (j = 0; j < SIZE; j++) {
            fscanf(fin, "%c", &map[i][j]);
            if (map[i][j] == 'F') {
                fx = j; fy = i;
            } else if (map[i][j] == 'C') {
                cx = j; cy = i;
            }
        }
        fscanf(fin, "%c", &ch);
    }
    fd = NORTH;
    cd = NORTH;

    int ok = 0;
    int s = 0; // total of minutes
    status[fx][fy][fd][cx][cy][cd] = 1;
    while (!ok) {
        // move
        s++;
        moveOneStep(&fx, &fy, &fd);
        moveOneStep(&cx, &cy, &cd);
        if (fx == cx && fy == cy) {
            // meet
            ok = 1;
            break;
        }
        if (status[fx][fy][fd][cx][cy][cd]) {
            // repeated
            ok = 1;
            s = 0;
            break;
        }
        status[fx][fy][fd][cx][cy][cd] = 1;
    }

    fprintf(fout, "%d\n", s);

    fclose(fin);
    fclose(fout);
    return 0;
}

