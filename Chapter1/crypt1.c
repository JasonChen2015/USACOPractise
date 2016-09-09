/*
ID: cyl12341
LANG: C
TASK: crypt1
*/
#include <stdio.h>
#include <assert.h>

int digit[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // record if the digit is used

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
	if (l < j) qs(array, l, j);
	if (i < r) qs(array, i, r);
}

int CheckDigit(int num)
{
    int t;
    while (num > 0) {
        t = num % 10;
        if (digit[t] == 0) return 0;
        num = num / 10;
    }
    return 1;
}

int main (void)
{
    int n, i, j, k, p, q, sum;
    int ijk, pq, prod1, prod2, res;
    int crypt[10];

    FILE *fin = fopen("crypt1.in", "r");
    FILE *fout = fopen("crypt1.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &crypt[i]);
        digit[crypt[i]] = 1;
    }

    sum = 0;
	qs(crypt, 0, n);
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    for (k = 0; k < n; k++) {
        ijk = crypt[i] * 100 + crypt[j] * 10 + crypt[k];
        for (p = 0; p < n; p++) {
            // partial product 2
            prod2 = ijk * crypt[p];
            if (prod2 > 999) break;
            if (CheckDigit(prod2) == 0) continue;
            for (q = 0; q < n; q++) {
                // partial product 1
                prod1 = ijk * crypt[q];
                if (prod1 > 999) break;
                if (CheckDigit(prod1) == 0) continue;
                // result
                pq = crypt[p] * 10 + crypt[q];
                res = ijk * pq;
                if (res > 9999) break;
                if (CheckDigit(res) == 1) sum++;
            }
        }
    }

    fprintf(fout, "%d\n", sum);

    fclose(fin);
    fclose(fout);
    return 0;
}

