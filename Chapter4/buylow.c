/*
ID: cyl12341
LANG: C
TASK: buylow
*/
#include <stdio.h>
#include <assert.h>

#define MAXN 5000
#define INF 2147483647
#define MAXB 200

typedef int BIG [MAXB + 1]; // index 0 store the bits

int n;
int price[MAXN + 1];
int series[MAXN + 1]; // the max length of sequence with this price
int next[MAXN + 1];   // whether has duplicate price
BIG num[MAXN + 1];    // the max number of sequence with this price

// plus a to b
void plus(BIG b, BIG a) {
    int i;
    int na = a[0], nb = b[0];
    int m = na > nb ? na : nb;
    for (i = 1; i <= m; i++) b[i] = a[i] + b[i];
    for (i = 1; i <= m; i++) {
        b[i + 1] += b[i] / 10;
        b[i] %= 10;
    }
    b[0] = b[m + 1] ? (m + 1) : m;
}

// copy a to b
void copy(BIG b, BIG a) {
    int i;
    b[0] = a[0];
    for (i = 1; i <= MAXB; i++) b[i] = a[i];
}

// assign a to b
void assign(BIG b, int a) {
    int i;
    for (i = 1; i <= MAXB; i++) b[i] = 0;
    i = 0;
    while (a > 0) {
        i++;
        b[i] = a % 10;
        a /= 10;
    }
    b[0] = i;
}

int main() {
    int i, j;
    FILE *fin = fopen("buylow.in", "r");
    FILE *fout = fopen("buylow.out", "w");

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d", &price[i]);
    }

    // record next duplicate price
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (price[i] == price[j]) {
                next[i] = j;
                break;
            }
        }
    }

    // dp search
    series[0] = 1;
    assign(num[0], 1);
    for (i = 1; i <= n; i++) { // set n for counting number of sequence
        series[i] = 1;
        assign(num[i], 1);
        for (j = 0; j < i; j++) {
            if (next[j] && next[j] < i) continue; // just search the same sequence once
            if (price[j] > price[i]) { // add this price to sequence
                if (series[j] + 1 > series[i]) {
                    series[i] = series[j] + 1;
                    copy(num[i], num[j]);
                } else if (series[j] + 1 == series[i]) {
                    plus(num[i], num[j]);
                }
            }
        }
    }

    // output result
    fprintf(fout, "%d ", series[n] - 1);
    for (i = num[n][0]; 1 <= i; i--)
        fprintf(fout, "%d", num[n][i]);
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);

    return 0;
}
