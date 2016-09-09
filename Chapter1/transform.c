/*
ID: cyl12341
LANG: C
TASK: transform
 */
#include <stdio.h>
#include <assert.h>

#define MAXN 10

void transform(char fromP[MAXN][MAXN], char toP[MAXN][MAXN], int way, int size)
{
    int i, j;
    switch (way) {
        case 1: // 90 degreee rotation
           for (i = 0; i < size; i++) {
               for (j = 0; j < size; j++) {
                   toP[i][j] = fromP[size - j - 1][i];
               }
           }               
        break;
        case 2: // 180 degree rotation
           for (i = 0; i < size; i++) {
               for (j = 0; j < size; j++) {
                   toP[i][j] = fromP[size - i - 1][size - j - 1];
               }
           }       
        break;
        case 3: // 270 degree rotation
           for (i = 0; i < size; i++) {
               for (j = 0; j < size; j++) {
                   toP[i][j] = fromP[j][size - i - 1];
               }
           }       
        break;
        case 4: // reflacted horizontally
           for (i = 0; i < size; i++) {
               for (j = 0; j < size; j++) {
                   toP[i][j] = fromP[i][size - j - 1];
               }
           }       
        break;
    }
}

// 1 for true, 0 for false
int checkPattern(char fromP[MAXN][MAXN], char toP[MAXN][MAXN], int size) {
    int i, j;
    int isSame = 1;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (fromP[i][j] != toP[i][j]) {
                isSame = 0;
                return isSame;
            }
        }
    }
    return isSame;
}

int main (void)
{
    int n, i, j;
    char before[MAXN][MAXN], after[MAXN][MAXN], tmp[MAXN][MAXN];
    int flag = 0; // the transform number

    FILE *fin = fopen("transform.in", "r");
    FILE *fout = fopen("transform.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    // before transform
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j == 0) fscanf(fin, "\n%c", &before[i][j]);
            else fscanf(fin, "%c", &before[i][j]);
        }
    }
    // after transform
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j == 0) fscanf(fin, "\n%c", &after[i][j]);
            else fscanf(fin, "%c", &after[i][j]);
        }
    }

    // just rotated clockwisely
    for (i = 1; i <= 3; i++) {
        transform(before, tmp, i, n);
        if (checkPattern(tmp, after, n) == 1) {
            flag = i;
            break;
        }
    }
    if (flag == 0) {
        // reflection
        transform(before, tmp, 4, n);
        if (checkPattern(tmp, after, n) == 1) {
            flag = 4;
        }
        if (flag == 0) {
            // reflectd and rotated
            char tmp1[MAXN][MAXN];
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++) tmp1[i][j] = tmp[i][j];
            for (i = 1; i <= 3; i++) {
                transform(tmp1, tmp, i, n);
                if (checkPattern(tmp, after, n) == 1) {
                    flag = 5;
                    break;
                }
            }
        }
		if (flag == 0) {
			// no change
			if (checkPattern(before, after, n) == 1) flag = 6;
		}
        // invalid transformation
        if (flag == 0) flag = 7;
    }

    fprintf(fout, "%d\n", flag);

    fclose(fout);
    return 0;
}

