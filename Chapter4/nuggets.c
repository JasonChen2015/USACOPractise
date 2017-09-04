/*
ID: cyl12341
LANG: C
TASK: nuggets
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 10
#define MAXM 256

int num[MAXN + 1];
int dp[MAXM + 1];

int gcd(int x, int y) {
    int t;
    if (x < y) {
        t = x; x = y; y = t;
    }
    while (y != 0) {
        t = x % y; x = y; y = t;
    }
    return x;
}

int main() {
    int n, max, min;
    int i, k, t, ans, count;

    FILE *fin = fopen("nuggets.in", "r");
    FILE *fout = fopen("nuggets.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    max = 0;
    min = MAXM;
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &num[i]);
        dp[num[i]] = 1;
        if (num[i] > max) max = num[i];
        if (min > num[i]) min = num[i];
    }
    dp[0] = 1;

    t = num[0];
    for (i = 1; i < n; i++) t = gcd(t, num[i]); // get gcd of all numbers
    if (t != 1) {
        ans = 0;
    } else {
        k = min;
        ans = k - 1; // max un-combinable num
        count = 0; // total num of progression
        while (1) {
            t = k % max;
            if (dp[t]) {
                count++;
                if (count >= min) break;
                for (i = 0; i < n; i++) {
                    dp[(t + num[i]) % max] = 1;
                }
            } else {
                ans = k;
                count = 0;
            }
            k++;
        }
    }

    fprintf(fout, "%d\n", ans);

    fclose(fin);
    fclose(fout);

    return 0;
}
