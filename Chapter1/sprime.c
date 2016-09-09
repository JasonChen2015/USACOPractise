/*
ID: cyl12341
LANG: C
TASK: sprime
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int digits[5] = {1, 3, 5, 7, 9};

int isPrime(int num)
{
    int i, t;
    if (num == 1) return 0;
    t = round(sqrt(num));
    for (i = 2; i <= t; i++)
        if (num % i == 0) return 0;
    return 1;
}

int main (void)
{
    int n;
    int p, q; // start and end pointer to array sprime
    int d, i, j, tq, tmp;
    int sprime[1000];

    FILE *fin = fopen("sprime.in", "r");
    FILE *fout = fopen("sprime.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    p = 1; q = 4;
    sprime[1] = 2; sprime[2] = 3; sprime[3] = 5; sprime[4] = 7;
    d = 1;
    tq = q; // the new end pointer to array sprime
    while (d < n) {
        d++;
        for (i = p; i <= q; i++) {
            for (j = 0; j < 5; j++) {
                // new num
                tmp = sprime[i] * 10 + digits[j];
                // judge if is prime
                if (isPrime(tmp)) {
                    tq++;
                    sprime[tq] = tmp;
                }
            }
        }
        p = q + 1;
        q = tq;
    }

    for (i = p; i <= q; i++)
        fprintf(fout, "%d\n", sprime[i]);

    fclose(fin);
    fclose(fout);
    return 0;
}

