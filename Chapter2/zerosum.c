/*
ID: cyl12341
LANG: C
TASK: zerosum
*/
#include <stdio.h>
#include <assert.h>

FILE *fin, *fout;
int n;
char s[] = "1 2 3 4 5 6 7 8 9";

void check(char *st) {
    int i = 0, s = 0, t = 0, o = 1;
    while (st[i] != '\0') {
        switch (st[i]) {
        case ' ':
            break;
        case '+':
            s = s + t * o;
            o = 1;
            t = 0;
            break;
        case '-':
            s = s + t * o;
            o = -1;
            t = 0;
            break;
        default:
            t = t * 10 + st[i] - 48;
            break;
        }
        i++;
    }
    s = s + t * o;
    if (s == 0) {
        fprintf(fout, "%s\n", st);
    }
}

void dfs(char* st, int depth) {
    if (depth == n) {
        // calculate & check
        check(st);
        return;
    }
    st[depth * 2 - 1] = ' ';
    dfs(st, depth + 1);
    st[depth * 2 - 1] = '+';
    dfs(st, depth + 1);
    st[depth * 2 - 1] = '-';
    dfs(st, depth + 1);
    st[depth * 2 - 1] = ' ';
}

int main(void) {
    fin = fopen("zerosum.in", "r");
    fout = fopen("zerosum.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);
    s[n * 2 - 1] = '\0';
    dfs(s, 1);

    fclose(fin);
    fclose(fout);

    return 0;
}

