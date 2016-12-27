/*
ID: cyl12341
LANG: C
TASK: game1
*/
#include <stdio.h>
#include <assert.h>

#define MAXPOS 100

int a[2][MAXPOS + 1][MAXPOS + 1];
int seq[MAXPOS + 1];

// picker's turn  in range [s, e], return player's score
int getScore(int player, int start, int end, int picker) {
    int i, j;
    int result = 0;
    if (a[player][start][end]) return a[player][start][end];
    if (start == end) {
        if (player == picker) {
            result = seq[start];
        } else {
            result = 0;
        }
    } else {
        i = getScore(picker, start + 1, end, 1 - picker) + seq[start];
        j = getScore(picker, start, end - 1, 1 - picker) + seq[end];
        if (i > j) {
            // picker get left one
            if (player == picker) {
                result = i;
            } else {
                result = getScore(player, start + 1, end, 1 - picker);
            }
        } else {
            // picker get right one
            if (player == picker) {
                result = j;
            } else {
                result = getScore(player, start, end - 1, 1 - picker);
            }
        }
    }
    a[player][start][end] = result;
    return a[player][start][end];
}

int main() {
    int n;
    int i;
    FILE *fin = fopen("game1.in", "r");
    FILE *fout = fopen("game1.out", "w");

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) fscanf(fin, "%d", &seq[i + 1]);

    fprintf(fout, "%d %d\n", getScore(0, 1, n, 0), getScore(1, 1, n, 0));

    fclose(fin);
    fclose(fout);
    return 0;
}

