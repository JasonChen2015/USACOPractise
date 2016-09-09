/*
ID: cyl12341
LANG: C
TASK: preface
*/
#include <stdio.h>
#include <assert.h>

const char roman[] = "IVXLCDM";
// 1 -> 1; 10 -> 0,0,1; 100 -> 0,0,0,0,1; 1000 -> 0,0,0,0,0,0,1
const int initCount[10][3] = {{0,0,0},{1,0,0},{2,0,0},{3,0,0},{1,1,0},
                              {0,1,0},{1,1,0},{2,1,0},{3,1,0},{1,0,1}};

int count[9]; // if the num is smaller(e.g. 7), when in func getCount() have num is 1000,
              // count[i + p] will have count[2 + 6] then get error on usaco

void getCount(int num)
{
    int i, t, p;
    p = 0;
    while (num > 0) {
        t = num % 10;
        for (i = 0; i < 3; i++) {
            count[i + p] += initCount[t][i];
        }
        num = num / 10;
        p += 2;
    }
}

int main (void)
{
    int n, i;

    FILE *fin = fopen("preface.in", "r");
    FILE *fout = fopen("preface.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    for (i = 0; i < 7; i++) count[i] = 0;

    for (i = 1; i <= n; i++)
        getCount(i);

    for (i = 0; i < 7; i++)
        if (count[i] > 0)
            fprintf(fout, "%c %d\n", roman[i], count[i]);

    fclose(fin);
    fclose(fout);
    return 0;
}

