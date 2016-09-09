/*
ID: cyl12341
LANG: C
TASK: milk2
 */
#include <stdio.h>
#include <assert.h>

void qs(int array[], int l, int r) {
    int i, j, mid, t;
    i = l;
    j = r;
    mid = array[(l + r) / 2];
    do {
        while (i < r && array[i] < mid) i++;
        while (l < j && mid < array[j]) j--;
        if (i <= j) {
            t = array[i];
            array[i] = array[j];
            array[j] = t;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) qs(array, l, j);
    if (i < r) qs(array, i, r);
}

// cause it must be found
int find(int array[], int num, int l, int r) {
    int mid = (l + r) / 2;
    if (num == array[mid]) return mid;
    else if (num < array[mid]) return find(array, num, l, mid - 1);
    else return find(array, num, mid + 1, r);
}

int main (void)
{
    int i, p, n;
    int m;                // the num of timestamp
    int maxmilk, maxnomilk; // the result
    int record[5000][2];  // record the input data
    int timestamp[10001]; // record the timestamp
    int ans[10001];       // the real status

    FILE *fin = fopen("milk2.in", "r");
    FILE *fout = fopen("milk2.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d\n", &n);
    for (i = 0; i < n; i++) {
        fscanf(fin, "%d %d\n", &record[i][0], &record[i][1]);
        timestamp[2 * i] = record[i][0];
        timestamp[2 * i + 1] = record[i][1];
    }
    // sort the timestamp ascending
    qs(timestamp, 0, 2 * n -1);
    // filter the same timestamp
    m = 0;
    p = 0;
    while (p < 2 * n) {
        int t = p;
        // find the next timestamp
        while (t < 2 * n && timestamp[m] == timestamp[t]) t++;
		if (t >= 2 * n) break;
        m++;
        timestamp[m] = timestamp[t];
        // the started position for next round
        p = t;
    }
    for (i = 0; i <= m; i++) ans[i] = 0;

    // fill the time
    for (i = 0; i < n; i++) {
        p = find(timestamp, record[i][0], 0, m);
        while (p < m && timestamp[p + 1] <= record[i][1]) {
            ans[p] = 1;
            p++;
        }
    }

    // get the maxmilk and maxnomilk
    maxmilk = 0;
    maxnomilk = 0;
    i = 0;
    while (i < m) {
        p = i;
        while (p <= m && ans[p] == ans[i]) p++;
        if (ans[i] == 1) {
			// milk
            if (timestamp[p] - timestamp[i] > maxmilk)
                maxmilk = timestamp[p] - timestamp[i];
        } else {
			// nomilk
            if (timestamp[p] - timestamp[i] > maxnomilk)
                maxnomilk = timestamp[p] - timestamp[i];
        }
        i = p;
    }

    fprintf(fout, "%d %d\n", maxmilk, maxnomilk);

    fclose(fout);
    return 0;
}

