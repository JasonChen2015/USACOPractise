/*
ID: cyl12341
LANG: C
TASK: frac1
*/
#include <stdio.h>
#include <assert.h>

typedef struct frac {
    int nume, deno;
} frac;

int gcd(int x, int y)
{
    int t;
    if (x < y) {
        t = x; x = y; y = t;
    }
    while (y > 0) {
        t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int isBigger(frac x, frac y)
{
    // a/b - c/d = (ad - bc) / bd
    return (x.nume * y.deno - x.deno * y.nume) > 0;
}

void qs(frac array[], int l, int r)
{
    int i, j;
    frac t, mid;
    i = l; j = r; mid = array[(l + r) / 2];
    do {
        while (i < r && isBigger(mid, array[i])) i++;
        while (l < j && isBigger(array[j], mid)) j--;
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
    int n, i, j, sum;
    frac fracs[13000];

    FILE *fin = fopen("frac1.in", "r");
    FILE *fout = fopen("frac1.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    // generate
    sum = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j < i; j++)
            if (gcd(j, i) == 1) {
                sum++;
                fracs[sum].nume = j;
                fracs[sum].deno = i;
            }

    // sort
    qs(fracs, 1, sum);

    fprintf(fout, "0/1\n");
    for (i = 1; i <= sum; i++)
        fprintf(fout, "%d/%d\n", fracs[i].nume, fracs[i].deno);
    fprintf(fout, "1/1\n");

    fclose(fin);
    fclose(fout);
    return 0;
}

