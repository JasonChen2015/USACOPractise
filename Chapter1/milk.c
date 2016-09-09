/*
ID: cyl12341
LANG: C
TASK: milk
 */
#include <stdio.h>
#include <assert.h>

int main (void)
{
    int n, m, i, result, price, amount;
	int sell[1001];

    FILE *fin = fopen("milk.in", "r");
    FILE *fout = fopen("milk.out", "w");
    assert(fin != NULL && fout != NULL);

	for (i = 0; i < 1001; i++) {
		sell[i] = 0;
	}
    fscanf(fin, "%d %d\n", &n, &m);
    for (i = 0; i < m; i++) {
        fscanf(fin, "%d %d\n", &price, &amount);
		sell[price] = sell[price] + amount;
    }

    // greedy get
    i = 0;
    while (n > 0) {
        if (sell[i] > n) {
            result = result + n * i;
            n = 0;
        } else {
            n = n - sell[i];
            result = result + sell[i] * i;
            i++;
        }
    }

    fprintf(fout, "%d\n", result);

    fclose(fin);
    fclose(fout);
    return 0;
}

