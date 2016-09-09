/*
ID: cyl12341
LANG: C
TASK: skidesign
*/
#include <stdio.h>
#include <assert.h>

const int MAXINT = (~(unsigned int)0) / 2;

void qs(int array[], int l, int r)
{
    int i, j, mid, t;
    i = l; j = r; mid = array[(l + r) / 2];
    do {
        while (i < r && array[i] < mid) i++;
        while (l < j && mid < array[j]) j--;
        if (i <= j) {
            t = array[i]; array[i] = array[j]; array[j] = t;
            i++; j--;
        }
    } while (i <= j);
    if (i < r) qs(array, i, r);
    if (l < j) qs(array, l, j);
}

int main (void)
{
    int n, i, j, t, sum;
    int hill[1000];

    FILE *fin = fopen("skidesign.in", "r");
    FILE *fout = fopen("skidesign.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &hill[i]);
    }

    sum = MAXINT;
    qs(hill, 0, n - 1);
    for (i = hill[0]; i <= hill[n - 1] -  17; i++) {
        t = 0;
        for (j = 0; j < n; j++) {
            if (hill[j] < i) {
                t = t + (i - hill[j]) * (i - hill[j]);
            } else if (i + 17 < hill[j]) {
                t = t + (hill[j] - i - 17) * (hill[j] - i - 17);
            }
        }
        if (t < sum) sum = t;
    }

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}

