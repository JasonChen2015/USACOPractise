/*
ID: cyl12341
LANG: C
TASK: prefix
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

char seq[200001];
int seqi[200001];
char pri[27][200][11];
int prin[27];

int main(void) {
    FILE *fin = fopen("prefix.in", "r");
    FILE *fout = fopen("prefix.out", "w");
    assert(fin != NULL && fout != NULL);

    char ch, s[11] = "";
    int p = 0;
    fscanf(fin, "%c", &ch);
    while (ch != '.') {
        if (ch != ' ' && ch != '\n') {
            s[p] = ch;
            p++;
        } else {
            int t = s[0] - 64;
            s[p] = '\0';
            strcpy(pri[t][++prin[t]], s);
            s[0] = '\0';
            p = 0;
        }
        fscanf(fin, "%c", &ch);
    }
    int seqn = 0;
    while (fscanf(fin, "%c", &ch) != EOF) {
        if (ch != '\n') {
            seqn++;
            seq[seqn] = ch;
        }
    }

    seqi[0] = 1;
    int i, j, k;
    for (i = 1; i <= seqn; i++) {
        int ok = 0;
        for (j = i - 10; j < i; j++) {
            if (j < 0) continue;
            if (ok == 1) break;
            if (seqi[j] == 0) continue;
            for (k = 1; k <= prin[seq[j + 1] - 64]; k++) {
                char temp[11];
                int l;
                for (l = j + 1; l <= i; l++) {
                    temp[l - j - 1] = seq[l];
                }
                temp[l - j - 1] = '\0';
                if (strcmp(temp, pri[seq[j + 1] - 64][k]) == 0) {
                    seqi[i] = 1;
                    ok = 1;
                    break;
                }
            }
        }
    }

    j = 0;
    for (i = seqn; i > 0; i--) {
        if (seqi[i] == 1) {
            fprintf(fout, "%d\n", i);
            j = 1;
            break;
        }
    }
    if (j == 0) fprintf(fout, "0\n");

    fclose(fin);
    fclose(fout);

    return 0;
}

