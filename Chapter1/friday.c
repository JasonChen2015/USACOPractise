/*
ID: cyl12341
LANG: C
TASK: friday
 */
#include <stdio.h>
#include <assert.h>

// the fact that 1900/01/01 was on a Monday

const int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0};

// if YEAR is leap year then return 1 else return 0
int isLeapYear(int year) {
	if (year % 100 == 0) {
		if (year % 400 == 0) return 1; else return 0;
	} else {
		if (year % 4 == 0) return 1; else return 0;
	}
}

int main (void) {
	FILE *fin  = fopen("friday.in", "r");
	FILE *fout = fopen("friday.out", "w");
	assert(fin != NULL && fout != NULL);
	int i, j, n, t;
	int p = 5;            // point the 13th is on which day
	int sum[7] = {0};     // restore the sumary of each day in a week
	sum[p]++;             // the 1900/01/13 was on Sat.
	fscanf (fin, "%d", &n);
	// count from years
	for (i = 0; i < n; i++) {
		// count from months
		for (j = 1; j <= 12; j++) {
			if (j == 2) {
				if (isLeapYear(1900 + i) == 0) {
					t = months[j];
				} else {
					t = months[j] + 1;
				}
			} else {
				t = months[j];
			}
			p = (p + t % 7) % 7;
			sum[p]++;
		}
	}
	sum[p]--;
	// print Sat., Sun., Mon., Tue., ..., Fri.
	fprintf (fout, "%d %d %d %d %d %d %d\n", sum[5], sum[6], sum[0], sum[1], sum[2], sum[3], sum[4]);
	fclose(fout);
	return 0;
}

