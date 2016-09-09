/*
ID: cyl12341
LANG: C
TASK: pprime
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int digit[10][2] = {{1, 9}, {1, 9}, {1, 9}, {10, 99}, {10, 99},{100, 999},
                          {100, 999}, {1000, 9999}, {1000, 9999}, {1000, 9999}};

int getDigit(int num)
{
    int t = 0;
    while (num > 0) {
        num = num / 10;
        t++;
    }
    return t;
}

void qs(int array[], int l, int r)
{
    int i, j, t, mid;
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

int isPrime(int num)
{
    int i, t;
    t = round(sqrt(num));
    for (i = 2; i <= t; i++)
        if (num % i == 0) return 0;
    return 1;
}

// flag = 1 means get Odd or flag = 0 means get Even
int getNewNum(int flag, int num)
{
    int i, tmp, result;
    i = 0;
    tmp = num;
    result = 0;
    while (tmp > 0) {
        i++;
        if (flag && i == 1) { // when get odd the lastest digit doesn't need to mirror
            tmp = tmp / 10;
            continue;
        }
        result = result * 10 + tmp % 10;
        num = num * 10;
        tmp = tmp / 10;
    }
    return num + result;
}

int main (void)
{
    int a, b, la, lb, i, t;
    int sum; // records the prime that has been created
    int prime[20000];

    FILE *fin = fopen("pprime.in", "r");
    FILE *fout = fopen("pprime.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &a, &b);

    sum = 0;
    la = getDigit(a);
    lb = getDigit(b);
    for (i = digit[la][0]; i <= digit[lb][1]; i++) {
        // Odd
        t = getNewNum(1, i);
        if (isPrime(t) == 1) {
            sum++;
            prime[sum] = t;
        }
        // Even
        t = getNewNum(0, i);
        if (isPrime(t) == 1) {
            sum++;
            prime[sum] = t;
        }
    }
    qs(prime, 1, sum);

    for (i = 1; i <= sum; i++)
        if (a <= prime[i] && prime[i] <= b)
            fprintf(fout, "%d\n", prime[i]);

    fclose(fin);
    fclose(fout);
    return 0;
}

