/*
ID: cyl12341
LANG: C
TASK: namenum
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXN 12

const char keypad[] = {'2', '2', '2',      // A, B, C,
                       '3', '3', '3',      // D, E, F,
                       '4', '4', '4',      // G, H, I,
                       '5', '5', '5',      // J, K, L,
                       '6', '6', '6',      // M, N, O,
                       '7', '0', '7', '7', // P, Q, R, S,
                       '8', '8', '8',      // T, U, V,
                       '9', '9', '9', '0'};// W, X, Y, Z

int checkName(char name[MAXN], char num[MAXN]) {
    int i, len;
	int flag = 1;
    char tmpnum[MAXN] = {0};
    len = strlen(name);
    for (i = 0; i < len; i++) {
        tmpnum[i] = keypad[name[i] - 65];
        if (tmpnum[i] != num[i]) {
            flag = 0;
            break;
        }
    }
    return flag;
}

int main (void)
{
    char num[MAXN], ch[MAXN];
    int numlen;
    int flag = 0; // if have result
    
    FILE *fin = fopen("namenum.in", "r");
    FILE *fout = fopen("namenum.out", "w");
    FILE *fdic = fopen("namenumdict.txt", "r");
    assert(fin != NULL && fout != NULL && fdic != NULL);

    fscanf(fin, "%s", num);
    numlen = strlen(num);

    while (fscanf(fdic, "%s", ch) != EOF) {
        if (strlen(ch) == numlen) {
            if (checkName(ch, num) == 1) {
                flag = 1;
                fprintf(fout, "%s\n", ch);
            }
        }
    }
    if (flag == 0) fprintf(fout, "NONE\n");

    fclose(fin);
    fclose(fout);
    fclose(fdic);
    return 0;
}

