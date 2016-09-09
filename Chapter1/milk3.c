/*
ID: cyl12341
LANG: C
TASK: milk3
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 20

int bucket[MAXN + 1][MAXN + 1][MAXN + 1];
int amount[MAXN + 1];
int a, b, c;

void pourMilk(int i, int j, int k)
{
    if (i == 0) amount[k] = 1;
    if (i != a) {
        // pour c -> a
        if (k > 0) {
            if (k + i >= a) {
                if (bucket[a][j][k - (a - i)] == 0) {
                    bucket[a][j][k - (a - i)] = 1;
                    pourMilk(a, j, k - (a - i));
                }
            } else {
                if (bucket[i + k][j][0] == 0) {
                    bucket[i + k][j][0] = 1;
                    pourMilk(i + k, j, 0);
                }
            }
        }
        // pour b -> a
        if (j > 0) {
            if (j + i >= a) {
                if (bucket[a][j - (a - i)][k] == 0) {
                    bucket[a][j - (a - i)][k] = 1;
                    pourMilk(a, j - (a - i), k);
                }
            } else {
                if (bucket[i + j][0][k] == 0) {
                    bucket[i + j][0][k] = 1;
                    pourMilk(i + j, 0, k);
                }
            }
        }
    }
    if (j != b) {
        // pour c -> b
        if (k > 0) {
            if (k + j >= b) {
                if (bucket[i][b][k - (b - j)] == 0) {
                    bucket[i][b][k - (b - j)] = 1;
                    pourMilk(i, b, k - (b - j));
                }
            } else {
                if (bucket[i][j + k][0] == 0) {
                    bucket[i][j + k][0] = 1;
                    pourMilk(i, j + k, 0);
                }
            }
        }
        // pour a -> b
        if (i > 0) {
            if (i + j >= b) {
                if (bucket[i - (b - j)][b][k] == 0) {
                    bucket[i - (b - j)][b][k] = 1;
                    pourMilk(i - (b - j), b, k);
                }
            } else {
                if (bucket[0][i + j][k] == 0) {
                    bucket[0][i + j][k] = 1;
                    pourMilk(0, i + j, k);
                }
            }
        }
    }
    if (k != c) {
        // pour a -> c
        if (i > 0) {
            if (i + k >= c) {
                if (bucket[i - (c - k)][j][c] == 0) {
                    bucket[i - (c - k)][j][c] = 1;
                    pourMilk(i - (c - k), j, c);
                }
            } else {
                if (bucket[0][j][i + k] == 0) {
                    bucket[0][j][i + k] = 1;
                    pourMilk(0, j, i + k);
                }
            }
        }
        // pour b -> c
        if (j > 0) {
            if (j + k >= c) {
                if (bucket[i][j - (c - k)][c] == 0) {
                    bucket[i][j - (c - k)][c] = 1;
                    pourMilk(i, j - (c - k), c);
                }
            } else {
                if (bucket[i][0][j + k] == 0) {
                    bucket[i][0][j + k] = 1;
                    pourMilk(i, 0, j + k);
                }
            }
        }
    }
}

int main (void)
{
    int i, flag = 0;

    FILE *fin = fopen("milk3.in", "r");
    FILE *fout = fopen("milk3.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d %d", &a, &b, &c);

    bucket[0][0][c] = 1;
    pourMilk(0, 0, c);

    for (i = 0; i <= c; i++)
        if (amount[i] == 1) {
            if (flag == 0) {
                fprintf(fout, "%d", i);
                flag = 1;
            } else {
                fprintf(fout, " %d", i);
            }
        }
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}

