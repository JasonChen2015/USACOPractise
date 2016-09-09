/*
ID: cyl12341
LANG: C
TASK: lamps
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

const int solve[2][8][4] = {
    {{0, 0, 0, 0}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 0, 1}, {0, 0, 1, 1}, {1, 1, 1, 1}},
    {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {1, 1, 1, 0}, {1, 1, 0, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}}
};
const int ways[] = {1, 4, 7, 8, 8};

int onNum[101], offNum[101];
char configure[17][255];
int n, c, parity, sum;

void changeAll(int array[])
{
    int i;
    for (i = 1; i <= n; i++) {
        array[i] = 1 - array[i];
    }
}

void changeOdd(int array[])
{
    int i;
    for (i = 1; i <= n; i += 2) {
        array[i] = 1 - array[i];
    }
}

void changeEven(int array[])
{
    int i;
    for (i = 2; i <= n; i += 2) {
        array[i] = 1 - array[i];
    }
}

void change3K(int array[])
{
    int i;
    for (i = 1; i <= n; i += 3) {
        array[i] = 1 - array[i];
    }
}

int check(int array[])
{
    int i, result = 1;
    for (i = 1; i <= onNum[0]; i++) {
        if (array[onNum[i]] == 0) {
            result = 0;
            break;
        }
    }
    if (result == 1) {
        for (i = 1; i <= offNum[0]; i++) {
            if (array[offNum[i]] == 1) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

void getPossible()
{
    int times, i, j;
    int init[101];
    times = c;
    if (c > 3 && (parity == 1)) times = 3;
    if (c > 4 && (parity == 0)) times = 4;
    for (i = 0; i < ways[times]; i++) {
        for (j = 1; j <= n; j++) init[j] = 1;
        for (j = 0; j < 4; j++) {
            if (solve[parity][i][j] == 1) {
                switch (j) {
                    case 0: changeAll(init); break;
                    case 1: changeOdd(init); break;
                    case 2: changeEven(init); break;
                    case 3: change3K(init); break;
                }
            }
        }
        if (check(init)) {
            sum++;
            for (j = 1; j <= n; j++) {
                if (init[j] == 1) {
                    configure[sum][j - 1] = '1';
                } else {
                    configure[sum][j - 1] = '0';
                }
            }
            configure[sum][j - 1] = '\0';
        }
    }
}

int main(void)
{
    FILE *fin = fopen("lamps.in", "r");
    FILE *fout = fopen("lamps.out", "w");
    assert(fin != NULL && fout != NULL);

    int i, j;

    // read
    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &c);
    parity = c % 2;
    do {
        fscanf(fin, "%d", &i);
        if (i != -1) {
            onNum[0]++;
            onNum[onNum[0]] = i;
        }
    } while (i != -1);
    do {
        fscanf(fin, "%d", &i);
        if (i != -1) {
            offNum[0]++;
            offNum[offNum[0]] = i;
        }
    } while (i != -1);

    // solve
    sum = 0;
    getPossible();
    if (sum == 0) {
        fprintf(fout, "IMPOSSIBLE\n");
    } else {
        for (i = 1; i <= sum; i++)
            for (j = i + 1; j <= sum; j++)
                if (strcmp(configure[i], configure[j]) > 0) {
                    strcpy(configure[0], configure[i]);
                    strcpy(configure[i], configure[j]);
                    strcpy(configure[j], configure[0]);
                }
        for (i = 1; i <= sum; i++)
            fprintf(fout, "%s\n", configure[i]);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

