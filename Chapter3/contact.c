/*
ID: cyl12341
LANG: C
TASK: contact
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

char emi[200001];
char patt[8200][13];
int count[8200];

int bin[14] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

int genPattNum(int l, int r) {
    int i;
    int num = 0;
    for (i = l; i <= r; i++) {
        if (emi[i] == '1') num += bin[r - i];
    }
    num += bin[r - l + 1]; // add 1 to distinct the number which has prefix 0
    return num;
}

void genPattern(int num) {
    int i, j, t;
    t = num; i = 12; j = -2;
    while (t < bin[i] && 0 <= i) i--;
    for (; 0 <= i; i--) {
        j++;
        if (t >= bin[i]) {
            t -= bin[i];
            if (j == -1) continue;
            patt[num][j] = '1';
        } else {
            patt[num][j] = '0';
        }
    }
}

void sortNum(int l, int r) {
    int i, j, t;
    char str[13];
    for (i = l; i <= r; i++) {
        for (j = i + 1; j <= r; j++) {
            if (count[i] < count[j]) {
                t = count[i]; count[i] = count[j]; count[j] = t;
                strcpy(str, patt[i]);
                strcpy(patt[i], patt[j]);
                strcpy(patt[j], str);
            }
        }
    }
}

void sortPatt(int l, int r) {
    int i, j, p, q;
    char str[13];
    for (i = l; i <= r; i++) {
        for (j = i + 1; j <= r; j++) {
            p = strlen(patt[i]);
            q = strlen(patt[j]);
            if (p > q || (p == q && strcmp(patt[i], patt[j]) > 0)) {
                strcpy(str, patt[i]);
                strcpy(patt[i], patt[j]);
                strcpy(patt[j], str);
            }
        }
    }
}

int main(void) {
    int a, b, n, m;
    int i, j, k, p, q;
    char ch;

    FILE *fin = fopen("contact.in", "r");
    FILE *fout = fopen("contact.out", "w");
    assert(fin != NULL && fout != NULL);

    // input
    fscanf(fin, "%d%d%d", &a, &b, &n);
    m = 0;
    while (fscanf(fin, "%c", &ch) != EOF) {
        if (ch != '\n') {
            m++;
            emi[m - 1] = ch;
        }
    }

    // count
    for (i = a; i <= b; i++) {
        for (j = 0; j < m - i + 1; j++) {
           count[genPattNum(j, j + i - 1)]++; 
        }
    }

    // get pattern
    for (i = bin[a]; i < bin[b + 1]; i++) {
        if (count[i] > 0) genPattern(i);
    }

    // sort
    sortNum(bin[a], bin[b + 1] - 1);
    p = bin[a];
    for (i = 0; i < n; i++) {
        q = p;
        if (count[p] == 0) break;
        while (q < bin[b + 1] && count[p] == count[q]) q++;
        sortPatt(p, q - 1);

        // output
        fprintf(fout, "%d\n", count[p]);
        k = 0;
        for (j = p; j <= q - 1; j++) {
            k++;
            if (k == 7) { k = 1; fprintf(fout, "\n"); }
            if (k != 1) fprintf(fout, " ");
            fprintf(fout, "%s", patt[j]);
        }
        fprintf(fout, "\n");

        p = q;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

